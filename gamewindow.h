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
#include<QSet>
using namespace std;
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
    bool isCollide();//碰撞障碍物检测，图标也用墙
    void addReward();//增加食物
    bool biteSelf();//判断是否咬到自己
    bool checkborder();//判断是否撞到边界墙
    void initObstacle(int num);//初始化障碍
    bool checkFoodPos();//检测食物是否与障碍物重叠
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
    QSet<pair<int,int>> occupiedPositions;//记录某个位置是否有障碍,用左上角坐标代替
    int score;//得分


};
#endif // GAMEWINDOW_H
