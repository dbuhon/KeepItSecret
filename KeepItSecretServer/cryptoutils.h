#include <QObject>
#include <qblowfish.h>
#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H


class CryptoUtils
{
public:
    CryptoUtils();
    ~CryptoUtils();
    QString encrypt(QString secretKey, QString string);
    QString decrypt(QString secretKey, QString string);
    QString decrypt(QBlowfish blowFish, QString string);
    QString encrypt(QBlowfish blowFish, QString string);
    QBlowfish getSecretKey(QString key);
};

#endif // CRYPTOUTILS_H
