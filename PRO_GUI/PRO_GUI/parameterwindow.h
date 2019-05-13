#ifndef PARAMETERWINDOW_H
#define PARAMETERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ParameterWindow;
}

class ParameterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParameterWindow(QWidget *parent = nullptr);
    ~ParameterWindow();

private:
    Ui::ParameterWindow *ui;
};

#endif // PARAMETERWINDOW_H
