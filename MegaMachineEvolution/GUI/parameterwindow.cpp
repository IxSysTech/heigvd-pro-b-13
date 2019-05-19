#include "parameterwindow.h"
#include "ui_parameterwindow.h"

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
    ui->cmbSelectionMode->addItems(selectionModes);
    ui->cmbCrossOverMode->addItems(crossoverModes);
    ui->dsbSpRate->setValue(1.5);
    ui->dsbCrossOverRate->setValue(0.5);
    ui->dsbMutationRate->setValue(0.05);
    ui->dsbToleranceRate->setValue(0.0);
    ui->pgbGeneration->setVisible(false);
    ui->sbGenerationNumber->setValue(100);
    ui->sbPopulationSize->setValue(100);
    ui->cbLogMachines->setCheckState(Qt::CheckState::Unchecked);

    // connect(this, SIGNAL(incrementPercent(double)), this, SLOT(incrementProgressBar(double)));
}

ParameterWindow::~ParameterWindow()
{
    delete ui;
}

void ParameterWindow::on_btnRun_clicked()
{
    this->setGUIEnabled(false);
    FILE* myfile;
    myfile = std::fopen("log.txt", "w");
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
    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(DISPATCHER, SIGNAL(finished()), &loop, SLOT(quit()));
    this->setGUIEnabled(true);


    // This will run the task from the application event loop.
    QTimer::singleShot(0, DISPATCHER, &Dispatcher::run);

    // Setup progress bar
    ui->pgbGeneration->setVisible(true);
    ui->btnRun->setVisible(false);
    ui->pgbGeneration->setMaximum(ui->sbGenerationNumber->value());
    setGUIEnabled(false);
    qApp->processEvents();

    loop.exec();

    setGUIEnabled(true);
    qApp->processEvents();
}

void ParameterWindow::incrementProgressBar(double percent){
    QTextStream out(stdout);
    out << "Signal received " << percent << endl;
    progress += percent;
    ui->pgbGeneration->setValue(progress);
    qApp->processEvents();
}

void ParameterWindow::on_cmbSelectionMode_currentIndexChanged(int index)
{
    if(index == 3){
        ui->dsbSpRate->setEnabled(true);
    } else {
        ui->dsbSpRate->setEnabled(false);
    }
}

void ParameterWindow::setGUIEnabled(bool value){
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
}

void ParameterWindow::setDataSource(QString fileNameDataSource){
    this->fileNameDataSource = fileNameDataSource;
}

