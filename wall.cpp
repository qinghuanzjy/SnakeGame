#include "wall.h"

Wall::Wall() {}

Wall::Wall(QPointF p)
{
    pos=p;
}

QPointF Wall::getPoint()
{
    return pos;
}

void Wall::setPoint(QPointF p)
{
    pos=p;
}
