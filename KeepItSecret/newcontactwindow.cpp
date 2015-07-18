#include "newcontactwindow.h"
#include "ui_newcontactwindow.h"
#include <QMessageBox>

NewContactWindow::NewContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewContactWindow)
{
    ui->setupUi(this);

}

NewContactWindow::~NewContactWindow()
{
    delete ui;
}

void NewContactWindow::on_pushButton_createContact_clicked()
{
    QString contact = ui->lineEdit_contactLogin->text();

    if (!contact.isNull() && !contact.isEmpty())
        client->addContact(contact);
}

void NewContactWindow::setClient(Client *_client)
{
    client = _client;
    connect(client,SIGNAL(addContactSignal(bool)),this,SLOT(addcontact(bool)));
}

void NewContactWindow::addcontact(bool isAdded){
    if (isAdded)
        this->close();
    else {
        QMessageBox mb;
        mb.setText("Impossible d'ajouter ce contact, l'identifiant saisit n'est pas valide.");
        mb.exec();
    }
}
