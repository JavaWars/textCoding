#ifndef FORMENIGMA_H
#define FORMENIGMA_H

#include <QWidget>
#include "enigma.h"
namespace Ui {
class FormEnigma;
}

class FormEnigma : public QWidget
{
    Q_OBJECT

public:
    explicit FormEnigma(QWidget *parent = 0);
    ~FormEnigma();

private slots:
    void on_OpenFile_PB_clicked();
    void on_SHIFR_PB_clicked();

private:
    Ui::FormEnigma *ui;
    Enigma *enigma;

    void clearSettings();
};

#endif // FORMENIGMA_H
