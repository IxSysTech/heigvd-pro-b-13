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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
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
    QCheckBox *ckbUseSSH;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtSSHPassword;
    QLineEdit *txtSSHUsername;
    QLineEdit *txtSSHHost;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(398, 369);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        txtDBHost = new QLineEdit(centralWidget);
        txtDBHost->setObjectName(QString::fromUtf8("txtDBHost"));
        txtDBHost->setGeometry(QRect(141, 49, 231, 26));
        txtDBName = new QLineEdit(centralWidget);
        txtDBName->setObjectName(QString::fromUtf8("txtDBName"));
        txtDBName->setGeometry(QRect(142, 80, 231, 26));
        txtDBUsername = new QLineEdit(centralWidget);
        txtDBUsername->setObjectName(QString::fromUtf8("txtDBUsername"));
        txtDBUsername->setGeometry(QRect(142, 111, 231, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(22, 55, 101, 18));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(22, 10, 381, 20));
        QFont font1;
        font1.setPointSize(14);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 84, 121, 18));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(21, 114, 121, 18));
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(21, 143, 161, 18));
        label_5->setFont(font);
        txtDBPassword = new QLineEdit(centralWidget);
        txtDBPassword->setObjectName(QString::fromUtf8("txtDBPassword"));
        txtDBPassword->setGeometry(QRect(141, 141, 231, 26));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(12, 300, 361, 26));
        ckbUseSSH = new QCheckBox(centralWidget);
        ckbUseSSH->setObjectName(QString::fromUtf8("ckbUseSSH"));
        ckbUseSSH->setGeometry(QRect(120, 180, 151, 24));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(false);
        label_6->setGeometry(QRect(22, 243, 121, 18));
        label_6->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setEnabled(false);
        label_7->setGeometry(QRect(22, 272, 161, 18));
        label_7->setFont(font);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setEnabled(false);
        label_8->setGeometry(QRect(22, 215, 101, 18));
        label_8->setFont(font);
        txtSSHPassword = new QLineEdit(centralWidget);
        txtSSHPassword->setObjectName(QString::fromUtf8("txtSSHPassword"));
        txtSSHPassword->setEnabled(false);
        txtSSHPassword->setGeometry(QRect(141, 270, 231, 26));
        txtSSHUsername = new QLineEdit(centralWidget);
        txtSSHUsername->setObjectName(QString::fromUtf8("txtSSHUsername"));
        txtSSHUsername->setEnabled(false);
        txtSSHUsername->setGeometry(QRect(141, 240, 231, 26));
        txtSSHHost = new QLineEdit(centralWidget);
        txtSSHHost->setObjectName(QString::fromUtf8("txtSSHHost"));
        txtSSHHost->setEnabled(false);
        txtSSHHost->setGeometry(QRect(141, 209, 231, 26));
        txtSSHHost->setReadOnly(false);
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
        QWidget::setTabOrder(txtDBPassword, ckbUseSSH);
        QWidget::setTabOrder(ckbUseSSH, txtSSHHost);
        QWidget::setTabOrder(txtSSHHost, txtSSHUsername);
        QWidget::setTabOrder(txtSSHUsername, txtSSHPassword);
        QWidget::setTabOrder(txtSSHPassword, btnConnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Host", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Database connection information", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Database name", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Password", nullptr));
        btnConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        ckbUseSSH->setText(QApplication::translate("MainWindow", "Use SSH Connection", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Password", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Host", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        txtSSHHost->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
