#include <QObject>

#ifndef LOGKIS_H
#define LOGKIS_H


class LogKIS
{
public:
    LogKIS();
    LogKIS(const QString &_sender, const QString &_date, const QString &_encryptedMessage);
    ~LogKIS();
    QString getSender();
    QString getDate();
    QString getEncryptedMessage();
private:
    QString sender;
    QString date;
    QString encryptedMessage;
};

#endif // LOGKIS_H
