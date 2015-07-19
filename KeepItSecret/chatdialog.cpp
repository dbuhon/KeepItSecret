#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QDateTime>
#include <QTextCodec>

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

void ChatDialog::setClient(Client *_client)
{
    client = _client;
    connect(client,SIGNAL(newMessageSignal(QString,QString,QString)),SLOT(newmessage(QString,QString,QString)));
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
        chat->append("Vous : [" + currentDate + "] : " + text);
    }
}

void ChatDialog::newmessage(QString partner, QString date, QString msg){
    ui->chat->append(partner.toUtf8() + " [" + date.toUtf8() + "] : " + msg.toUtf8().trimmed());
}
