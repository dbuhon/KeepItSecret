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
    QString login = ui->lineEdit_log->text();
    QString pwd1 = ui->lineEdit_pwd1->text();
    QString pwd2 = ui->lineEdit_pwd2->text();

    QMessageBox mb;
    if (!login.isNull() && !login.isEmpty()
            && !pwd1.isNull() && !pwd1.isEmpty()
            && !pwd2.isNull() && !pwd2.isEmpty()
            && pwd1.compare(pwd2) == 0){

        // Create a kis_user
        kis_user user(login, pwd1);

        // If save is effective
        if (user.save())
            this->close();

        else{
            mb.setText("Un compte avec ce nom existe déjà.");
            mb.exec();
        }
    }
    else{
        mb.setText("Les champs du formulaire ne sont pas bien remplis.");
        mb.exec();
    }
}

void NewAccountWindow::setClient(Client *_client)
{
    client = _client;
}
