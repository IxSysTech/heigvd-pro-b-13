#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Permet de cacher le mot de passe
    ui->txtDBPassword->setEchoMode(QLineEdit::Password);
    ui->txtSSHPassword->setEchoMode(QLineEdit::Password);

    ui->pgbDownload->setVisible(false);
    ui->lblInfo->setVisible(false);

    //Pour les tests
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
    ssh_session session = nullptr;
    ssh_channel channel = nullptr;
    fileDataSource = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/remoteSequences";

    this->setGUIEnabled(false);
    rc = sshConnect(&session);
    if(rc != SSH_OK){
        setGUIEnabled(true);
        ui->lblInfo->setText("Connection to host via SSH failed");
        qApp->processEvents();
    } else {
        rc = channelConnect(session, channel);
        if(rc != SSH_OK){
            ui->lblInfo->setText("Connection to host via SSH failed");
            setGUIEnabled(true);
            qApp->processEvents();
        } else {
            ui->lblInfo->setText("Connecting to the database...");
            qApp->processEvents();

            //Formatage de la requete

            std::string sqlResquest = ui->sqlRequest->toPlainText().toStdString();
            char command[500];
            sprintf(command, "PGPASSWORD=%s psql -U %s %s -c \"Copy (%s) To stdout With CSV DELIMITER ';';\" > /home/samuel.mettler/result.csv",
                    ui->txtDBPassword->text().toLocal8Bit().data(),
                    ui->txtDBUsername->text().toLocal8Bit().data(),
                    ui->txtDBName->text().toLocal8Bit().data(),
                    sqlResquest.data());

            std::cout << command << std::endl;



            //Envoie de la commande pour la requete au serveur distant
            rc = sshWrite(channel, command);
            sleep(5);
            if (rc != SSH_OK){
                ui->lblInfo->setText("Connection to database failed");
                setGUIEnabled(true);
                qApp->processEvents();
            } else {
                //Lecture du fichier de résultat de la requete
                ui->lblInfo->setText("Getting data from database ...");
                qApp->processEvents();

                rc = scpRead(session);
                if(rc != SSH_OK){
                    ui->lblInfo->setText("Error during the download of data");
                    qApp->processEvents();
                    setGUIEnabled(true);
                } else {
                    this->hide();
                    this->p.setDataSource(fileDataSource);
                    this->p.show();
                }
            }
        }

        //Fermeture de toutes les connexions ssh
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
    }
}

int MainWindow::sshWrite(ssh_channel channel, char* command){
    int rc = 0;

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

    //Création de l'objet SSH
    *session = ssh_new();

    //Spécification du hostname
    ssh_options_set(*session, SSH_OPTIONS_HOST, ui->txtSSHHost->text().toLocal8Bit().data());

    rc = ssh_connect(*session);
    if (rc != SSH_OK){
        fprintf(stderr, "Error: %s\n", ssh_get_error(session));
        ssh_free(*session);
        return SSH_ERROR;
    }

    //Connection avec le mot de passe
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

int MainWindow::scpRead(ssh_session session){
    ssh_scp scp;
    int rc;
    int size, mode;
    char *filename, *buffer;
    scp = ssh_scp_new(session, SSH_SCP_READ, "/home/samuel.mettler/result.csv");
    FILE* file = fopen(fileDataSource.toLocal8Bit().data(), "w+");
    int fd = fileno(file);

    if(fd == -1){
        return -1;
    }

    if (scp == NULL)
    {
        fprintf(stderr, "Error allocating scp session: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }
    rc = ssh_scp_init(scp);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error initializing scp session: %s\n", ssh_get_error(session));
        ssh_scp_free(scp);
        return SSH_ERROR;
    }

    rc = ssh_scp_pull_request(scp);
    if (rc != SSH_SCP_REQUEST_NEWFILE)
    {
        fprintf(stderr, "Error receiving information about file: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    size = ssh_scp_request_get_size(scp);
    if(size == 0){
        return SSH_ERROR;
    }

    filename = strdup(ssh_scp_request_get_filename(scp));
    mode = ssh_scp_request_get_permissions(scp);
    printf("Receiving file %s, size %d, permissions 0%o\n",
           filename, size, mode);
    free(filename);
    buffer = (char*)malloc(size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return SSH_ERROR;
    }
    ssh_scp_accept_request(scp);

    //Le fichier est lu par bloque
    //La boucler permet de lire tout le fichier
    ui->pgbDownload->setVisible(true);
    ui->btnConnect->setVisible(false);
    ui->pgbDownload->setMaximum(size);
    int r = 0;
    while (r < size) {
        int st = ssh_scp_read(scp, buffer+r, size-r);
        r += st;
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
    write(fd, buffer, size);
    free(buffer);
    rc = ssh_scp_pull_request(scp);
    if (rc != SSH_SCP_REQUEST_EOF)
    {
        ui->pgbDownload->setVisible(false);
        ui->btnConnect->setVisible(true);
        fprintf(stderr, "Unexpected request: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    ssh_scp_close(scp);
    ssh_scp_free(scp);
    return SSH_OK;
}

int MainWindow::channelConnect(ssh_session session, ssh_channel &channel){ 
    int rc;

    channel = ssh_channel_new(session);
    if (channel == NULL){
        return SSH_ERROR;
    }

    //Ouverture du channel
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
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Browse file data"),
                "/home",
                "All files (*.*)"
                );

    fileDataSource = path;
    QFile f(path);
    QFileInfo fileInfo(f);

    QString filename = fileInfo.fileName();
    int fileSize = fileInfo.size();

    char fileInfoContent[500];

    sprintf(fileInfoContent, "Date file information : \nFilename : %s \nSize : %d Bytes \nPath : %s",
            filename.toLocal8Bit().data(),
            fileSize,
            path.toLocal8Bit().data());

    fileSelected = true;
    ui->lblFileInfo->setText(fileInfoContent);
}

void MainWindow::on_btnContinue_clicked()
{
    if(fileSelected){
        this->hide();
        this->p.setDataSource(fileDataSource);
        this->p.show();
    }
}
