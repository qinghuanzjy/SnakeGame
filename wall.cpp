#include "wall.h"

Wall::Wall() {
    rec=nullptr;
}

Wall::~Wall()
{
    delete rec;
}

Wall::Wall(int x, int y, int width, int height)
{
    rec=new QRectF(x,y,width,height);
}

QRectF*& Wall::getWall()
{
    return rec;
}

void Wall::setWall(int x, int y, int width, int height)
{
    rec->setRect(x,y,width,height);
}


