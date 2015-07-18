#include "options.h"
#include "dbtools.h"

#define SEPARATOR "[|#|]"

Options::Options(QTcpSocket *_client, QList<QTcpSocket *> *_connectedUsers)
{
    client = _client;
    connectedUsers = _connectedUsers;

    if (connectedUsers->contains(client))
        loggedin = true;
}


void Options::parseLine(const QString &line){
    QString command = line.split(SEPARATOR).at(0);

    if (command.compare("*SHOWUSERS*") == 0){
        option_showusers = true;
        treatmentShowUsers(line);
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
    if (!loggedin)
        return;

    QTextStream flux(client);
    flux << "*SHOWUSERS*" << SEPARATOR;

    QListIterator<QTcpSocket*> iteratorContacts(*connectedUsers);
    while (iteratorContacts.hasNext()){
        QTcpSocket *contact = iteratorContacts.next();
        QString contactname = contact->objectName();

        if (DBTools::Instance().isAContact(client->objectName(), contactname))
            flux << iteratorContacts.next()->objectName() << SEPARATOR;
    }
    flux << endl;
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
        if (user.save())
            flux << "*ADDUSER*" << SEPARATOR << "OK" << SEPARATOR << endl;
        else
            flux << "*ADDUSER*" << SEPARATOR << "NOK" << SEPARATOR << endl;
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
    flux << "*ADDCONTACT*" << SEPARATOR;

    if (DBTools::Instance().insertContact(contact, client->objectName()))
        flux << "OK" << SEPARATOR << endl;
    else
        flux << "NOK" << SEPARATOR << endl;
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
            client->setObjectName(login);
            connectedUsers->append(client);

            sendContactListToClients();
            return;
        }
    }
    flux << "*SIGNIN*" << SEPARATOR << "NOK" << SEPARATOR << SEPARATOR << endl;
}


/**
 * Deliver a message
 * @brief Options::treatmentMessage
 * @param line
 */
void Options::treatmentMessage(const QString &line){
    if (!loggedin || line.split(SEPARATOR).length() < 3)
        return;

    QString login(line.split(SEPARATOR).at(1));
    QString msg(line.split(SEPARATOR).at(2));

    qDebug() << "Debug : [to " << login << "] " << msg;
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
        QListIterator<QTcpSocket*> iteratorContacts(*connectedUsers);
        while (iteratorContacts.hasNext()){
            QTcpSocket *contact = iteratorContacts.next();
            QString contactname = contact->objectName();

            if (DBTools::Instance().isAContact(username, contactname))
                flux << iteratorContacts.next()->objectName() << SEPARATOR;
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
