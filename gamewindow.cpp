#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QRandomGenerator>
typedef enum{
    LEFT,RIGHT,UP,DOWN
}dir;


GameWindow::GameWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    // 创建随机数生成器
    QRandomGenerator *generator = QRandomGenerator::global();
    int random_number = generator->bounded(0, 4);
    direction=random_number;
    timer=new QTimer(this);
    snake=new Snake();//生成蛇，并指定坐标
    connect(timer,&QTimer::timeout,this,&GameWindow::timeout);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    switch (key) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
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


}

void GameWindow::timeout()
{

}
