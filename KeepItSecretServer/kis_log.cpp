#include "kis_log.h"

LogKIS::LogKIS()
{

}

LogKIS::LogKIS(const QString &_sender, const QString &_date, const QString &_encryptedMessage)
{
    sender = _sender;
    date = _date;
    encryptedMessage = _encryptedMessage;
}

QString LogKIS::getSender(){
    return sender;
}

QString LogKIS::getDate(){
    return date;
}

QString LogKIS::getEncryptedMessage(){
    return encryptedMessage;
}

LogKIS::~LogKIS()
{

}

