#ifndef DEVICESELECTIONWINDOW_H
#define DEVICESELECTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class DeviceSelectionWindow;
}

class DeviceSelectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceSelectionWindow(QWidget *parent = 0);
    ~DeviceSelectionWindow();

private slots:
    void on_listView_devices_clicked(const QModelIndex &index);

private:
    Ui::DeviceSelectionWindow *ui;
};

#endif // DEVICESELECTIONWINDOW_H
