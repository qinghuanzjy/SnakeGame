#ifndef RETURNWINDOW_H
#define RETURNWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReturnWindow;
}

class ReturnWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReturnWindow(QWidget *parent = nullptr);
    ~ReturnWindow();
private: signals:

    void toStart();
private slots:

    void on_return_2_clicked();

private:
    Ui::ReturnWindow *ui;
};

#endif // RETURNWINDOW_H
