#include "cryptoutils.h"
#include "qblowfish.h"

CryptoUtils::CryptoUtils()
{

}

CryptoUtils::~CryptoUtils()
{

}

/**
 * Handle the encryption using QBlowfish
 * @brief CryptoUtils::encrypt
 * @param secretKey
 * @param string
 */
QString CryptoUtils::encrypt(QString secretKey, QString string){
    QBlowfish blowFish(QByteArray::fromBase64(secretKey.toUtf8()));
    blowFish.setPaddingEnabled(true);

    return blowFish.encrypted(string.toUtf8());
}

QString CryptoUtils::encrypt(QBlowfish blowFish, QString string){
    QByteArray encrypted = blowFish.encrypted(string.toUtf8());

    return encrypted.toBase64();
}

QString CryptoUtils::encrypt(QByteArray secretKey, QString string){
    QBlowfish blowFish(secretKey);
    blowFish.setPaddingEnabled(true);

    QByteArray encrypted = blowFish.encrypted(string.toUtf8());

    return encrypted.toBase64();
}


/**
 * Handle the decryption using QBlowfish
 * @brief CryptoUtils::decrypt
 * @param secretKey
 * @param string
 */
QString CryptoUtils::decrypt(QString secretKey, QString string){
    QBlowfish blowFish(QByteArray::fromBase64(secretKey.toUtf8()));
    blowFish.setPaddingEnabled(true);

    QByteArray decrypted = QByteArray::fromBase64(string.toUtf8());

    return blowFish.decrypted(decrypted);
}

/**
 * Handle the decryption using QBlowfish
 * @brief CryptoUtils::decrypt
 * @param blowFish
 * @param string
 * @return
 */
QString CryptoUtils::decrypt(QBlowfish blowFish, QString string){
    QByteArray decrypted = QByteArray::fromBase64(string.toUtf8());

    return blowFish.decrypted(decrypted);
}

QString CryptoUtils::decrypt(QByteArray secretKey, QString string){
    QBlowfish blowFish(secretKey);
    blowFish.setPaddingEnabled(true);

    QByteArray decrypted = QByteArray::fromBase64(string.toUtf8());

    return blowFish.decrypted(decrypted);
}


/**
 * Transforms a key into a QBlowfish
 * @brief CryptoUtils::getSecretKey
 * @param key
 * @return
 */
QBlowfish CryptoUtils::getSecretKey(QString key){
    QByteArray secretKey = QByteArray::fromBase64(key.toUtf8());

    QBlowfish blowFish(secretKey);

    blowFish.setPaddingEnabled(true);

    return blowFish;
}

