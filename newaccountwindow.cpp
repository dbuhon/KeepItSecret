#include "newaccountwindow.h"
#include "ui_newaccountwindow.h"
#include "user.h"

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
    /*
    QString XMAX=ui->lineEdit->text();
    xMax=XMAX.toDouble();
    */

    user u(ui->lineEdit_log->text(), ui->lineEdit_pwd1->text(), ui->lineEdit_pwd2->text());

    if (u)
        u.save();

    //TODO Création du compte et persistance locale
    this->close();
}
