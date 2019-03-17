#include "formwithpublickey.h"
#include "ui_formwithpublickey.h"
#include <QFileDialog>
#include <QMessageBox>
FormWithPublicKey::FormWithPublicKey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWithPublicKey)
{
    ui->setupUi(this);
    rsa=new Rsa();
    rsa->CreateKey();
}

FormWithPublicKey::~FormWithPublicKey()
{
    delete ui;
}

void FormWithPublicKey::on_Open_PB_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home", tr("Files (*.*)"));
    ui->fileName_LE->setText(fileName);
}

void FormWithPublicKey::on_UnShifr_PB_clicked()
{
    QString inputFileName=ui->fileName_LE->text();
    QString outputFileName=inputFileName;
    outputFileName.insert(outputFileName.size()-4,"Unshifred");
    bool ok,ok2;
    int d=ui->key1_LE->text().toInt(&ok),n=ui->key2_LE->text().toInt(&ok2);
    if ( ok && ok2 )
    {
        rsa->setKey(0,d,n);
        rsa->RsaUnshifrFile(inputFileName,outputFileName);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Incorrect key");
        msgBox.exec();
    }
}

void FormWithPublicKey::on_Shifr_PB_clicked()
{
    QString inputFileName=ui->fileName_LE->text();
    QString outputFileName=inputFileName;
    outputFileName.insert(outputFileName.size()-4,"Shifred");
    rsa->RsaShifrFile(inputFileName,outputFileName);

    ui->key1_LE->setText(QString::number(rsa->getD()));
    ui->key2_LE->setText(QString::number(rsa->getN()));
}
