#include "food.h"

Food::Food() {
    rec=nullptr;
}

Food::~Food()
{
    delete rec;
}

Food::Food(int x, int y, int width, int height)
{
    rec=new QRectF(x,y,width,height);
}

QRectF *&Food::getFood()
{
    return rec;
}

void Food::setFood(int x, int y, int width, int height)
{
    rec->setRect(x,y,width,height);
}
