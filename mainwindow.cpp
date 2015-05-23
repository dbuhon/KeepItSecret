#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
   mMyNewWindow = new myWindow(); // Be sure to destroy you window somewhere
   mMyNewWindow->show();
}

void MainWindow::on_pushButton_submit_clicked()
{
    openNewWindow();
}
