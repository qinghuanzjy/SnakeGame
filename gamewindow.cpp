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

}

void GameWindow::setwh(int x, int y)
{
    w=x;
    h=y;
}

void GameWindow::timeout()
{

}
