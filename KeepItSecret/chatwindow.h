#include "client.h"

#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QMainWindow>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();
    void setClient(Client *_client);
    void setPartner(const QString &_partner);

private slots:
    void on_sendButton_clicked();
    void newmessage(QString partner, QString date, QString encryptedMsg);

    void on_quitButton_clicked();

private:
    Ui::ChatWindow *ui;
    Client *client;
    QString partner;
};

#endif // CHATDIALOG_H
