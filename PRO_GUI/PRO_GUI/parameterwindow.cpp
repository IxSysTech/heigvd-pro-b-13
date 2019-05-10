#include "parameterwindow.h"
#include "ui_parameterwindow.h"

ParameterWindow::ParameterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParameterWindow)
{
    ui->setupUi(this);

    ui->cmbMutationMode->addItems({
                                      "Boundary mutation (BDM)",
                                      "Single point mutation (BDM)",
                                      "Uniform mutation (UNM)"});
    ui->cmbSelectionMode->addItems({
                                       "Proportional roulette wheel selection (RWS)",
                                       "Stochastic universal sampling (SUS)",
                                       "Classic linear rank-based selection (RNK)",
                                       "Linear rank-based selection with selective pressure (RSP)",
                                       "Tournament selection (TNT)",
                                       "Transform ranking selection (TRS)"
                                   });
    ui->cmbCrossOverMode->addItems({
                                       "One point cross-over (P1XO)",
                                       "Two point cross-over (P2XO)",
                                       "Uniform cross-over (UXO)"
                                   });
    ui->dsbSpRate->setValue(1.5);
    ui->dsbCrossOverRate->setValue(0.5);
    ui->dsbMutationRate->setValue(0.05);
    ui->dsbToleranceRate->setValue(0.0);
}

ParameterWindow::~ParameterWindow()
{
    delete ui;
}
