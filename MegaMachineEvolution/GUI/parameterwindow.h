#ifndef PARAMETERWINDOW_H
#define PARAMETERWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "../dispatcher.h"
#include <unistd.h>
#include <QTimer>

namespace Ui {
class ParameterWindow;
}

class ParameterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParameterWindow(QWidget *parent = nullptr);
    ~ParameterWindow();

    void setDataSource(QString fileNameDataSource);

private slots:
    void on_btnRun_clicked();
    void setGUIParametersEnabled(bool value);
    void on_cmbSelectionMode_currentIndexChanged(int index);

    void on_browseLog_clicked();

public slots:
    void incrementProgressBar(double percent);
    void currentState(unsigned int gen, double maxFit, double currentMean);
    void nextAnalysis(unsigned int current, unsigned int total);

private:
    Ui::ParameterWindow *ui;
    double progress = 0.0;
    QString fileNameDataSource;
    QString logFileLocation = "";

signals:
    void incrementPercent(double);
};

#endif // PARAMETERWINDOW_H
