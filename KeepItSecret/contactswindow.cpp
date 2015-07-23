#include "contactswindow.h"
#include "ui_contactswindow.h"
#include "chatdialog.h"

ContactsWindow::ContactsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactsWindow)
{
    ui->setupUi(this);
}

ContactsWindow::~ContactsWindow()
{
    delete ui;
}

void ContactsWindow::openNewContactView()
{
   newContactWindow = new NewContactWindow();
   newContactWindow->setClient(client);
   newContactWindow->show();
}

void ContactsWindow::openChatDialogView(QString partner)
{
    ChatDialog *chatDialog = new ChatDialog();
    chatDialog->setClient(client);
    chatDialog->setPartner(partner);
    chatDialog->show();
}

void ContactsWindow::setClient(Client *_client)
{
    client = _client;
    connect(client,SIGNAL(populateListContactsSignal()),this,SLOT(populateContacts()));
    client->showUsers();
}

void ContactsWindow::on_pushButton_newContact_clicked()
{
    openNewContactView();
}

void ContactsWindow::on_listWidget_contacts_clicked(const QModelIndex &index)
{
    QString partner = index.model()->data(index, Qt::DisplayRole).toString();
    openChatDialogView(partner);
}

void ContactsWindow::populateContacts(){
    ui->listWidget_contacts->clear();
    ui->listWidget_contacts->addItems(client->listUsers);
}
