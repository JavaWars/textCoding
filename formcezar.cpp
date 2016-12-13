#include "formcezar.h"
#include "ui_formcezar.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "shifr.h"

FormCezar::FormCezar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCezar)
{
    ui->setupUi(this);
}

FormCezar::~FormCezar()
{
    delete ui;
}

void FormCezar::on_openDataTextEdit_textChanged()
{
    QString fname = ui->openDataTextEdit->toPlainText();
    if (fname.size()!=0)
    {
        fname.replace(0,8,"");
        qDebug()<<"text changed"<<fname;

        QFile file(fname);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"file not open!";
            return;
        }
        qDebug()<<"file open!";
        QTextStream in(&file);
        QString line = in.readLine();
        QString result;
        while (!line.isNull()) {
            result+=line;
            line=in.readLine();
        }
        ui->openDataTextEdit->setText(result);
    }
}

void FormCezar::on_pushButton_clicked()
{
    ui->closeDataTextEdit->setText(Shifr::CezarShifr(ui->openDataTextEdit->toPlainText(),ui->spinBox->value()));
}

void FormCezar::on_pushButton_2_clicked()
{
    //QString s("C:/Users/Pavel/Desktop/text.txt");
    ui->closeDataTextEdit->setText(Shifr::HemingShifr(ui->openDataTextEdit->toPlainText()));
}
