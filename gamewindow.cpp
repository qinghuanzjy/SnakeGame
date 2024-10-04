#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QRandomGenerator>
#include<QDebug>


GameWindow::GameWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::GameWindow)
{
    int wid=36*Node::getWidth();
    int hgt=36*Node::getHeight();
    setwh(wid,hgt);//设置游戏界面为18*18
    setFixedSize(wid,hgt);
    ui->setupUi(this);
    // 创建随机数生成器
    QRandomGenerator *generator = QRandomGenerator::global();
    int random_number = generator->bounded(0, 4);//方向随机
    timer=new QTimer(this);
    mysnake=new Snake(wid/2,hgt/2,random_number);//生成蛇，并指定坐标
    int unithgt=hgt/Node::getHeight();//算出高有几块
    int unitwid=wid/Node::getWidth();//算出宽有几块
    walls=new Wall*[unithgt];//初始化墙
    for(int i=0;i<unithgt;i++){
        walls[i]=new Wall[unitwid];
    }
    for(int i=0;i<unithgt;i++){
        for(int j=0;j<unitwid;j++){
            if(i==0||i==unithgt-1){
                walls[i][j]= Wall(i*Node::getHeight(),j*Node::getWidth(),Node::getWidth(),Node::getHeight());
            }else{
                if(j==0||j==unitwid-1){
                    walls[i][j]=Wall(i*Node::getHeight(),j*Node::getWidth(),Node::getWidth(),Node::getHeight());
                }else{
                    walls[i][j]=Wall();
                }
            }
        }

    }
    addReward();
    connect(timer,&QTimer::timeout,this,&GameWindow::timeout);

}

GameWindow::~GameWindow()
{
    delete ui;
    delete mysnake;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    switch (key) {
    case Qt::Key_Up:
        if(mysnake->getDirection()!=dir::DOWN){
            mysnake->setDirection(dir::UP);
        }
        break;
    case Qt::Key_Down:
        if(mysnake->getDirection()!=dir::UP){
            mysnake->setDirection(dir::DOWN);
        }
        break;
    case Qt::Key_Left:
        if(mysnake->getDirection()!=dir::RIGHT){
            mysnake->setDirection(dir::LEFT);
        }
        break;
    case Qt::Key_Right:
        if(mysnake->getDirection()!=dir::LEFT){
            mysnake->setDirection(dir::RIGHT);
        }
        break;
    case Qt::Key_Space:
        if(isStart==true){
            isStart=false;
            timer->stop();
        }else{
            isStart=true;
            timer->start(time);//实现空格切换暂停开始
        }
        break;
    default:
        break;
    }
}

void GameWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pix;
    QPen pen;
    QBrush brush;
    for(int i=0;i<mysnake->snake.length();i++){
        QRectF temp=mysnake->snake[i];
        int direct=mysnake->getDirection();
        if(i==0){
            if(direct==dir::UP){
                pix.load(":/snakeHeadUp.png");
                painter.drawPixmap(temp.x(),temp.y(),Node::getWidth(),Node::getHeight(),pix);
            }else if(direct==dir::DOWN){
                pix.load(":/snakeHeadDown.png");
                painter.drawPixmap(temp.x(),temp.y(),Node::getWidth(),Node::getHeight(),pix);
            }else if(direct==dir::LEFT){
                pix.load(":/snakeHeadLeft.png");
                painter.drawPixmap(temp.x(),temp.y(),Node::getWidth(),Node::getHeight(),pix);
            }else{
                pix.load(":/snakeHeadRight.png");
                painter.drawPixmap(temp.x(),temp.y(),Node::getWidth(),Node::getHeight(),pix);
            }
            //画蛇头，根据四个方向来画
        }else{
            //画蛇尾
            pix.load(":/snakeTail.png");
            painter.drawPixmap(temp.x(),temp.y(),Node::getWidth(),Node::getHeight(),pix);
        }
    }
    pen.setColor(Qt::lightGray);
    pen.setWidth(1);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    int gridWidth = Node::getWidth(); // 网格宽度
    int gridHeight = Node::getHeight(); // 网格高度

    // 绘制纵向线条
    for (int x = 0; x < width(); x += gridWidth) {
        painter.drawLine(x, 0, x, height());
    }

    // 绘制横向线条
    for (int y = 0; y < height(); y += gridHeight) {
        painter.drawLine(0, y, width(), y);
    }
    //画墙
    pix.load(":/wall.png");
    for(int i=0;i<h/Node::getHeight();i++){
        for(int j=0;j<w/Node::getWidth();j++){
            QRectF* p=walls[i][j].getWall();
            if(p!=nullptr){
                painter.drawPixmap(p->left(),p->top(),Node::getWidth(),Node::getHeight(),pix);
            }
        }
    }
    //画食物
    pix.load(":/china.png");
    painter.drawPixmap(food->getFood()->left(),food->getFood()->top(),Node::getWidth(),Node::getHeight(),pix);
    /*if(isCollide()){
        QFont font("方正舒体",30,QFont::ExtraLight,false);
        painter.setFont(font);
        painter.drawText(w/2,h/2,QString("GAME OVER!"));
        timer->stop();

    }*/
    if(biteSelf()){
        pen.setColor(Qt::red);
        painter.setPen(pen);
        QFont font("方正舒体",50,QFont::Medium,false);
        painter.setFont(font);
        painter.drawText(w/2-200,h/2,QString("GAME OVER!"));
        timer->stop();
    }

}

void GameWindow::setwh(int x, int y)
{

    w=x;
    h=y;
}

bool GameWindow::isCollide()
{
    int unitwid=w/Node::getWidth();
    int unithgt=h/Node::getHeight();
    for(int i=0;i<unitwid;i++){
        for(int j=0;j<unithgt;j++){
            QRectF* p=walls[i][j].getWall();
            if(mysnake->snake[0].intersects(*p)){
                return true;
            }
        }
    }
    return false;
}

void GameWindow::addReward()
{
    // 创建随机数生成器
    QRandomGenerator *generator = QRandomGenerator::global();
    int unitwid=w/Node::getWidth();
    int unithgt=h/Node::getHeight();
    int x=generator->bounded(1,unitwid-1);
    int y=generator->bounded(1,unithgt-1);
    food=new Food(x*Node::getWidth(),y*Node::getHeight(),Node::getWidth(),Node::getHeight());
}

bool GameWindow::biteSelf()
{
    for(int i=1;i<mysnake->snake.length();i++){
        if(mysnake->snake[0].intersects(mysnake->snake[i])){
            return true;
        }
    }
    return false;
}

void GameWindow::timeout()
{
    QRectF* f=food->getFood();
    if(mysnake->snake[0].intersects(*f)){
        mysnake->addLength();
        delete food;
        addReward();
    }
    mysnake->deletetail();
    mysnake->addhead();
    update();
}
