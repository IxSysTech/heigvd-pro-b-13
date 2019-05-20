#ifndef PARAMETERWINDOW_H
#define PARAMETERWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "../dispatcher.h"
#include <unistd.h>
#include <QTimer>
#include <QStandardPaths>

namespace Ui {
class ParameterWindow;
}

class ParameterWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief ParameterWindow : Default constructor
     * @param parent
     */
    explicit ParameterWindow(QWidget *parent = nullptr);
    ~ParameterWindow();

    /**
     * @brief setDataSource : Set the path of the data file
     * @param fileNameDataSource : path of the data file
     */
    void setDataSource(QString fileNameDataSource);

private slots:

    /**
     * @brief on_btnRun_clicked : Action of the button Run that start the application work
     */
    void on_btnRun_clicked();

    /**
     * @brief on_cmbSelectionMode_currentIndexChanged : Action of the Combobox of the Selection mode that enable or disable GUI according to the option selected
     * @param index : index of the option selected
     */
    void on_cmbSelectionMode_currentIndexChanged(int index);

    /**
     * @brief on_browseLog_clicked : Action of the button Browse that allow the user to choose where to save the log file
     */
    void on_browseLog_clicked();

public slots:
    /**
     * @brief incrementProgressBar : Allow to increment the progress bar
     * @param percent : percent of the progress bar
     */
    void incrementProgressBar(double percent);

    /**
     * @brief currentState : Set the value of the current state that will be displayed to the user
     * @param gen : Actual generation
     * @param maxFit : Value of the maxmium fitness
     * @param currentMean : mean of the current generation
     */
    void currentState(unsigned int gen, double maxFit, double currentMean);

    /**
     * @brief nextAnalysis : reset the GUI to be ready to run the next analysis
     * @param current : number of the analysis
     * @param total : number total of analysis
     */
    void nextAnalysis(unsigned int current, unsigned int total);

private:
    /**
     * @brief setGUIEnabled : Enable or disable the UI
     * @param value bool
     */
    void setGUIParametersEnabled(bool value);

    Ui::ParameterWindow *ui;
    double progress = 0.0;                                                                                              //Value of the progress bar
    QString fileNameDataSource;                                                                                         //File where the application will get datas
    QString logFileLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);      //Log file location

signals:
    /**
     * @brief incrementPercent : Signal use to increment the progress bar
     */
    void incrementPercent(double);
};

#endif // PARAMETERWINDOW_H
