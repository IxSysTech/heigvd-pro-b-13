/********************************************************************************
** Form generated from reading UI file 'parameterwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERWINDOW_H
#define UI_PARAMETERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *cmbSelectionMode;
    QComboBox *cmbCrossOverMode;
    QComboBox *cmbMutationMode;
    QDoubleSpinBox *dsbCrossOverRate;
    QDoubleSpinBox *dsbMutationRate;
    QDoubleSpinBox *dsbSpRate;
    QDoubleSpinBox *dsbToleranceRate;
    QLabel *label_5;
    QLabel *label_10;
    QSpinBox *sbStateNumbers;
    QPushButton *btnRun;
    QSpinBox *sbGenerationNumber;
    QLabel *label_11;
    QLabel *label_13;
    QSpinBox *sbPopulationSize;
    QLabel *label_12;
    QSpinBox *sbMaxAlert;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ParameterWindow)
    {
        if (ParameterWindow->objectName().isEmpty())
            ParameterWindow->setObjectName(QString::fromUtf8("ParameterWindow"));
        ParameterWindow->resize(700, 500);
        ParameterWindow->setMinimumSize(QSize(700, 500));
        ParameterWindow->setMaximumSize(QSize(700, 500));
        centralwidget = new QWidget(ParameterWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 4, 351, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 43, 191, 18));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 73, 191, 18));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 104, 191, 18));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 133, 191, 18));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 195, 191, 18));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 165, 191, 18));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 224, 191, 18));
        cmbSelectionMode = new QComboBox(centralwidget);
        cmbSelectionMode->setObjectName(QString::fromUtf8("cmbSelectionMode"));
        cmbSelectionMode->setGeometry(QRect(220, 40, 461, 26));
        cmbCrossOverMode = new QComboBox(centralwidget);
        cmbCrossOverMode->setObjectName(QString::fromUtf8("cmbCrossOverMode"));
        cmbCrossOverMode->setGeometry(QRect(220, 70, 461, 26));
        cmbMutationMode = new QComboBox(centralwidget);
        cmbMutationMode->setObjectName(QString::fromUtf8("cmbMutationMode"));
        cmbMutationMode->setGeometry(QRect(220, 100, 461, 26));
        dsbCrossOverRate = new QDoubleSpinBox(centralwidget);
        dsbCrossOverRate->setObjectName(QString::fromUtf8("dsbCrossOverRate"));
        dsbCrossOverRate->setGeometry(QRect(220, 130, 121, 27));
        dsbCrossOverRate->setMaximum(1.000000000000000);
        dsbCrossOverRate->setSingleStep(0.100000000000000);
        dsbMutationRate = new QDoubleSpinBox(centralwidget);
        dsbMutationRate->setObjectName(QString::fromUtf8("dsbMutationRate"));
        dsbMutationRate->setGeometry(QRect(220, 160, 121, 27));
        dsbMutationRate->setMaximum(1.000000000000000);
        dsbMutationRate->setSingleStep(0.100000000000000);
        dsbSpRate = new QDoubleSpinBox(centralwidget);
        dsbSpRate->setObjectName(QString::fromUtf8("dsbSpRate"));
        dsbSpRate->setGeometry(QRect(220, 190, 121, 27));
        dsbToleranceRate = new QDoubleSpinBox(centralwidget);
        dsbToleranceRate->setObjectName(QString::fromUtf8("dsbToleranceRate"));
        dsbToleranceRate->setGeometry(QRect(220, 220, 121, 27));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 320, 351, 31));
        label_5->setFont(font);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 360, 191, 18));
        sbStateNumbers = new QSpinBox(centralwidget);
        sbStateNumbers->setObjectName(QString::fromUtf8("sbStateNumbers"));
        sbStateNumbers->setGeometry(QRect(220, 355, 121, 27));
        sbStateNumbers->setMinimum(1);
        sbStateNumbers->setValue(4);
        btnRun = new QPushButton(centralwidget);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));
        btnRun->setGeometry(QRect(20, 430, 661, 26));
        sbGenerationNumber = new QSpinBox(centralwidget);
        sbGenerationNumber->setObjectName(QString::fromUtf8("sbGenerationNumber"));
        sbGenerationNumber->setGeometry(QRect(220, 250, 121, 27));
        sbGenerationNumber->setMinimum(1);
        sbGenerationNumber->setMaximum(1000);
        sbGenerationNumber->setValue(1);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 254, 191, 18));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 285, 191, 18));
        sbPopulationSize = new QSpinBox(centralwidget);
        sbPopulationSize->setObjectName(QString::fromUtf8("sbPopulationSize"));
        sbPopulationSize->setGeometry(QRect(220, 281, 121, 27));
        sbPopulationSize->setMinimum(1);
        sbPopulationSize->setMaximum(1000);
        sbPopulationSize->setValue(1);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 390, 191, 18));
        sbMaxAlert = new QSpinBox(centralwidget);
        sbMaxAlert->setObjectName(QString::fromUtf8("sbMaxAlert"));
        sbMaxAlert->setGeometry(QRect(220, 385, 121, 27));
        sbMaxAlert->setMinimum(1);
        sbMaxAlert->setMaximum(1000);
        sbMaxAlert->setValue(1);
        ParameterWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ParameterWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 23));
        ParameterWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ParameterWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ParameterWindow->setStatusBar(statusbar);

        retranslateUi(ParameterWindow);

        QMetaObject::connectSlotsByName(ParameterWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ParameterWindow)
    {
        ParameterWindow->setWindowTitle(QApplication::translate("ParameterWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("ParameterWindow", "Genetic algorithme parameters", nullptr));
        label_2->setText(QApplication::translate("ParameterWindow", "Selection mode", nullptr));
        label_3->setText(QApplication::translate("ParameterWindow", "Cross-over mode", nullptr));
        label_4->setText(QApplication::translate("ParameterWindow", "Mutation mode", nullptr));
        label_6->setText(QApplication::translate("ParameterWindow", "Cross-over rate", nullptr));
        label_7->setText(QApplication::translate("ParameterWindow", "Selective pressure rate", nullptr));
        label_8->setText(QApplication::translate("ParameterWindow", "Mutation rate", nullptr));
        label_9->setText(QApplication::translate("ParameterWindow", "Tolerance rate", nullptr));
        label_5->setText(QApplication::translate("ParameterWindow", "State machine parameters", nullptr));
        label_10->setText(QApplication::translate("ParameterWindow", "State numbers", nullptr));
        btnRun->setText(QApplication::translate("ParameterWindow", "Run Simulation", nullptr));
        label_11->setText(QApplication::translate("ParameterWindow", "Number of generation", nullptr));
        label_13->setText(QApplication::translate("ParameterWindow", "Population size", nullptr));
        label_12->setText(QApplication::translate("ParameterWindow", "Max alert", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterWindow: public Ui_ParameterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERWINDOW_H
