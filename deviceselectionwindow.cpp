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

void DeviceSelectionWindow::on_listWidget_devices_clicked(const QModelIndex &index)
{
    // TODO mémorisation du device pour le sauvegarder dans le contact
    this->close();
}



