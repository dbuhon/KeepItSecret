#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbtools.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //client = new Client;
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
    else{
        QMessageBox mb;
        mb.setText("Vos identifiants sont invalides.\nRééssayez ou créez un nouveau compte.");
        mb.exec();
    }
}

void MainWindow::on_pushButton_newAccount_clicked()
{
    openNewAccountView();
}
