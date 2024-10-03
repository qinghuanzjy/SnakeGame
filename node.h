#ifndef NODE_H
#define NODE_H

class Node
{
private:
    static int width,height;
public:
    Node();
    Node(int x,int y);
    static int getWidth();
    static int getHeight();
    static void setWidth(int x);
    static void setHeight(int y);
};

#endif // NODE_H
