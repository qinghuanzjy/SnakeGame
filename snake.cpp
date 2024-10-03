#include "snake.h"
#include "node.h"


Snake::Snake()
{
}

Snake::Snake(int x, int y)
{
    QRectF head(x,y,Node::getWidth(),Node::getHeight());
    snake.append(head);
    addLength();
    addLength();
}

void Snake::addLength()
{
    int len=snake.length();
    int x=snake[len-1].left();
    int y=snake[len-1].bottom();
    QRectF body(x,y,Node::getWidth(),Node::getHeight());
    snake.append(body);
}
