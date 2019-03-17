#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cezarForm=new FormCezar();
    enigmaForm=new FormEnigma();
    pubKeyForm=new FormWithPublicKey();

    ui->stackedWidget->addWidget(cezarForm);
    ui->stackedWidget->addWidget(enigmaForm);
    ui->stackedWidget->addWidget(pubKeyForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_action_2_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_action_3_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}
