#ifndef DISCUSSIONWINDOW_H
#define DISCUSSIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class DiscussionWindow;
}

class DiscussionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiscussionWindow(QWidget *parent = 0);
    ~DiscussionWindow();

private:
    Ui::DiscussionWindow *ui;
};

#endif // DISCUSSIONWINDOW_H
