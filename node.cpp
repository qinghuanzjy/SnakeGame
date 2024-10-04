#include "node.h"
int Node::width=19;
int Node::height=20;


Node::Node()
{

}

Node::Node(int x, int y)
{
    width=x;
    height=y;
}

int Node::getWidth()
{
    return width;
}

int Node::getHeight()
{
    return height;
}

void Node::setWidth(int x)
{
    width=x;
}

void Node::setHeight(int y)
{
    height=y;
}
