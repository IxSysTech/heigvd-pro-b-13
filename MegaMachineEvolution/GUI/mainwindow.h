#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <string>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include "parameterwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow : Default constructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    /**
     * @brief on_btnConnect_clicked : Action of the button Connect that connect to the Database
     */
    void on_btnConnect_clicked();

    /**
     * @brief on_btnBrowse_clicked : Action of the button Browse that permit to choose the local file data
     */
    void on_btnBrowse_clicked();

    /**
     * @brief on_btnContinue_clicked : Action of the button Continue that permit to continue after the local file data has been selected
     */
    void on_btnContinue_clicked();

private:
    /**
     * @brief p : Window that contain all the parameters of the GA
     */
    ParameterWindow p;

    /**
     * @brief sshConnect : Create a ssh connection to the remote host
     * @param session : The session that will be established beetween the local and remote machine
     * @return int : SSH_OK if there is no error or SSH_ERROR if there is an error
     */
    int sshConnect(ssh_session *session);

    /**
     * @brief scpRead : Allow to copie a remote file to the local machine
     * @param session : The session established beetween the local and remot machine
     * @param remoteFilePath : Path of the remote file to copie
     * @return int : SSH_OK if there is no error or SSH_ERROR if there is an error
     */
    int scpRead(ssh_session session, QString remoteFilePath);

    /**
     * @brief scpRead
     * @param session
     * @return int
     */

    /**
     * @brief channelConnect : Connect a channel to the remote host to get a shell bash
     * @param session : The session established beetween the local and remot machine
     * @param channel : The channel that will be connected to the remote shell
     * @return int : SSH_OK if there is no error or SSH_ERROR if there is an error
     */
    int channelConnect(ssh_session session, ssh_channel &channel);

    /**
     * @brief sshWrite : Allow to send a bash command to te remote host
     * @param channel : Channel connected to the remote host
     * @param command : Commande to send to the remote host
     * @return int : SSH_OK if there is no error or SSH_ERROR if there is an error
     */
    int sshWrite(ssh_channel channel, char* command);

    /**
     * @brief setGUIEnabled : Enable or disable the UI
     * @param value bool
     */
    void setGUIEnabled(bool value);

    Ui::MainWindow *ui;
    bool fileSelected = false;              //Bool that indicat if a local file has been selected
    QString fileDataSource = "result";      //File where the application will get datas
};

#endif // MAINWINDOW_H
