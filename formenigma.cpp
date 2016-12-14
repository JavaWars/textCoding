#include "formenigma.h"
#include "ui_formenigma.h"
#include <QFileDialog>
FormEnigma::FormEnigma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEnigma)
{
    ui->setupUi(this);
    enigma=new Enigma();
    clearSettings();

    //test setting
    ui->FilePath_LE->setText("C:/Users/Pavel/Desktop/test enigma.txt");
    ui->RotorStartPos3_CB->setCurrentIndex(2);
    ui->RotorStartPos2_CB->setCurrentIndex(21);
    ui->RotorStartPos1_CB->setCurrentIndex(16);

    ui->RotorSetting1_CB->setCurrentIndex(0);
    ui->RotorSetting2_CB->setCurrentIndex(1);
    ui->RotorSetting3_CB->setCurrentIndex(2);
}

FormEnigma::~FormEnigma()
{
    delete ui;
}

void FormEnigma::clearSettings()
{
    ui->RotorStartPos1_CB->addItems(Enigma::alphabet());
    ui->RotorStartPos2_CB->addItems(Enigma::alphabet());
    ui->RotorStartPos3_CB->addItems(Enigma::alphabet());

    ui->RotorSetting1_CB->addItems(Enigma::Rotors());
    ui->RotorSetting2_CB->addItems(Enigma::Rotors());
    ui->RotorSetting3_CB->addItems(Enigma::Rotors());

    ui->ReflectorSetting_CB->addItems(Enigma::Reflectors());
    ui->EnigmaProgress->setValue(0);
}

void FormEnigma::on_OpenFile_PB_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open Image"), "/home", tr("Files (*.*)"));
    ui->FilePath_LE->setText(fileName);
}

void FormEnigma::on_SHIFR_PB_clicked()
{
    QChar A('A');
    enigma->SetKey(ui->RotorSetting1_CB->currentText().toInt()-1,
                   ui->RotorSetting2_CB->currentText().toInt()-1,
                   ui->RotorSetting3_CB->currentText().toInt()-1,
                   ui->ReflectorSetting_CB->currentText()[0]);


    enigma->SetRotorsStartPos(ui->RotorStartPos1_CB->currentText()[0].unicode()-A.unicode()+1,
                              ui->RotorStartPos2_CB->currentText()[0].unicode()-A.unicode()+1,
                              ui->RotorStartPos3_CB->currentText()[0].unicode()-A.unicode()+1);
    qDebug()<<ui->RotorStartPos3_CB->currentText()[0].unicode()-A.unicode();

    QString inputFileName=ui->FilePath_LE->text();
    QString outputFileName=inputFileName;
    outputFileName.insert(outputFileName.size()-4,"Shifred");
    enigma->Shifr(inputFileName,outputFileName);

}
