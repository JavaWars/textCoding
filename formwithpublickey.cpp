#include "formwithpublickey.h"
#include "ui_formwithpublickey.h"
#include <QFileDialog>
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
    //rsa->setKey(199,23,265);
    QString s2=fileName;
    s2=s2.insert(fileName.size()-4,"_new");
    rsa->RsaShifrFile(fileName,s2);
}

void FormWithPublicKey::on_UnShifr_PB_clicked()
{
    QString inputFileName=ui->fileName_LE->text();
    QString outputFileName=inputFileName;
    outputFileName.insert(outputFileName.size()-4,"Unshifred");
    rsa->RsaUnshifrFile(inputFileName,outputFileName);
}
