#include "rsa.h"

#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <QDataStream>
Rsa::Rsa()
{

}

void Rsa::setKey(int _e, int _d, int _n)
{
    e=_e;
    d=_d;
    n=_n;
    PrintKey();
}

void Rsa::RsaShifrFile(QString _inputFileName, QString _outputFileName)
{
    qDebug()<<_inputFileName<<" "<<_outputFileName;
    int c,m,b=301,b2=301;

    if (_inputFileName.size()>0)
    {
        QFile file(_inputFileName);
        if (file.exists())
        {
            QFile result(_outputFileName);
            result.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
            QDataStream fout(&result);
            qDebug()<<"file exist";
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug()<<"file not open";
            }
            qDebug()<<"file open";

            long long step=0;
            static const int MaxBytesRead = 1;
            while(!file.atEnd()) {
                step++;
                QByteArray blob = file.read(MaxBytesRead);

                m=1;
                c = 1;
                unsigned int i1 = 0;
                QChar ch(blob[0]);

                int ASCIIcode =  (int)blob[0]+ b;//try .unicode()
                if ((int)blob[0]==0) ASCIIcode+=300;
                while (i1<e)
                {
                    c = c*ASCIIcode;
                    c = c%n;
                    i1++;
                }
                //if ((int)blob[0]!=0)
                    fout<<QString::number(c);
                //else fout<<

                unsigned int i2=0;
                while (i2<d)
                {
                    m = m*c;
                    m = m%n;
                    i2++;
                }
                m = m - b2;

                qDebug()<<"Uncripto "<<m<<"start "<<(int)blob[0]<<" "<<(char)blob[0]<<" ";

                if (m!=(int)blob[0] && m!=300)
                {
                    qDebug()<<step;
                    PrintKey();
                    break;
                }
            }
            result.close();
        }
    }
}

void Rsa::RsaUnshifrFile(QString _fileName,QString _outputFileName)
{
    int c,m,b=301,b2=301;

    if (_fileName.size()>0)
    {
        QFile file(_fileName);

        QFile result(_outputFileName);
        result.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
        QByteArray byteArr;
        if (file.exists())
        {
            qDebug()<<"file exist";
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug()<<"file not open";
            }
            qDebug()<<"file open";
            QDataStream fin(&file);
            long long step=0;
            while(!fin.atEnd()) {
                step++;
                m=1;
                bool ok = false;
                QString s;
                fin>>s;
                c=s.toInt();

                unsigned int i=0;
                while (i<d)
                {
                    m = m*c;
                    m = m%n;
                    i++;
                }
                m = m - b2;
                if (m==0)
                {
                    byteArr.append(QChar (0));
                }
                else
                {
                    byteArr.append(m);
                }
                qDebug()<<"cripto "<<c<<" Uncript "<<m;
                //b2 += 1;
                //if (b2>600) b2=301;

            }
        }
        result.write(byteArr);
        result.close();
    }
}

void Rsa::CreateKey()
{
    qDebug()<<"Please wait... Key generation procces.\n";
    srand((unsigned)time(NULL));
    int p = rand() % 100;
    int q = rand() % 100;
    int p_simple = sundaram(p);
    int q_simple = sundaram(q);
    n = p_simple*q_simple;

    unsigned int  d_simple = 0;
    while (d_simple != 1)
    {
        d = rand() % 100;
        d_simple = gcd(d, ((p_simple - 1)*(q_simple - 1)));
    }
    //Определение числа e, для которого является истинным
    //соотношение (e*d)%((p_simple-1)*(q_simple-1))=1.
    e=0;
    unsigned int e_simple = 0;
    while (e_simple != 1)
    {
        e += 1;
        e_simple = (e*d) % ((p_simple - 1)*(q_simple - 1));
    }
    //Сгенерированные ключи.
    PrintKey();
}
void Rsa::PrintKey()
{

    qDebug() << "{e"  << e << ','  << n << "n}" << " - Open key\n" ;
    qDebug() << "{d"  << d << ','  << n << "n}" << " - Secret key\n";
}

/////////////////////////////////////////////////////////////////////
//Алгоритм "решето Сундарама". Выбирает все простые числа
//до заданного (случайно сгенерированного).
int Rsa::sundaram(int n)
{
    int *a = new int[n], i, j, k;
    memset(a, 0, sizeof(int) * n);
    for (i = 1; 3 * i + 1 < n; i++)
    {
        for (j = 1; (k = i + j + 2 * i*j) < n && j <= i; j++)
            a[k] = 1;
    }
    //Выбирает из списка простых чисел ближайшее к заданному.
    for (i = n - 1; i >= 1; i--)
        if (a[i] == 0)
        {
            return (2 * i + 1);
            break;
        }
    delete[] a;
}
/////////////////////////////////////////////////////////////////////
//Алгоритм Евклида. Алгоритм для нахождения наибольшего
//общего делителя двух целых чисел. Используется для проверки
//чисел на взаимопростоту.
int Rsa::gcd(int a, int b)
{
    int c;
    while (b)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return abs(a);
}
