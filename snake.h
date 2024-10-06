#ifndef SNAKE_H
#define SNAKE_H
#include<QRectF>
#include<QList>
#include<QPointF>
typedef enum{
    LEFT,RIGHT,UP,DOWN
}dir;
class Snake
{
private:
    int direction;
    int predirection;
public:
    Snake();
    Snake(int x,int y,int dir);
    void addLength();//增长尾部，根据方向来增长
    void move();
    void deletetail();//删除尾部
    void deletehead();//删除头部
    void addhead();//增长头部，根据方向增长
    int getDirection();
    void setDirection(int x);
    QList<QRectF>snake;
};

#endif // SNAKE_H
