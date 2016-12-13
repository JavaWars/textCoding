#ifndef SHIFR_H
#define SHIFR_H

#include <QObject>
#include <QWidget>
#include <QString>

class Shifr
{
public:
    Shifr();
    static QString CezarShifr(QString _inputString,int code);
    static QString HemingShifr(QString _inputString);

};

#endif // SHIFR_H
