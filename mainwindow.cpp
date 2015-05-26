#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    openContactsView();
}

void MainWindow::on_pushButton_newAccount_clicked()
{
    openNewAccountView();
}
