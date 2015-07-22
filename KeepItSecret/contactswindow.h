#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include "newcontactwindow.h"
#include "chatdialog.h"
#include "client.h"

class Chat;

namespace Ui {
class ContactsWindow;
}

class ContactsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContactsWindow(QWidget *parent = 0);
    ~ContactsWindow();
    void openNewContactView();
    void openChatDialogView(QString partner);
    void setClient(Client *_client);

private slots:
    void on_pushButton_newContact_clicked();
    void on_listWidget_contacts_clicked(const QModelIndex &index);
    void populateContacts();

private:
    Ui::ContactsWindow *ui;
    NewContactWindow *newContactWindow;
    Client *client;
};

#endif // CONTACTSWINDOW_H
