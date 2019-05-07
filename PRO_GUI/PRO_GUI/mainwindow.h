#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <libpq-fe.h>

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
    ssh_session sshConnect(char* hostname, char* username, char* password);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
