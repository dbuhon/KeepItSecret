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

void NewContactWindow::openDeviceSelectionView(){
    deviceSelectionWindow = new DeviceSelectionWindow;
    deviceSelectionWindow->show();
}

void NewContactWindow::on_pushButton_createContact_clicked()
{
    this->close();
}

void NewContactWindow::on_pushButton_sync_clicked()
{
    openDeviceSelectionView();
}