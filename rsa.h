#ifndef RSA_H
#define RSA_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QByteArray>

class Rsa
{
private:
    unsigned int n,e,d;

    int sundaram(int n);
    int gcd(int a, int b);
public:
    Rsa();
    void PrintKey();
    void getKey();
    void setKey(int _e,int _d,int _n);
    void CreateKey();

    void RsaShifrFile(QString _inputFileName,QString _outputFileName);
    void RsaUnshifrFile(QString _fileName,QString _outputFileName);
};

#endif // RSA_H
