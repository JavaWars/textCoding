#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formcezar.h"
#include "formenigma.h"
#include "formwithpublickey.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    FormCezar *cezarForm;
    FormEnigma * enigmaForm;
    FormWithPublicKey *pubKeyForm;
};

#endif // MAINWINDOW_H
