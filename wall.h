#ifndef WALL_H
#define WALL_H
#include<QPointF>
#include<QRectF>
class Wall
{
private:
    QRectF* rec;
public:
    Wall();
    ~Wall();
    Wall(int x,int y,int width,int height);
    QRectF*& getWall();
    void setWall(int x,int y,int width,int height);
};

#endif // WALL_H
