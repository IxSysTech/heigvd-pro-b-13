#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <libpq-fe.h>
#include <fcntl.h>

#define MAX_XFER_BUF_SIZE 16384

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
    void on_ckbUseSSH_clicked();

    void on_btnConnect_clicked();

private:
    ssh_session sshConnect();
    void scpRead(ssh_session session);
    ssh_channel channelConnect(ssh_session session);
    void sshWrite(ssh_channel channel, char* command);
    void sshRead(ssh_channel channel);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
