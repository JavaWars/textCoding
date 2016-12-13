#ifndef FORMWITHPUBLICKEY_H
#define FORMWITHPUBLICKEY_H

#include <QWidget>

#include "rsa.h"
namespace Ui {
class FormWithPublicKey;
}

class FormWithPublicKey : public QWidget
{
    Q_OBJECT

public:
    explicit FormWithPublicKey(QWidget *parent = 0);
    ~FormWithPublicKey();

private slots:
    void on_Open_PB_clicked();

    void on_UnShifr_PB_clicked();

private:
    Ui::FormWithPublicKey *ui;
    Rsa *rsa;
};

#endif // FORMWITHPUBLICKEY_H
