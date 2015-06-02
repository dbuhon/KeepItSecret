#include "contactswindow.h"
#include "ui_contactswindow.h"
#include "chat.h"

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
   newContactWindow->show();
}

void ContactsWindow::openDiscussionView()
{
   // Test bluetooth chat
    Chat d;
    QObject::connect(&d, SIGNAL(accepted()), SLOT(quit()));
    d.show();

   /*discussionWindow = new DiscussionWindow();
   discussionWindow->show();*/
}

void ContactsWindow::on_pushButton_newContact_clicked()
{
    openNewContactView();
}

void ContactsWindow::on_listWidget_contacts_clicked(const QModelIndex &index)
{
     openDiscussionView();
}
