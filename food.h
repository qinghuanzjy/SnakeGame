#ifndef FOOD_H
#define FOOD_H
#include<QRectF>
class Food
{
private:
    QRectF* rec;
public:
    Food();
    ~Food();
    Food(int x,int y,int width,int height);
    QRectF*& getFood();
    void setFood(int x,int y,int width,int height);
};

#endif // FOOD_H
