#ifndef FORMCEZAR_H
#define FORMCEZAR_H

#include <QWidget>
namespace Ui {
class FormCezar;
}

class FormCezar : public QWidget
{
    Q_OBJECT

public:
    explicit FormCezar(QWidget *parent = 0);
    ~FormCezar();

private slots:
    void on_openDataTextEdit_textChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FormCezar *ui;
};

#endif // FORMCEZAR_H
