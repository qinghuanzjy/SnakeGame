#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include<QTimer>
#include<QPaintEvent>
#include<QPainter>
#include"snake.h"
#include"node.h"
#include"wall.h"
#include"food.h"
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
    void setwh(int x,int y);
    bool isCollide();
    void addReward();
    bool biteSelf();
public slots:
    void timeout();
private:
    Ui::GameWindow *ui;
    QTimer* timer;
    bool isStart=false;
    int time=100;//时间间隔
    Snake* mysnake;
    int w,h;//设置整个游戏界面的宽高
    Wall** walls;
    Food* food;


};
#endif // GAMEWINDOW_H
