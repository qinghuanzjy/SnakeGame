#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include"gamewindow.h"
#include"returnwindow.h"
namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::StartWindow *ui;
    GameWindow* gamewindow;
    int diff=0;

};

#endif // STARTWINDOW_H
