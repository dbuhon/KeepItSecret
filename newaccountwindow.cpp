#include "newaccountwindow.h"
#include "ui_newaccountwindow.h"

NewAccountWindow::NewAccountWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAccountWindow)
{
    ui->setupUi(this);
}

NewAccountWindow::~NewAccountWindow()
{
    delete ui;
}

void NewAccountWindow::on_pushButton_clicked()
{
    //TODO Création du compte et persistance fichier local
    this->close();
}
