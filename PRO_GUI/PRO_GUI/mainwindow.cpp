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
}

void MainWindow::on_btnConnect_clicked()
{
    if(ui->ckbUseSSH->isChecked()){
        //Valeur pour vérifié la connection SSH
        int rc = 0;

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

        PGconn *conn;
        char connInfo[100];

        sprintf(connInfo, "user=%s password=%s dbname=%s host=%s port=%d",
                ui->txtDBUsername->text().toLocal8Bit().data(),
                ui->txtDBPassword->text().toLocal8Bit().data(),
                ui->txtDBName->text().toLocal8Bit().data(),
                ui->txtDBHost->text().toLocal8Bit().data(),
                5432);

        std:: cout << connInfo << std::endl;

        conn = PQconnectdb(connInfo);

        if (PQstatus(conn) != CONNECTION_OK)
        {
            fprintf(stderr, "Connection to database failed: %s",
                    PQerrorMessage(conn));
            //exit_nicely(conn);
        }


        //Fermeture de la session
        ssh_disconnect(session);
        ssh_free(session);
    }
}

