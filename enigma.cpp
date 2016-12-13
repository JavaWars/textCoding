#include "enigma.h"
#include <QDataStream>
#include <QRegExp>
Enigma::Enigma()
{
    ReadRotorReflectorConstDataFromFile();
    allRotors.clear();
    allReflectors.clear();

    numRotor1=-1;numRotor2=-1;numRotor3=-1;numReflector=-1;
}

void Enigma::SetKey(int _Rotor1, int _Rotor2, int _Rotor3, QChar _reflector)
{
    numRotor1=_Rotor1;
    numRotor2=_Rotor2;numRotor3=_Rotor3;

    if (_reflector=='B')
        numReflector=0;
    else
        if (_reflector=='C') numReflector=1;
    isSettingsCorrect();
    printKeyAndCurrentState();
}

void Enigma::SetRotorsStartPos(int _rot1, int _rot2, int _rot3)
{
    currentPosRotor1=_rot1;
    currentPosRotor2=_rot2;
    currentPosRotor3=_rot3;
}

void Enigma::Shifr(QString _filePath,QString _resultPath)
{
    qDebug()<<_filePath<<_resultPath;

    if (_filePath.size()>0 && _resultPath.size()>0)
    {
        QFile inFile(_filePath);

        if (inFile.exists())
        {
            inFile.open(QIODevice::Text | QIODevice::ReadWrite);
            QFile result(_resultPath);
            //QDataStream fout(&result);
            result.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
            qDebug()<<"file exist";
            if (!result.exists())
            {
                result.close();
                result.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
                qDebug()<<"output file not open";
            }
            QByteArray byteArr;
            while (!inFile.atEnd()) {
                QString buf=inFile.readLine();
                QString resultStr;
                for (int i=0;i<buf.size();i++)
                {
                    qDebug()<<buf[i];
                    if (buf[i].isLetter())
                        resultStr+=ShifrChar(buf[i].toUpper());
                    else resultStr+=buf[i];
                }
                qDebug()<<resultStr;
                byteArr.append(resultStr);
            }
            result.write(byteArr);
            result.close();
        }
        else {
            qDebug()<<"file not exist";
        }
    }
}

QStringList Enigma::alphabet()
{
    QStringList result;
    QChar A('A');
    for (int i=0;i<26;i++)
    {
        result.push_back(QChar(A.toLatin1()+i));
    }
    return result;
}

QStringList Enigma::Rotors()
{
    QStringList result;
    for (int i=1;i<=8;i++)
    {
        result.push_back(QString::number(i));
    }
    return result;
}

QStringList Enigma::Reflectors()
{
    QStringList result;
    result.push_back("B");
    result.push_back("C");
    return result;
}

void Enigma::ReadRotorReflectorConstDataFromFile()
{
    QString reflectorPath(":/res/reflector.txt");
    QString rotorPath(":/res/rotors.txt");

    //allRotors;//rotor in range 1..8
    QFile fileIn(rotorPath);
    if (fileIn.exists())
    {
        fileIn.open(QIODevice::ReadOnly);

        while (!fileIn.atEnd()) {
            QString str=fileIn.readLine();
            qDebug()<<str;
            Rotor *r=CreateRotor(str);
            PrintRotor(*r);
            allRotors.push_back(r);
        }
    }

    //allReflectors;//reflector B or C
    QFile fileReflector(reflectorPath);
    if (fileReflector.exists())
    {
        fileReflector.open(QIODevice::ReadOnly);

        while (!fileReflector.atEnd()) {
            QString str=fileReflector.readLine();
            qDebug()<<str;
            Rotor *reflector=CreateReflector(str);
            PrintRotor(*reflector);
            allReflectors.push_back(reflector);
        }
    }
}

bool Enigma::isSettingsCorrect()
{
    if (((numReflector>=0) && (numReflector<=1))
            && (numRotor1>=0) &&(numRotor2>=0)&&(numRotor3>=0)
            &&(numRotor1<=7) &&(numRotor2<=7)&&(numRotor3<=7)
            && (numRotor1!=numRotor2)&& (numRotor1!=numRotor3) && (numRotor2!=numRotor3))
    {
        qDebug()<<" settings is correct!";
        return true;
    }
    qDebug()<<" incorrect settings ";
    return false;
}

QChar Enigma::GetNextLetterFromRotor(int _rotorNum, QChar _letter)
{
    Rotor * rotor=allRotors.at(_rotorNum);
    for (int i=0;i<rotor->m_RotorDataList.size();i++)
    {
        if (_letter==rotor->m_RotorDataList.at(i).first) return rotor->m_RotorDataList.at(i).second;
    }
}

QChar Enigma::GetNextLetterFromReflector(int _reflectorNum, QChar _letter)
{
    Rotor * rotor=allRotors.at(_reflectorNum);
    for (int i=0;i<rotor->m_RotorDataList.size();i++)
    {
        if (_letter==rotor->m_RotorDataList.at(i).first) return rotor->m_RotorDataList.at(i).second;
        if (_letter==rotor->m_RotorDataList.at(i).second) return rotor->m_RotorDataList.at(i).first;
    }
}

void Enigma::printKeyAndCurrentState()
{
    qDebug()<<"Model rot1 "<<numRotor1<<"rotor2 "<<numRotor2<<"rotor3 "<<numRotor3<<"refl "<<numReflector;
    qDebug()<<"Positon rot1 "<<currentPosRotor1<<"rot2 "<<currentPosRotor2<<"rot3 "<<currentPosRotor3;
}

QChar Enigma::ShifrChar(QChar ch)
{
    return ch;
}

Rotor *CreateRotor(QString _rotorParam)
{
    Rotor * result=new Rotor;
    QStringList stringList=_rotorParam.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);
    QChar A('A');
    int step=0;
    while (!stringList.empty())
    {
        //qDebug()<<stringList.at(0);
        if (step==0)
        {
            result->name=stringList.at(0);
        }
        else
        {
            QPair <QChar,QChar> *pair=new QPair<QChar,QChar>;
            pair->first=QChar(A.toLatin1()+step-1);
            pair->second=stringList.at(0)[0];
            //qDebug()<<QChar(A.toLatin1()+step-1)<<" "<<stringList.at(0)[0];
            result->m_RotorDataList.push_back(*pair);
        }
        step++;
        stringList.pop_front();
    }
    return result;
}

Rotor *CreateReflector(QString _reflectorParam)
{
    Rotor * result=new Rotor();
    QStringList stringList=_reflectorParam.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);
    int step=0;
    while (!stringList.empty())
    {
        //qDebug()<<stringList.at(0);

        if (step==0)
        {
            result->name=stringList.at(0);
        }
        else
        {
            QPair <QChar,QChar> pair;
            pair.first=stringList.at(0)[1];
            pair.second=stringList.at(0)[2];
            result->m_RotorDataList.push_back(pair);
        }
        stringList.pop_front();
        step++;
    }
    return result;
}

void PrintRotor(const Rotor &rotor)
{
    qDebug()<<"=============="<<rotor.name<<"================";
    for (int i=0;i<rotor.m_RotorDataList.size();i++)
    {
        qDebug()<<rotor.m_RotorDataList.at(i).first<<" "<<rotor.m_RotorDataList.at(i).second;
    }
}

Rotor *CopyRotor(const Rotor &rotor)
{
    Rotor *result=new Rotor();

    result->name=rotor.name;
    for (int i=0;i<rotor.m_RotorDataList.size();i++)
    {
        result->m_RotorDataList.push_back(rotor.m_RotorDataList.at(i));
    }
    return result;
}
