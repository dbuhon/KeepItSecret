#include "client.h"

#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
    void setClient(Client *_client);
    void setPartner(const QString &_partner);

private slots:
    void on_sendButton_clicked();
    void newmessage(QString partner, QString date, QString encryptedMsg);

private:
    Ui::ChatDialog *ui;
    Client *client;
    QString partner;
};

#endif // CHATDIALOG_H
