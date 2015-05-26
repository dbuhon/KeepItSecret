#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ContactsWindow;
}

class ContactsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContactsWindow(QWidget *parent = 0);
    ~ContactsWindow();
    void openDiscussionView();
    void openNewContactView();

private:
    Ui::ContactsWindow *ui;
};

#endif // CONTACTSWINDOW_H
