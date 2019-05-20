#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Hide the password
    ui->txtDBPassword->setEchoMode(QLineEdit::Password);
    ui->txtSSHPassword->setEchoMode(QLineEdit::Password);

    ui->pgbDownload->setVisible(false);
    ui->lblInfo->setVisible(false);

    //Only for tests
    ui->txtDBHost->setText("localhost");
    ui->txtDBName->setText("prot_family_b13");
    ui->txtDBUsername->setText("samuel_m");
    ui->txtDBPassword->setText("samuel_db");

    ui->txtSSHHost->setText("trex.lan.iict.ch");
    ui->txtSSHUsername->setText("samuel.mettler");
    ui->txtSSHPassword->setText("samuel.b13");

    ui->lblFileInfo->setWordWrap(true);
    ui->sqlRequest->setText("SELECT protein.sadn, location.id FROM \\\"PRO19\\\".protein INNER JOIN \\\"PRO19\\\".prot_to_loc ON protein.id = prot_to_loc.fk_prot INNER JOIN \\\"PRO19\\\".location on prot_to_loc.fk_loc = location.id WHERE location.id = 1 LIMIT 5000");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    int rc = 0;
    ssh_session session = nullptr;                                                                                  //Session established beetween the local and remot machine
    ssh_channel channel = nullptr;                                                                                  //Channel connected to the remote host
    fileDataSource = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/remoteSequences";   //Local data file location

    //Disable the GUI so that the user can't change the values
    this->setGUIEnabled(false);

    //Create the session beetween the local and remot machine
    rc = sshConnect(&session);
    if(rc != SSH_OK){
        setGUIEnabled(true);
        ui->lblInfo->setText("Connection to host via SSH failed");

        //Refresh the GUI
        qApp->processEvents();
    } else {
        //Connect the channel to the remote host
        rc = channelConnect(session, channel);
        if(rc != SSH_OK){
            ui->lblInfo->setText("Connection to host via SSH failed");
            setGUIEnabled(true);
            qApp->processEvents();
        } else {
            ui->lblInfo->setText("Connecting to the database...");
            qApp->processEvents();

            //Set the remote file path
            QString remoteFileLocation = "/home/" + ui->txtSSHUsername->text() + "/result.csv";

            std::cout << remoteFileLocation.toStdString() << std::endl;

            //Formatting the request
            std::string sqlResquest = ui->sqlRequest->toPlainText().toStdString();
            char command[500];
            sprintf(command, "PGPASSWORD=%s psql -U %s %s -c \"Copy (%s) To stdout With CSV DELIMITER ';';\" > %s",
                    ui->txtDBPassword->text().toLocal8Bit().data(),
                    ui->txtDBUsername->text().toLocal8Bit().data(),
                    ui->txtDBName->text().toLocal8Bit().data(),
                    sqlResquest.data(),
                    remoteFileLocation.toLocal8Bit().data());

            //Send the request to the remote host
            rc = sshWrite(channel, command);
            sleep(5);
            if (rc != SSH_OK){
                ui->lblInfo->setText("Connection to database failed");
                setGUIEnabled(true);
                qApp->processEvents();
            } else {
                ui->lblInfo->setText("Getting data from database ...");
                qApp->processEvents();

                //Copying the result file from the remote host to the local machine
                rc = scpRead(session, remoteFileLocation);
                if(rc != SSH_OK){
                    ui->lblInfo->setText("Error during the download of data");
                    qApp->processEvents();
                    setGUIEnabled(true);
                } else {
                    //Hide this window and display the parameter window
                    this->hide();
                    this->p.setDataSource(fileDataSource);
                    this->p.show();
                }
            }
        }

        //Closing the SSH connection
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
    }
}

int MainWindow::sshWrite(ssh_channel channel, char* command){
    int rc = 0;

    //Send the command to the remote host
    rc = ssh_channel_request_exec(channel, command);
    if (rc != SSH_OK)
    {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    return SSH_OK;
}

int MainWindow::sshConnect(ssh_session *session){
    int rc;

    ui->lblInfo->setVisible(true);
    ui->lblInfo->setText("Connecting to the SSH host...");
    qApp->processEvents();

    //Creation of the ssh session
    *session = ssh_new();

    //Giving hostname
    ssh_options_set(*session, SSH_OPTIONS_HOST, ui->txtSSHHost->text().toLocal8Bit().data());

    rc = ssh_connect(*session);
    if (rc != SSH_OK){
        fprintf(stderr, "Error: %s\n", ssh_get_error(session));
        ssh_free(*session);
        return SSH_ERROR;
    }

    //Giving the username and the password
    rc = ssh_userauth_password(*session, ui->txtSSHUsername->text().toLocal8Bit().data(), ui->txtSSHPassword->text().toLocal8Bit().data());
    if (rc != SSH_AUTH_SUCCESS){
        fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(*session));
        ssh_disconnect(*session);
        ssh_free(*session);
        return SSH_ERROR;
    }

    return SSH_OK;
}

int MainWindow::scpRead(ssh_session session, QString remoteFilePath){
    ssh_scp scp;
    int rc;
    int size, mode;
    char *filename, *buffer;

    //Set the remote location file
    scp = ssh_scp_new(session, SSH_SCP_READ, remoteFilePath.toLocal8Bit().data());

    //Openig the local file
    FILE* file = fopen(fileDataSource.toLocal8Bit().data(), "w+");

    int fd = fileno(file);
    if(fd == -1) return -1;

    if (scp == NULL)
    {
        fprintf(stderr, "Error allocating scp session: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    //Initialization of the SCP object
    rc = ssh_scp_init(scp);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error initializing scp session: %s\n", ssh_get_error(session));
        ssh_scp_free(scp);
        return SSH_ERROR;
    }

    //Send a pull request for the remote file
    rc = ssh_scp_pull_request(scp);
    if (rc != SSH_SCP_REQUEST_NEWFILE)
    {
        fprintf(stderr, "Error receiving information about file: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    //Getting the size of the remote file
    size = ssh_scp_request_get_size(scp);
    if(size == 0){
        return SSH_ERROR;
    }

    //Getting the filename of the remote file
    filename = strdup(ssh_scp_request_get_filename(scp));

    //Getting the UNIX rights of the remote file
    mode = ssh_scp_request_get_permissions(scp);

    //Displaying info about the file
    printf("Receiving file %s, size %d, permissions 0%o\n",
           filename, size, mode);
    free(filename);

    //Allocate memory to stock the remote file
    buffer = (char*)malloc(size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return SSH_ERROR;
    }

    //Accept the pull request
    ssh_scp_accept_request(scp);

    //Display the progress bar and hide the button connect
    ui->pgbDownload->setVisible(true);
    ui->btnConnect->setVisible(false);
    ui->pgbDownload->setMaximum(size);
    int r = 0;

    //Loop that read the file block by block
    while (r < size) {
        int st = ssh_scp_read(scp, buffer+r, size-r);
        r += st;

        //Update the progress bar
        ui->pgbDownload->setValue(r);
        qApp->processEvents();
    }

    if (rc == SSH_ERROR)
    {
        fprintf(stderr, "Error receiving file data: %s\n",
                ssh_get_error(session));
        free(buffer);
        return SSH_ERROR;
    }
    printf("Done\n");

    //Write the content of the remote file to the local file
    write(fd, buffer, size);
    free(buffer);

    //Check if the pull resquest has benn successful
    rc = ssh_scp_pull_request(scp);
    if (rc != SSH_SCP_REQUEST_EOF)
    {
        ui->pgbDownload->setVisible(false);
        ui->btnConnect->setVisible(true);
        fprintf(stderr, "Unexpected request: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    //Close the SCP object
    ssh_scp_close(scp);
    ssh_scp_free(scp);
    return SSH_OK;
}

int MainWindow::channelConnect(ssh_session session, ssh_channel &channel){ 
    int rc;

    //Create the channel to connect to the remote host
    channel = ssh_channel_new(session);
    if (channel == NULL){
        return SSH_ERROR;
    }

    //Open the channel
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    return SSH_OK;
}

void MainWindow::setGUIEnabled(bool value){
    ui->txtDBHost->setEnabled(value);
    ui->txtDBName->setEnabled(value);
    ui->txtDBUsername->setEnabled(value);
    ui->txtDBPassword->setEnabled(value);
    ui->txtSSHHost->setEnabled(value);
    ui->txtSSHUsername->setEnabled(value);
    ui->txtSSHPassword->setEnabled(value);
    ui->sqlRequest->setEnabled(value);
}

void MainWindow::on_btnBrowse_clicked()
{
    //Open a file explorer, path contain the path of the local file where the application will get the datas
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Browse file data"),
                "/home",
                "All files (*.*)"
                );

    fileDataSource = path;

    //Getting info about this file
    QFile f(path);
    QFileInfo fileInfo(f);
    //Filename
    QString filename = fileInfo.fileName();
    //Size
    int fileSize = fileInfo.size();

    char fileInfoContent[500];
    sprintf(fileInfoContent, "Date file information : \nFilename : %s \nSize : %d Bytes \nPath : %s",
            filename.toLocal8Bit().data(),
            fileSize,
            path.toLocal8Bit().data());

    fileSelected = true;

    //Display the information to the user
    ui->lblFileInfo->setText(fileInfoContent);
}

void MainWindow::on_btnContinue_clicked()
{
    if(fileSelected){
        //Hide this window and display the parameter window
        this->hide();
        this->p.setDataSource(fileDataSource);
        this->p.show();
    }
}
