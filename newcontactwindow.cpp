#include "newcontactwindow.h"
#include "ui_newcontactwindow.h"

NewContactWindow::NewContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewContactWindow)
{
    ui->setupUi(this);
}

NewContactWindow::~NewContactWindow()
{
    delete ui;
}
