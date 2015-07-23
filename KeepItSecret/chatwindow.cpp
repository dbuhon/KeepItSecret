#include "chatwindow.h"
#include "ui_chatdialog.h"
#include <QDateTime>
#include <QTextCodec>

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

/**
 * Set a client to the chat window and performs actions
 * @brief ChatWindow::setClient
 * @param _client
 */
void ChatWindow::setClient(Client *_client)
{
    client = _client;
    connect(client,SIGNAL(newMessageSignal(QString,QString,QString)),SLOT(newmessage(QString,QString,QString)));
}

/**
 * Set a partner to the chat window and performs actions
 * @brief ChatWindow::setPartner
 * @param _partner
 */
void ChatWindow::setPartner(const QString &_partner)
{
    partner = _partner;
    ui->partnerLabel->setText("to : " + partner);
    client->askLogs(partner);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

/**
 * Action performed when the user clicks on the button to send a message
 * @brief ChatWindow::on_sendButton_clicked
 */
void ChatWindow::on_sendButton_clicked()
{
    QDateTime date;
    QString currentDate = date.currentDateTime().toLocalTime().toString("yyyy/MM/dd hh:mm:ss");

    QString text = ui->sendText->text().trimmed();

    if (!text.isNull() && !text.isEmpty()){

        CryptoUtils crypto;
        QString encryptedMsg = crypto.encrypt(client->secretKey, text);

        client->sendMessage(partner, currentDate, encryptedMsg);

        ui->chat->appendHtml("<b>Vous : [" + currentDate + "] : </b>" + text);
        ui->sendText->clear();
    }
}

/**
 * Action performed when the user receives a new message
 * @brief ChatWindow::newmessage
 * @param partner
 * @param date
 * @param encryptedMsg
 */
void ChatWindow::newmessage(QString partner, QString date, QString encryptedMsg){
    CryptoUtils crypto;
    QString msg = crypto.decrypt(client->secretKey, encryptedMsg);

    ui->chat->appendHtml("<b>" + partner.toUtf8() + " [" + date.toUtf8() + "] : </b>" + msg);
}

/**
 * Action performed on click in the 'Quit' button
 * @brief ChatWindow::on_quitButton_clicked
 */
void ChatWindow::on_quitButton_clicked()
{
    this->close();
}
