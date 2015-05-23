#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>

namespace Ui {
class myWindow;
}

class myWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myWindow(QWidget *parent = 0);
    ~myWindow();

private:
    Ui::myWindow *ui;
};

#endif // MYWINDOW_H
