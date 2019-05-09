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

    //Pour les tests
    ui->txtDBHost->setText("localhost");
    ui->txtDBName->setText("prot_family_b13");
    ui->txtDBUsername->setText("samuel_m");
    ui->txtDBPassword->setText("samuel_db");

    ui->txtSSHHost->setText("trex.lan.iict.ch");
    ui->txtSSHUsername->setText("samuel.mettler");
    ui->txtSSHPassword->setText("samuel.b13");
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
}

void MainWindow::on_btnConnect_clicked()
{
    if(ui->ckbUseSSH->isChecked()){
        ssh_session session = sshConnect();
        ssh_channel channel = channelConnect(session);
        int rc;

        //Formatage de la requete
        char* sqlResquest = "SELECT protein.sadn, location.id FROM \"PRO19\".protein INNER JOIN \"PRO19\".prot_to_loc ON protein.id = prot_to_loc.fk_prot INNER JOIN \"PRO19\".location on prot_to_loc.fk_loc = location.id WHERE location.id != 7;";
        char command[500];
        sprintf(command, "PGPASSWORD=%s psql -U %s %s -c '%s' > result.txt;",
                ui->txtDBPassword->text().toLocal8Bit().data(),
                ui->txtDBUsername->text().toLocal8Bit().data(),
                ui->txtDBName->text().toLocal8Bit().data(),
                sqlResquest);

        //Envoie de la commande pour la requete au serveur distant
        sshWrite(channel, command);

        sleep(5);

        //Lecture du fichier de résultat de la requete
        scpRead(session);

        //Fermeture de toutes les connexions ssh
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

void MainWindow::scpRead(ssh_session session){
    ssh_scp scp;
    int rc;
    int size, mode;
    char *filename, *buffer;
    scp = ssh_scp_new(session, SSH_SCP_READ, "/home/samuel.mettler/result.txt");
    int fd = open("/home/david/Desktop/HEIG-VD/PRO/heigvd-pro-b-13/PRO_GUI/PRO_GUI/result", O_WRONLY | O_CREAT);
    if(fd == -1){
        std::cout << "Errore when opening de local file" << std::endl;
        exit(-1);
    }

    if (scp == NULL)
    {
      fprintf(stderr, "Error allocating scp session: %s\n",
              ssh_get_error(session));
        exit(SSH_ERROR);
    }
    rc = ssh_scp_init(scp);
    if (rc != SSH_OK)
    {
      fprintf(stderr, "Error initializing scp session: %s\n", ssh_get_error(session));
      ssh_scp_free(scp);
    }

    rc = ssh_scp_pull_request(scp);
    if (rc != SSH_SCP_REQUEST_NEWFILE)
    {
       fprintf(stderr, "Error receiving information about file: %s\n",
               ssh_get_error(session));
       exit(SSH_ERROR);
    }
     size = ssh_scp_request_get_size(scp);
     filename = strdup(ssh_scp_request_get_filename(scp));
     mode = ssh_scp_request_get_permissions(scp);
     printf("Receiving file %s, size %d, permissions 0%o\n",
             filename, size, mode);
     free(filename);
     buffer = (char*)malloc(size);
     if (buffer == NULL)
     {
       fprintf(stderr, "Memory allocation error\n");
       exit(SSH_ERROR);
     }
     ssh_scp_accept_request(scp);

     //Le fichier et lu par bloque
     //La boucler permet de lire tout le fichier
     int r = 0;
     while (r < size) {
         int st = ssh_scp_read(scp, buffer+r, size-r);
         r += st;
     }

     if (rc == SSH_ERROR)
     {
       fprintf(stderr, "Error receiving file data: %s\n",
               ssh_get_error(session));
       free(buffer);
       exit(SSH_ERROR);
     }
     printf("Done\n");
     write(fd, buffer, size);
     free(buffer);
     rc = ssh_scp_pull_request(scp);
     if (rc != SSH_SCP_REQUEST_EOF)
     {
       fprintf(stderr, "Unexpected request: %s\n", ssh_get_error(session));
       exit(SSH_ERROR);
     }

     ssh_scp_close(scp);
     ssh_scp_free(scp);
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

