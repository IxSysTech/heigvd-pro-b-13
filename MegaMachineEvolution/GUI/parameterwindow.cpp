#include "parameterwindow.h"
#include "ui_parameterwindow.h"

#include <qfiledialog.h>

ParameterWindow::ParameterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParameterWindow)
{
    ui->setupUi(this);
    QStringList mutationModes = {
        "Boundary mutation (BDM)",
        "Single point mutation (SPM)",
        "Uniform mutation (UNM)"
    };
    QStringList selectionModes = {
        "Proportional roulette wheel selection (RWS)",
        "Stochastic universal sampling (SUS)",
        "Classic linear rank-based selection (RNK)",
        "Linear rank-based selection with selective pressure (RSP)",
        "Tournament selection (TNT)",
        "Transform ranking selection (TRS)"
    };
    QStringList crossoverModes = {
        "One point cross-over (P1XO)",
        "Two point cross-over (P2XO)",
        "Uniform cross-over (UXO)"
    };

    ui->cmbMutationMode->addItems(mutationModes);
    ui->cmbMutationMode->setCurrentIndex(1);
    ui->cmbSelectionMode->addItems(selectionModes);
    ui->cmbSelectionMode->setCurrentIndex(2);
    ui->cmbCrossOverMode->addItems(crossoverModes);
    ui->dsbSpRate->setValue(1.5);
    ui->dsbCrossOverRate->setValue(0.9);
    ui->dsbMutationRate->setValue(0.02);
    ui->dsbToleranceRate->setValue(0.0);
    ui->pgbGeneration->setVisible(false);
    ui->lblLogFile->setWordWrap(true);
    ui->sbGenerationNumber->setValue(100);
    ui->sbPopulationSize->setValue(100);
    ui->cbLogMachines->setCheckState(Qt::CheckState::Unchecked);

    ui->LiveState->hide();
    ui->CurrentAnalysis->setText("Analysis 1 of 1");
    ui->CurrentGen->setText("Gen : 0");
    ui->MaxFitness->setText("Max Fitness : 0.0");
    ui->MeanFitness->setText("Mean current Gen : 0.0");

    // connect(this, SIGNAL(incrementPercent(double)), this, SLOT(incrementProgressBar(double)));
}

ParameterWindow::~ParameterWindow()
{
    delete ui;
}

void ParameterWindow::on_btnRun_clicked()
{
    this->setGUIParametersEnabled(false);
    // Showing current state og GA
    ui->LiveState->show();

    // Redirect stdout to logfile
    FILE* myfile;
    logFileLocation += "log.txt";
    std::cout << logFileLocation.toStdString() << std::endl;
    myfile = std::fopen(logFileLocation.toLocal8Bit().data(), "w+");
    int myfileFD = fileno(myfile);

    dup2(myfileFD, 1);

    QEventLoop loop;

    // Task parented to the application so that it
    // will be deleted by the application.
    struct gaParameters gaParam = {
        ui->cmbMutationMode->currentIndex(),
                ui->cmbCrossOverMode->currentIndex(),
                ui->cmbSelectionMode->currentIndex(),
                static_cast<float>(ui->dsbCrossOverRate->value()),
                static_cast<float>(ui->dsbMutationRate->value()),
                static_cast<float>(ui->dsbSpRate->value()),
                ui->sbPopulationSize->value(),
                ui->sbGenerationNumber->value(),
                ui->sbElitePopulationSize->value(),
                static_cast<float>(ui->dsbToleranceRate->value())
    };

    Dispatcher *DISPATCHER = new Dispatcher(
                ui->sbStateNumbers->value(),
                ui->sbMaxAlert->value(),
                gaParam,
                fileNameDataSource,
                ui->cbLogMachines->checkState() == Qt::Checked ? true : false,
                &loop
                );
    QObject::connect(DISPATCHER, SIGNAL(incrementProgress(double)), this, SLOT(incrementProgressBar(double)));
    QObject::connect(DISPATCHER, SIGNAL(sendState(uint,double,double)), this, SLOT(currentState(uint,double,double)));
    QObject::connect(DISPATCHER, SIGNAL(sendAnalysis(uint,uint)), this, SLOT(nextAnalysis(uint,uint)));

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(DISPATCHER, SIGNAL(finished()), &loop, SLOT(quit()));
    this->setGUIParametersEnabled(true);


    // This will run the task from the application event loop.
    QTimer::singleShot(0, DISPATCHER, &Dispatcher::run);

    // Setup progress bar
    ui->pgbGeneration->setVisible(true);
    ui->btnRun->setVisible(false);
    setGUIParametersEnabled(false);
    qApp->processEvents();

    loop.exec();

    setGUIParametersEnabled(true);
    qApp->processEvents();
}

void ParameterWindow::incrementProgressBar(double percent){
    progress += percent;
    ui->pgbGeneration->setValue(progress);
    qApp->processEvents();
}

void ParameterWindow::on_cmbSelectionMode_currentIndexChanged(int index)
{
    if(index == 3) {
        ui->dsbSpRate->setEnabled(true);
    } else {
        ui->dsbSpRate->setEnabled(false);
    }
}

void ParameterWindow::setGUIParametersEnabled(bool value){
    ui->cmbCrossOverMode->setEnabled(value);
    ui->cmbMutationMode->setEnabled(value);
    ui->cmbSelectionMode->setEnabled(value);
    ui->sbElitePopulationSize->setEnabled(value);
    ui->sbGenerationNumber->setEnabled(value);
    ui->sbMaxAlert->setEnabled(value);
    ui->sbPopulationSize->setEnabled(value);
    ui->sbStateNumbers->setEnabled(value);
    ui->dsbCrossOverRate->setEnabled(value);
    ui->dsbMutationRate->setEnabled(value);
    ui->dsbSpRate->setEnabled(value);
    ui->dsbToleranceRate->setEnabled(value);
    ui->cbLogMachines->setEnabled(value);
    ui->browseLog->setEnabled(value);
}

void ParameterWindow::setDataSource(QString fileNameDataSource){
    this->fileNameDataSource = fileNameDataSource;
}

void ParameterWindow::currentState(unsigned int gen, double maxFit, double currentMean) {
    ui->CurrentGen->setText(QString("Gen : %1").arg(gen));
    ui->MaxFitness->setText(QString("Max Fitness : %1").arg(maxFit));
    ui->MeanFitness->setText(QString("Mean current Gen : %1").arg(currentMean));
}

void ParameterWindow::nextAnalysis(unsigned int current, unsigned int total){
    ui->pgbGeneration->setValue(0);
    progress = 0.;
    ui->CurrentAnalysis->setText(QString("Analysis %1 of %2").arg(QString::number(current), QString::number(total)));
}


void ParameterWindow::on_browseLog_clicked()
{
    logFileLocation = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks
                                                        );
    if(logFileLocation != ""){
        logFileLocation += "/";
    }

    ui->lblLogFile->setText("Current log file locataion : \n" + logFileLocation + "log.txt");
    qApp->processEvents();
}

