#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbtools.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewAccountView()
{
   newAccountWindow = new NewAccountWindow(); // Be sure to destroy you window somewhere
   newAccountWindow->show();
}

void MainWindow::openContactsView()
{
   contactsWindow = new ContactsWindow();
   contactsWindow->show();
}

void MainWindow::on_pushButton_submit_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if (DBTools::Instance().tryToSignIn(login, password))
        openContactsView();
}

void MainWindow::on_pushButton_newAccount_clicked()
{
    openNewAccountView();
}
