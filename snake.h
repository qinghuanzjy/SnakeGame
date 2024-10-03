#ifndef SNAKE_H
#define SNAKE_H
#include<QRectF>
#include<QList>
#include<QPointF>
class Snake
{
private:
    QList<QRectF>snake;
public:
    Snake();
    Snake(int x,int y);
    void addLength();
    void move();
};

#endif // SNAKE_H
