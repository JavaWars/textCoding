#ifndef ENIGMA_H
#define ENIGMA_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QChar>
#include <QPair>

struct Rotor
{
    QString name;
    QList <QPair<QChar,QChar> > m_RotorDataList;
};

Rotor * CreateRotor(QString _rotorParam);
Rotor *CreateReflector(QString _reflectorParam);
void PrintRotor(const  Rotor& rotor);
Rotor * CopyRotor(const  Rotor& rotor);

class Enigma
{
public:
    Enigma();

    void SetKey(int _Rotor1,int _Rotor2,int _Rotor3,QChar _reflector);
    void SetRotorsStartPos(int _rot1,int _rot2,int _rot3);
    void Shifr(QString _filePath, QString _resultPath);

    static QStringList alphabet();
    static QStringList Rotors();
    static QStringList Reflectors();

private:
    //all possible settings
    QVector<Rotor*> allRotors;//rotor in range {rotor 1 - rotor 8}
    QVector <Rotor*> allReflectors;//reflector {B or C}

    //part of settings
    //enigma has 3 rotors and 1 reflector
    int numRotor1,numRotor2,numRotor3,numReflector;//configuration enigma rotor & reflector
    int currentPosRotor1,currentPosRotor2,currentPosRotor3;


    void ReadRotorReflectorConstDataFromFile();
    void SubChars(QChar ch1,QChar ch2);
    bool isSettingsCorrect();
    QChar GetNextLetterFromRotor(int _rotorNum, QChar _letter);
    QChar GetNextLetterFromReflector(int _reflectorNum,QChar _letter);
    void printKeyAndCurrentState();

    QChar ShifrChar(QChar ch);
};

#endif // ENIGMA_H
