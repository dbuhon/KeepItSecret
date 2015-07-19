#include "options.h"

#define SEPARATOR "[|#|]"

Options::Options(Client *_client)
{
    client = _client;
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
    else{
        QTextStream flux(client->getSocket());
        flux << line << endl;
    }
}

/**
 * Send his contacts list to the client and send a signal to populate the widget
 * @brief Options::treatmentShowUsers
 */
void Options::treatmentShowUsers(const QString &line){
    // Get the result of SHOWUSERS command and fil the listUsers with it
    if (line.split(SEPARATOR).length() >= 1){
        client->listUsers.clear();

        if (client->login.isEmpty()) return;

        for (int i = 1; i < line.split(SEPARATOR).length() - 1; i++){
            QString user = line.split(SEPARATOR).at(i);

            if (client->login.compare(user) != 0)
                client->listUsers.append(user);
        }
        emit client->populateListContactsSignal();
    }
}


/**
 * Get the result of ADDUSER command
 * @brief Options::treatmentAddContact
 * @param line
 */
void Options::treatmentAddUser(const QString &line){
    if (line.split(SEPARATOR).length() == 3){
        QString result = line.split(SEPARATOR).at(1);

         if (result == "OK"){
            emit client->addUserSignal(true);
         }
         else {
             emit client->addUserSignal(false);
         }
    }
}


/**
 * Get the result of ADDCONTACT command
 * @brief Options::treatmentAddContact
 * @param line
 */
void Options::treatmentAddContact(const QString &line){
    if (line.split(SEPARATOR).length() == 3){
        QString result = line.split(SEPARATOR).at(1);

         if (result == "OK"){
            emit client->addContactSignal(true);
         }
         else {
             emit client->addContactSignal(false);
         }
    }
}

/**
 * Get the result of SIGNIN command
 * @brief Options::treatmentSignIn
 * @param line
 */
void Options::treatmentSignIn(const QString &line){
    if (line.split(SEPARATOR).length() == 4){
        QString result = line.split(SEPARATOR).at(1);
        QString login = line.split(SEPARATOR).at(2);

        if (result == "OK"){
           client->login = login;
           emit client->signinSignal(true);
        }
        else
            emit client->signinSignal(false);
    }
}


/**
 * Get the result of MSG command
 * @brief Options::treatmentMessage
 * @param line
 */
void Options::treatmentMessage(const QString &line){
    if (line.split(SEPARATOR).length() >= 3){
        QString login = line.split(SEPARATOR).at(1);
        QString date = line.split(SEPARATOR).at(2);
        QString msg = line.split(SEPARATOR).at(3);

        // TRAITEMENT
    }
}

Options::~Options()
{

}
