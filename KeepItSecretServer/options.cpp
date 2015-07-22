#include "options.h"
#include "dbtools.h"
#include "cryptoutils.h"
#include "kis_log.h"

#define SEPARATOR "[|#|]"

Options::Options(QTcpSocket *_client, QList<QTcpSocket *> *_connectedUsers, QTextEdit *_logger)
{
    /*
    dictionaryActions.insert("*SHOWUSERS*", treatmentShowUsers);
    dictionaryActions.insert("*ADDUSER*", treatmentAddUser);
    dictionaryActions.insert("*ADDCONTACT*", treatmentAddContact);
    dictionaryActions.insert("*SIGNIN*", treatmentSignIn);
    dictionaryActions.insert("*MSG*", treatmentMessage);
    */

    loggedin = false;
    client = _client;
    connectedUsers = _connectedUsers;
    logger = _logger;

    if (connectedUsers->contains(client))
        loggedin = true;
}


void Options::parseLine(const QString &line){
    QString command = line.split(SEPARATOR).at(0);

    /*
    if (dictionaryActions.contains(command))
        dictionaryActions.find(command)(line);
    */

    if (command.compare("*SHOWUSERS*") == 0){
        option_showusers = true;
        treatmentShowUsers(line);
    }
    else if (command.compare("*GETLOGS*") == 0){
        option_getlogs = true;
        treatmentGetLogs(line);
    }
    else if (command.compare("*ADDUSER*") == 0){
        option_adduser = true;
        treatmentAddUser(line);
    }
    else if (command.compare("*ADDCONTACT*") == 0){
        option_addcontact = true;
        treatmentAddContact(line);
    }
    else if (command.compare("*SIGNIN*") == 0){
        option_signin = true;
        treatmentSignIn(line);
    }
    else if (command.compare("*MSG*") == 0){
        option_message = true;
        treatmentMessage(line);
    }
}

/**
 * Send his contacts list to the requester
 * @brief Options::treatmentShowUsers
 */
void Options::treatmentShowUsers(const QString &line){
    Q_UNUSED(line)

    if (!loggedin)
        return;

    /*SHOW CONNECTED USERS
    QTextStream flux(client);

    logger->append("SHOWUSERS : ");
    flux << "*SHOWUSERS*" << SEPARATOR;
    QListIterator<QTcpSocket*> iteratorOthers(*connectedUsers);
    while (iteratorOthers.hasNext()){
        QString username = iteratorOthers.next()->objectName();
        flux << username << SEPARATOR;
        logger->append("   - " + username);
    }
    flux << endl;
    logger->append("");
    */

    // SHOW CONTACTS
    QTextStream flux(client);
    flux << "*SHOWUSERS*" << SEPARATOR;
    QString clientName = client->objectName();
    QStringList listContact = DBTools::Instance().getContacts(clientName);
    for (int i = 0; i < listContact.size(); ++i) {
        flux << listContact[i] << SEPARATOR;
    }
    flux << endl;
}

/**
 * Send to the client its logs with a specific contact
 * @brief treatmentGetLogs
 * @param line
 */
void Options::treatmentGetLogs(const QString &line){
    if (loggedin && line.split(SEPARATOR).length() == 3){
        QString partner = line.split(SEPARATOR).at(1);

        QList<LogKIS> listLogs = DBTools::Instance().getLogs(partner, client->objectName());

        for (int i = 0; i < listLogs.size(); i++){
            LogKIS log = listLogs[i];

            QTextStream flux(client);
            flux << "*MSG*" << SEPARATOR << log.getSender() << SEPARATOR << log.getDate() << SEPARATOR << log.getEncryptedMessage() << SEPARATOR << endl;
        }
        logger->append("History sent to : '" + client->objectName() + "'\n");
    }
}

/**
 * Add a user into the database and send to the requester the result
 * @brief Options::treatmentAddContact
 * @param line
 */
void Options::treatmentAddUser(const QString &line){
    if (line.split(SEPARATOR).length() == 4)
    {
        QString login(line.split(SEPARATOR).at(1));
        QString password(line.split(SEPARATOR).at(2));

        QTextStream flux(client);

        // User creation
        UserKIS user(login, password);

        // Try to save in the database
        if (user.save()){
            flux << "*ADDUSER*" << SEPARATOR << "OK" << SEPARATOR << endl;
            logger->append("ADDUSER (" + login + ") : OK\n");
        }
        else{
            flux << "*ADDUSER*" << SEPARATOR << "NOK" << SEPARATOR << endl;            
            logger->append("ADDUSER (" + login + ") : NOK\n");
        }
    }
}


/**
 * Add a contact into the requester's list and send to the requester the result
 * @brief Options::treatmentAddContact
 * @param line
 */
void Options::treatmentAddContact(const QString &line){
    if (!loggedin || line.split(SEPARATOR).length() != 3)
        return;

    QString contact(line.split(SEPARATOR).at(1));

    QTextStream flux(client);

    if (DBTools::Instance().insertContact(contact, client->objectName())){
        flux << "*ADDCONTACT*" << SEPARATOR << "OK" << SEPARATOR << endl;
        logger->append("ADDCONTACT (" + contact + " : " + client->objectName() + ") : OK\n");
        treatmentShowUsers(line);
        sendContactListToClients();
    }
    else{
        flux << "*ADDCONTACT*" << SEPARATOR << "NOK" << SEPARATOR << endl;
        logger->append("ADDCONTACT (" + contact + " : " + client->objectName() + ") : NOK\n");
    }
}

/**
 * Set the client logged in or not
 * @brief Options::treatmentSignIn
 * @param line
 */
void Options::treatmentSignIn(const QString &line){
    if (line.split(SEPARATOR).length() != 4)
        return;

    QString login(line.split(SEPARATOR).at(1));
    QString password(line.split(SEPARATOR).at(2));

    QTextStream flux(client);

    if (DBTools::Instance().tryToSignIn(login, password)){

        bool isNotConnectedYet = true;

        // Vérification que l'utilisateur n'est pas déjà connecté
        QListIterator<QTcpSocket*> iter(*connectedUsers);
        while (iter.hasNext()){
            if (iter.next()->objectName().compare(login) == 0)
                isNotConnectedYet = false;
        }

        if (isNotConnectedYet){
            flux << "*SIGNIN*" << SEPARATOR << "OK" << SEPARATOR << login << SEPARATOR << endl;
            logger->append("SIGNIN (" + login + ") : OK\n");

            client->setObjectName(login);
            connectedUsers->append(client);

            sendContactListToClients();
            return;
        }
    }
    flux << "*SIGNIN*" << SEPARATOR << "NOK" << SEPARATOR << SEPARATOR << endl;    
    logger->append("SIGNIN (" + login + ") : NOK\n");
}


/**
 * Deliver a message
 * @brief Options::treatmentMessage
 * @param line
 */
void Options::treatmentMessage(const QString &line){
    if (!loggedin || line.split(SEPARATOR).length() < 4)
        return;

    QString partner(line.split(SEPARATOR).at(1));
    QString date(line.split(SEPARATOR).at(2));
    QString encryptedMsg(line.split(SEPARATOR).at(3));
    QString cryptedMsgForPartner = handleLogsInsertion(encryptedMsg, date, partner);

    QListIterator<QTcpSocket*> iter(*connectedUsers);
    while (iter.hasNext()){
        QTcpSocket *user = iter.next();
        if (user->objectName().compare(partner) == 0){
            QTextStream flux(user);

            flux << "*MSG*" << SEPARATOR << client->objectName() << SEPARATOR << date << SEPARATOR << cryptedMsgForPartner << SEPARATOR << endl;
        }
    }

    logger->append("Message sent from : '" + client->objectName() + "' to '" + partner + "' at [" + date + "]\n");
}

/**
 * Handle the logs insertion (history of conversations) and return an encrypted message readable by the partner
 * @brief Options::handleLogsInsertion
 * @param encryptedMsg
 * @param date
 * @param partner
 */
QString Options::handleLogsInsertion(QString &encryptedMsg, QString &date, QString &partner){
    // Handle the re-encryption of the message with the partner secret
    QString clientName = client->objectName();

    // Insert logs in the sender db
    DBTools::Instance().insertLog(encryptedMsg, date, partner, clientName);

    CryptoUtils crypto;
    QString secretClient = DBTools::Instance().getSecret(clientName);
    QString secretPartner = DBTools::Instance().getSecret(partner);

    QString msg = crypto.decrypt(secretClient, encryptedMsg);

    QString cryptedMsg = crypto.encrypt(secretPartner, msg);

    // Insert logs in the receiver db
    DBTools::Instance().insertLog(cryptedMsg, date, clientName, partner);

    return cryptedMsg;
}

/**
 * Send to the clients their contact list
 * @brief Server::sendNewUserList
 */
void Options::sendContactListToClients(){
    if (!loggedin)
        return;

    QListIterator<QTcpSocket*> iteratorUsers(*connectedUsers);
    while (iteratorUsers.hasNext()){
        QTcpSocket *user = iteratorUsers.next();
        QString username = user->objectName();

        QTextStream flux(user);
        flux << "*SHOWUSERS*" << SEPARATOR;

        QStringList listContact = DBTools::Instance().getContacts(username);
        for (int i = 0; i < listContact.size(); ++i) {
            flux << listContact[i] << SEPARATOR;
        }
        flux << endl;
    }
}

/**
 * Send to the clients the new list of connectedUsers
 * @brief Server::sendNewUserList
 */
void Options::sendUserListToClients(){
    QListIterator<QTcpSocket*> iteratorUsers(*connectedUsers);
    while (iteratorUsers.hasNext()){
        QTextStream flux(iteratorUsers.next());

        flux << "*SHOWUSERS*" << SEPARATOR;
        QListIterator<QTcpSocket*> iteratorOthers(*connectedUsers);
        while (iteratorOthers.hasNext()){
            flux << iteratorOthers.next()->objectName() << SEPARATOR;
        }
        flux << endl;
    }
}

Options::~Options()
{

}

