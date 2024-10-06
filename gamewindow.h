#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>
#include<QTimer>
#include<QPaintEvent>
#include<QPainter>
#include"snake.h"
#include"wall.h"
#include"food.h"
#include<QSet>
#include"returnwindow.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE
typedef enum{
    EASY,MIDDLE,HARD
}difficulty;
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr,int diff=difficulty::EASY);
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
    bool checknext();//检测下一时刻是否碰到障碍物或咬自己
    void drawGrid(QPainter& painter);
    void drawWalls(QPainter& painter);
    void drawObstacles(QPainter& painter);
    void drawFood(QPainter& painter);
    void drawSnake(QPainter& painter);
public slots:
    void timeout();
private:
    Ui::GameWindow *ui;
    QTimer* timer;
    bool isStart=false;
    bool isspeed=false;
    int time=300;//时间间隔
    Snake* mysnake;
    int w,h;//设置整个游戏界面的宽高
    Wall** walls;
    Food* food;
    QSet<pair<int,int>> occupiedPositions;//记录某个位置是否有障碍,用左上角坐标代替
    int score;//得分
    bool gameover=false;
    ReturnWindow* re;

};
#endif // GAMEWINDOW_H
