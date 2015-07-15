#ifndef DISCUSSIONWINDOW_H
#define DISCUSSIONWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class DiscussionWindow;
}

class DiscussionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiscussionWindow(QWidget *parent = 0);
    ~DiscussionWindow();
    void setClient(Client *_client);

private:
    Ui::DiscussionWindow *ui;
    Client *client;
};

#endif // DISCUSSIONWINDOW_H
