#include "shifr.h"
#include <QDebug>
#include <QFile>
#include <QByteArray>
Shifr::Shifr()
{

}

QString Shifr::CezarShifr(QString _inputString,int code)
{
    QString result;
    QChar Z='Z';//90
    QChar A='A';//65 min

    QChar zCh='z';//122 max
    QChar aCh='a';//97

    for (int i=0;i<_inputString.size();i++)
    {
        int a=_inputString[i].toLatin1();
        if (((QChar)a).isLower())//a..z
        {


            a+=code;
            if (a>zCh.toLatin1())
            {
                a-=(zCh.toLatin1()-aCh.toLatin1()+1);
            }
            if (a<aCh.toLatin1())
            {
                a+=(zCh.toLatin1()-aCh.toLatin1()+1);
            }

        }
        else//A..Z
        {
            if(((QChar)a).isUpper())
            {
                a+=code;
                if (a>Z.toLatin1())
                {
                    a-=(Z.toLatin1()-A.toLatin1()+1);
                }
                if (a<A.toLatin1())
                {
                    a+=(Z.toLatin1()-A.toLatin1()+1);
                }
            }
        }
        result+=(QChar)a;
    }
    return result;
}

QString Shifr::HemingShifr(QString _inputString)
{
    QString result;
    if (_inputString.size()>0)
    {
        QFile file(_inputString);
        if (file.exists())
        {
            qDebug()<<"file exist";
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug()<<"file not open";
            }
            qDebug()<<"file open";

            //QByteArray blob = file.readAll();
            long long i=0;
            static const int MaxBytesRead = 1;
            while(!file.atEnd()) {
                i++;
                QByteArray blob = file.read(MaxBytesRead);

                //qDebug()<<"data"<<blob.data()<<"\n";
                //qDebug()<<"hex"<<blob.toHex()<<"\n";
                bool ok = false;
                QString binaryNumber = QString::number(blob.toHex().toLongLong(&ok, 16), 2);
                qDebug()<<binaryNumber;
            }
            qDebug()<<"finish"<<i;
        }
    }
    return result;
}
