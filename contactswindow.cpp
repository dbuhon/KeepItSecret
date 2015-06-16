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
    chat = new Chat();
    connect(chat, SIGNAL(accepted()), this, SLOT(close()));
    chat->show();

   /*discussionWindow = new DiscussionWindow();
   discussionWindow->show();*/
}

void ContactsWindow::on_pushButton_newContact_clicked()
{
    openNewContactView();
}

void ContactsWindow::on_listWidget_contacts_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    openDiscussionView();
}
