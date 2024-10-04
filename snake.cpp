#include "snake.h"
#include "node.h"
#include<QDebug>

Snake::Snake()
{
}

Snake::Snake(int x, int y,int dir)
{
    QRectF head(x,y,Node::getWidth(),Node::getHeight());
    setDirection(dir);
    snake.append(head);
    addLength();
    addLength();
}

void Snake::addLength()
{
    int len=snake.length();
    int x=0,y=0;
    qDebug()<<getDirection();
    switch (getDirection()) {
    case dir::LEFT:
        x=snake[len-1].right();
        y=snake[len-1].top();
        break;
    case dir::RIGHT:
        x=snake[len-1].left()-Node::getWidth();
        y=snake[len-1].top();
        break;
    case dir::UP:
        x=snake[len-1].left();
        y=snake[len-1].bottom();
        break;
    case dir::DOWN:
        x=snake[len-1].left();
        y=snake[len-1].top()-Node::getHeight();
        break;
    default:
        break;
    }
    QRectF body(x,y,Node::getWidth(),Node::getHeight());
    snake.append(body);
}

void Snake::deletetail()
{
    if(!snake.isEmpty()){
        snake.removeLast();
    }
}

void Snake::addhead()
{//后续要加判断边界
    int x=0,y=0;
    switch (getDirection()) {
    case dir::LEFT:
        x=snake[0].left()-Node::getWidth();
        y=snake[0].top();
        break;
    case dir::RIGHT:
        x=snake[0].right();
        y=snake[0].top();
        break;
    case dir::UP:
        x=snake[0].left();
        y=snake[0].top()-Node::getHeight();
        break;
    case dir::DOWN:
        x=snake[0].left();
        y=snake[0].bottom();
        break;
    default:
        break;
    }
    QRectF body(x,y,Node::getWidth(),Node::getHeight());
    snake.insert(0,body);
}

int Snake::getDirection()
{
    return direction;
}

void Snake::setDirection(int x)
{
    direction=x;
}
