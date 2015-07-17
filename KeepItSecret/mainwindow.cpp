#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbtools.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client;
    connect(client,SIGNAL(signinSignal(bool)),this,SLOT(signin(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewAccountView()
{
   newAccountWindow = new NewAccountWindow(); // Be sure to destroy you window somewhere
   newAccountWindow->setClient(client);
   newAccountWindow->show();
}

void MainWindow::openContactsView()
{
   contactsWindow = new ContactsWindow();
   contactsWindow->setClient(client);
   contactsWindow->show();
}

void MainWindow::on_pushButton_submit_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    client->tryToSignIn(login, password);

    // TO TEST ALL THE COMMANDS
    //client->sendCommand(login);

    // TRAITEMENT
    // openContactsView();

    /*
    if (DBTools::Instance().tryToSignIn(login, password))
        openContactsView();
    else{
        QMessageBox mb;
        mb.setText("Vos identifiants sont invalides.\nRééssayez ou créez un nouveau compte.");
        mb.exec();
    }
    */
}

void MainWindow::on_pushButton_newAccount_clicked()
{
    openNewAccountView();
}

void MainWindow::signin(bool isOk)
{
    // TRAITEMENT
    if (isOk)
        openContactsView();
    else {
        QMessageBox mb;
        mb.setText("Vos identifiants sont invalides.\nRééssayez ou créez un nouveau compte.");
        mb.exec();
    }
}
