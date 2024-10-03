#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include<QTimer>
#include<QPaintEvent>
#include<QPainter>
#include"snake.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void timeout();
private:
    Ui::GameWindow *ui;
    QTimer* timer;
    bool isStart=true;
    int time=100;//时间间隔
    int direction;
    Snake* snake;


};
#endif // GAMEWINDOW_H
