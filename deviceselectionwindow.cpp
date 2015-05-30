#include "deviceselectionwindow.h"
#include "ui_deviceselectionwindow.h"

DeviceSelectionWindow::DeviceSelectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceSelectionWindow)
{
    ui->setupUi(this);
}

DeviceSelectionWindow::~DeviceSelectionWindow()
{
    delete ui;
}

void DeviceSelectionWindow::on_listView_devices_clicked(const QModelIndex &index)
{
    this->close();
}
