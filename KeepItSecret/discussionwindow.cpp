#include "discussionwindow.h"
#include "ui_discussionwindow.h"

DiscussionWindow::DiscussionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiscussionWindow)
{
    ui->setupUi(this);
}

DiscussionWindow::~DiscussionWindow()
{
    delete ui;
}
