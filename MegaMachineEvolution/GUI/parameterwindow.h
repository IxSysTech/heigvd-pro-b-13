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

private slots:
    void on_btnRun_clicked();
    void setGUIEnabled(bool value);
    void on_cmbSelectionMode_currentIndexChanged(int index);

public slots:
    void incrementProgressBar(double percent);

private:
    Ui::ParameterWindow *ui;
    double progress = 0.0;


signals:
    void incrementPercent(double);
};

#endif // PARAMETERWINDOW_H
