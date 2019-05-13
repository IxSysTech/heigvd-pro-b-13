#ifndef PARAMETERWINDOW_H
#define PARAMETERWINDOW_H

#include <QMainWindow>
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

private:
    Ui::ParameterWindow *ui;
};

#endif // PARAMETERWINDOW_H
