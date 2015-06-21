#include "newaccountwindow.h"
#include "ui_newaccountwindow.h"
#include <QMessageBox>
#include "kis_user.h"

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
    QMessageBox mb;
    // If both passwords lineEdit match
    if (ui->lineEdit_pwd1->text() == ui->lineEdit_pwd2->text()){
        // Create a kis_user
        kis_user u(ui->lineEdit_log->text(), ui->lineEdit_pwd2->text());

        // If save is effective
        if (u.save())
            this->close();

        else{
            mb.setText("Un compte avec ce nom existe déjà.");
            mb.exec();
        }
    }
    else{
        mb.setText("Les mots de passe ne sont pas identiques.");
        mb.exec();
    }
}
