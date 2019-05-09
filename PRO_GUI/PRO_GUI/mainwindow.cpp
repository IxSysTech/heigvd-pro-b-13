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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ckbUseSSH_clicked()
{
    //Enable au disable de section of ssh connection
    ui->txtSSHPassword->setDisabled(ui->txtSSHPassword->isEnabled());
    ui->txtSSHUsername->setDisabled(ui->txtSSHUsername->isEnabled());
    ui->txtSSHHost->setDisabled(ui->txtSSHHost->isEnabled());
    ui->label_6->setDisabled(ui->label_6->isEnabled());
    ui->label_7->setDisabled(ui->label_7->isEnabled());
    ui->label_8->setDisabled(ui->label_8->isEnabled());


    //Pour les tests
    ui->txtDBHost->setText("localhost");
    ui->txtDBName->setText("prot_family_b13");
    ui->txtDBUsername->setText("samuel_m");
    ui->txtDBPassword->setText("samuel_db");

    ui->txtSSHHost->setText("trex.lan.iict.ch");
    ui->txtSSHUsername->setText("samuel.mettler");
    ui->txtSSHPassword->setText("samuel.b13");
}

void MainWindow::on_btnConnect_clicked()
{
    if(ui->ckbUseSSH->isChecked()){
        ssh_session session = sshConnect();
        sftp_session sftp = sftpConnect(session);
        ssh_channel channel = channelConnect(session);
        int rc;

        //Formatage de la requete
        char* sqlResquest = "SELECT protein.sadn, location.id FROM \"PRO19\".protein INNER JOIN \"PRO19\".prot_to_loc ON protein.id = prot_to_loc.fk_prot INNER JOIN \"PRO19\".location on prot_to_loc.fk_loc = location.id WHERE location.id != 7 LIMIT  1900;";
        char command[500];
        sprintf(command, "PGPASSWORD=%s psql -U %s %s -c '%s' > result.txt;",
                ui->txtDBPassword->text().toLocal8Bit().data(),
                ui->txtDBUsername->text().toLocal8Bit().data(),
                ui->txtDBName->text().toLocal8Bit().data(),
                sqlResquest);

        //Envoie de la commande pour la requete au serveur distant
        //sshWrite(channel, command);

        //sleep(5);

        //Lecture du fichier de résultat de la requete
        rc = sshReadFile(session, sftp);
        if(rc != SSH_OK){
            std::cout << "Erreur de lecture dans le fichier" << std::endl;
        }

        //Fermeture de toutes les connexions ssh
        sftp_free(sftp);
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
    }
}

void MainWindow::sshRead(ssh_channel channel){
    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes;

    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0)
    {
        if (fwrite(buffer, 1, nbytes, stdout) != nbytes){
            ssh_channel_close(channel);
            ssh_channel_free(channel);
            std::cout << SSH_ERROR << std::endl;
        }
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }

    if (nbytes < 0){
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        std::cout << SSH_ERROR << std::endl;
    }

    std::cout << buffer << std::endl;
}

void MainWindow::sshWrite(ssh_channel channel, char* command){
    int rc = 0;

    rc = ssh_channel_request_exec(channel, command);
    if (rc != SSH_OK)
    {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        std::cout << SSH_ERROR << std::endl;
    }
}

ssh_session MainWindow::sshConnect(){
    int rc;

    //Création de l'objet SSH
    ssh_session session = ssh_new();
    if (session == NULL){ exit(-1); }

    //Spécification du hostname
    ssh_options_set(session, SSH_OPTIONS_HOST, ui->txtSSHHost->text().toLocal8Bit().data());

    rc = ssh_connect(session);
    if (rc != SSH_OK){
        fprintf(stderr, "Error: %s\n", ssh_get_error(session));
        ssh_free(session);
        exit(-1);
    }

    //Connection avec le mot de passe
    rc = ssh_userauth_password(session, ui->txtSSHUsername->text().toLocal8Bit().data(), ui->txtSSHPassword->text().toLocal8Bit().data());
    if (rc != SSH_AUTH_SUCCESS){
        fprintf(stderr, "Error authenticating with password: %s\n",
            ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        exit(-1);
    }

    return session;
}

sftp_session MainWindow::sftpConnect(ssh_session session){
    sftp_session sftp;
    int rc;

    sftp = sftp_new(session);
    if (sftp == NULL)
    {
        fprintf(stderr, "Error allocating SFTP session: %s\n", ssh_get_error(session));
        exit(SSH_ERROR);
    }
    rc = sftp_init(sftp);
    if (rc != SSH_OK)
    {
    fprintf(stderr, "Error initializing SFTP session: %s.\n",
        sftp_get_error(sftp));
        sftp_free(sftp);
        exit(SSH_ERROR);
    }

    return sftp;
}

ssh_channel MainWindow::channelConnect(ssh_session session){
    ssh_channel channel = ssh_channel_new(session);
    int rc;
    if (channel == NULL){
        exit(SSH_ERROR);
    }

    //Ouverture du channel
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_channel_free(channel);
        exit(SSH_ERROR);
    }

    return channel;
}

int MainWindow::sshReadFile(ssh_session session, sftp_session sftp){
    int access_type;
     sftp_file file;
     char buffer[MAX_XFER_BUF_SIZE];
     int async_request;
     int nbytes;
     long counter;
     int rc;
     int fd;
     access_type = O_RDONLY;

     fd = open("/home/david/Desktop/HEIG-VD/PRO/heigvd-pro-b-13/PRO_GUI/PRO_GUI/result.txt", O_CREAT);

     file = sftp_open(sftp, "/home/samuel.mettler/result.txt", access_type, 0);
     if (file == NULL) {
       fprintf(stderr, "Can't open file for reading: %s\n", ssh_get_error(session));
       return SSH_ERROR;
     }
     sftp_file_set_nonblocking(file);
     async_request = sftp_async_read_begin(file, sizeof(buffer));
     counter = 0L;
     usleep(10000);
     if (async_request >= 0) {
       nbytes = sftp_async_read(file, buffer, sizeof(buffer), async_request);
     } else {
         nbytes = -1;
     }
     while (nbytes > 0 || nbytes == SSH_AGAIN) {
       if (nbytes > 0) {
         write(fd, buffer, nbytes);
         async_request = sftp_async_read_begin(file, sizeof(buffer));
       } else {
           counter++;
       }
       usleep(10000);
       if (async_request >= 0) {
         nbytes = sftp_async_read(file, buffer, sizeof(buffer),
                                  async_request);
       } else {
           nbytes = -1;
       }
     }
     if (nbytes < 0) {
       fprintf(stderr, "Error while reading file: %s\n",
               ssh_get_error(session));
       sftp_close(file);
       return SSH_ERROR;
     }
     printf("The counter has reached value: %ld\n", counter);
     rc = sftp_close(file);
     if (rc != SSH_OK) {
       fprintf(stderr, "Can't close the read file: %s\n",
               ssh_get_error(session));
       return rc;
     }
     return SSH_OK;
}

