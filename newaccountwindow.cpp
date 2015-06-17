#include "newaccountwindow.h"
#include "ui_newaccountwindow.h"
#include "user.h"

NewAccountWindow::NewAccountWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::NewAccountWindow)
{
    ui->setupUi(this);
}

NewAccountWindow::~NewAccountWindow()
{
    delete ui;
}

void NewAccountWindow::on_pushButton_clicked()
{
    // If both passwords lineEdit match
    if (ui->lineEdit_pwd2->text() == ui->lineEdit_pwd2->text()){
        // Create user
        user u(ui->lineEdit_log->text(), ui->lineEdit_pwd2->text());
        // Save user in database
        u.save();
    }

    this->close();
}
