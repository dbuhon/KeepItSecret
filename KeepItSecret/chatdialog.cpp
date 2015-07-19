#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QDateTime>

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

void ChatDialog::setClient(Client *_client)
{
    client = _client;
}

void ChatDialog::setPartner(const QString &_partner)
{
    partner = _partner;
    ui->partnerLabel->setText("to : " + partner);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::on_sendButton_clicked()
{
    QDateTime date;
    QString currentDate = date.currentDateTime().toLocalTime().toString();

    QTextEdit *chat = ui->chat;
    QString text = ui->sendText->text();

    if (!text.isNull() && !text.isEmpty()){
        client->sendMessage(partner, currentDate, text);
        chat->append(client->login + " [" + currentDate + "] : " + text);
    }
}
