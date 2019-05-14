/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *txtDBHost;
    QLineEdit *txtDBName;
    QLineEdit *txtDBUsername;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *txtDBPassword;
    QPushButton *btnConnect;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtSSHPassword;
    QLineEdit *txtSSHUsername;
    QLineEdit *txtSSHHost;
    QLabel *label_9;
    QLabel *lblInfo;
    QProgressBar *pgbDownload;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(460, 410);
        MainWindow->setMinimumSize(QSize(460, 410));
        MainWindow->setMaximumSize(QSize(460, 410));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        txtDBHost = new QLineEdit(centralWidget);
        txtDBHost->setObjectName(QString::fromUtf8("txtDBHost"));
        txtDBHost->setGeometry(QRect(220, 49, 231, 26));
        txtDBName = new QLineEdit(centralWidget);
        txtDBName->setObjectName(QString::fromUtf8("txtDBName"));
        txtDBName->setGeometry(QRect(221, 80, 231, 26));
        txtDBUsername = new QLineEdit(centralWidget);
        txtDBUsername->setObjectName(QString::fromUtf8("txtDBUsername"));
        txtDBUsername->setGeometry(QRect(221, 111, 231, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(22, 55, 101, 18));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(22, 10, 431, 20));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 84, 191, 18));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(21, 114, 191, 18));
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(21, 143, 161, 18));
        label_5->setFont(font);
        txtDBPassword = new QLineEdit(centralWidget);
        txtDBPassword->setObjectName(QString::fromUtf8("txtDBPassword"));
        txtDBPassword->setGeometry(QRect(220, 141, 231, 26));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(12, 300, 441, 26));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(true);
        label_6->setGeometry(QRect(22, 243, 121, 18));
        label_6->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setEnabled(true);
        label_7->setGeometry(QRect(22, 272, 161, 18));
        label_7->setFont(font);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setEnabled(true);
        label_8->setGeometry(QRect(22, 215, 101, 18));
        label_8->setFont(font);
        txtSSHPassword = new QLineEdit(centralWidget);
        txtSSHPassword->setObjectName(QString::fromUtf8("txtSSHPassword"));
        txtSSHPassword->setEnabled(true);
        txtSSHPassword->setGeometry(QRect(220, 270, 231, 26));
        txtSSHUsername = new QLineEdit(centralWidget);
        txtSSHUsername->setObjectName(QString::fromUtf8("txtSSHUsername"));
        txtSSHUsername->setEnabled(true);
        txtSSHUsername->setGeometry(QRect(220, 240, 231, 26));
        txtSSHHost = new QLineEdit(centralWidget);
        txtSSHHost->setObjectName(QString::fromUtf8("txtSSHHost"));
        txtSSHHost->setEnabled(true);
        txtSSHHost->setGeometry(QRect(220, 209, 231, 26));
        txtSSHHost->setReadOnly(false);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 179, 441, 20));
        label_9->setFont(font1);
        lblInfo = new QLabel(centralWidget);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));
        lblInfo->setGeometry(QRect(10, 334, 441, 20));
        lblInfo->setLayoutDirection(Qt::LeftToRight);
        lblInfo->setAlignment(Qt::AlignCenter);
        pgbDownload = new QProgressBar(centralWidget);
        pgbDownload->setObjectName(QString::fromUtf8("pgbDownload"));
        pgbDownload->setGeometry(QRect(11, 302, 441, 21));
        pgbDownload->setValue(0);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(txtDBHost, txtDBName);
        QWidget::setTabOrder(txtDBName, txtDBUsername);
        QWidget::setTabOrder(txtDBUsername, txtDBPassword);
        QWidget::setTabOrder(txtDBPassword, txtSSHHost);
        QWidget::setTabOrder(txtSSHHost, txtSSHUsername);
        QWidget::setTabOrder(txtSSHUsername, txtSSHPassword);
        QWidget::setTabOrder(txtSSHPassword, btnConnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Mega Machine Evolution - Connection", nullptr));
        label->setText(QApplication::translate("MainWindow", "Host", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Database connection information", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Database name", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Password", nullptr));
        btnConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Password", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Host", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        txtSSHHost->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        label_9->setText(QApplication::translate("MainWindow", "SSH connection information", nullptr));
        lblInfo->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
