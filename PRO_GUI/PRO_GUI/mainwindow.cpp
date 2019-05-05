#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <libpq/libpq-fs.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    int lib_ver = PQlibVersion();

        printf("Version of libpq: %d\n", lib_ver);
}

void MainWindow::on_btnConnect_clicked()
{
    //Récupération des informations de connection pour la base de données
    std::string dbHost = ui->txtDBHost->text().toStdString();
    std::string dbName = ui->txtDBName->text().toStdString();
    std::string dbUsername = ui->txtDBUsername->text().toStdString();
    std::string dbPassword = ui->txtDBPassword->text().toStdString();

    if(ui->ckbUseSSH->isChecked()){
        int rc = 0;
        //int verbosity = SSH_LOG_PROTOCOL;

        //Création de l'objet SSH
        ssh_session session = ssh_new();
        if (session == NULL){ exit(-1); }

        //Spécification du hostname ainsi que du user pour la connection
        ssh_options_set(session, SSH_OPTIONS_HOST, ui->txtSSHHost->text().toLocal8Bit().data());
        ssh_options_set(session, SSH_OPTIONS_USER, ui->txtSSHPassword->text().toLocal8Bit().data());
        //ssh_options_set(ssh_Connect, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);

        rc = ssh_connect(session);
        if (rc != SSH_OK){
            fprintf(stderr, "Error: %s\n", ssh_get_error(session));
            ssh_free(session);
            exit(-1);
        }

        rc = ssh_userauth_password(session, NULL, /*ui->txtSSHUsername->text().toStdString().c_str()*/ "MdpHardCodéf");
        if (rc != SSH_AUTH_SUCCESS){
            fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(session));
            ssh_disconnect(session);
            ssh_free(session);
            exit(-1);
        }


        ssh_disconnect(session);
        ssh_free(session);
    }
}
