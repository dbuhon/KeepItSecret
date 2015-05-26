#ifndef NEWCONTACTWINDOW_H
#define NEWCONTACTWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewContactWindow;
}

class NewContactWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewContactWindow(QWidget *parent = 0);
    ~NewContactWindow();
    void openDeviceSelectionView();

private:
    Ui::NewContactWindow *ui;
};

#endif // NEWCONTACTWINDOW_H
