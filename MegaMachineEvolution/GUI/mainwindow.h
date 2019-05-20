#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <string>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <algorithm>
#include "parameterwindow.h"

#define MAX_XFER_BUF_SIZE 32768
#define ERROR_MESSAGE "FATAL"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();

    void on_btnBrowse_clicked();

    void on_btnContinue_clicked();

private:
    ParameterWindow p;
    int sshConnect(ssh_session *session);
    int scpRead(ssh_session session);
    int channelConnect(ssh_session session, ssh_channel &channel);
    int sshWrite(ssh_channel channel, char* command);
    void setGUIEnabled(bool value);
    Ui::MainWindow *ui;

    bool fileSelected = false;
    QString fileDataSource = "result";
};

#endif // MAINWINDOW_H
