#include "client.h"

#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QMainWindow>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QMainWindow
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

    void on_quitButton_clicked();

private:
    Ui::ChatDialog *ui;
    Client *client;
    QString partner;
};

#endif // CHATDIALOG_H
