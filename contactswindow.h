#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include "newcontactwindow.h"
#include "discussionwindow.h"

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
    void openDiscussionView();

private slots:
    void on_pushButton_newContact_clicked();
    void on_listWidget_contacts_clicked(const QModelIndex &index);

private:
    Ui::ContactsWindow *ui;
    NewContactWindow *newContactWindow;
    DiscussionWindow *discussionWindow;
    Chat *chat;
};

#endif // CONTACTSWINDOW_H
