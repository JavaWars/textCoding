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
    enigma->SetKey(ui->RotorSetting1_CB->currentText().toInt(),
                   ui->RotorSetting2_CB->currentText().toInt(),
                   ui->RotorSetting3_CB->currentText().toInt(),
                   ui->ReflectorSetting_CB->currentText()[0].unicode()-A.unicode()+1);

    enigma->SetRotorsStartPos(ui->RotorStartPos1_CB->currentText()[1].unicode()-A.unicode(),
                              ui->RotorStartPos2_CB->currentText()[1].unicode()-A.unicode(),
                              ui->RotorStartPos3_CB->currentText()[1].unicode()-A.unicode());

    QString inputFileName=ui->FilePath_LE->text();
    QString outputFileName=inputFileName;
    outputFileName.insert(outputFileName.size()-4,"Shifred");
    enigma->Shifr(inputFileName,outputFileName);

}
