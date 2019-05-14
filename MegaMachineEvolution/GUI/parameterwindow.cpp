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

    connect(this, SIGNAL(incrementPercent(double)), this, SLOT(incrementProgressBar(double)));
}

ParameterWindow::~ParameterWindow()
{
    delete ui;
}

void ParameterWindow::on_btnRun_clicked()
{
    FILE* myfile;
    myfile = std::fopen("test.txt", "w");
    int myfileFD = fileno(myfile);

    dup2(myfileFD, 1);

    QEventLoop loop;

    // Task parented to the application so that it
    // will be deleted by the application.
    //Task *task = new Task(&a);
    Dispatcher *DISPATCHER = new Dispatcher(ui->cmbCrossOverMode->currentIndex(), ui->cmbSelectionMode->currentIndex(), ui->cmbMutationMode->currentIndex(), ui->dsbCrossOverRate->value(), ui->dsbMutationRate->value(), ui->dsbSpRate->value(), ui->dsbToleranceRate->value(), ui->sbStateNumbers->value(), ui->sbPopulationSize->value(), ui->sbMaxAlert->value(), ui->sbGenerationNumber->value(), &loop);

    // This will cause the application to exit when
    // the task signals finished.
     //QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
     QObject::connect(DISPATCHER, SIGNAL(finished()), &loop, SLOT(quit()));

    // This will run the task from the application event loop.
    //QTimer::singleShot(0, task, SLOT(run()));

    //QObject::connect(task, &Task::finished, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    //QTimer::singleShot(0, task, &Task::run);
    QTimer::singleShot(0, DISPATCHER, &Dispatcher::run);

    // Setup progress bar
    ui->pgbGeneration->setVisible(true);
    ui->btnRun->setVisible(false);
    ui->pgbGeneration->setMaximum(ui->sbGenerationNumber->value());
    qApp->processEvents();

    loop.exec();
}

void ParameterWindow::incrementProgressBar(double percent){
    progress += percent;
    ui->pgbGeneration->setValue(progress);
    qApp->processEvents();
}
