#include "gamewindow.h"
#include "ui_gamewindow.h"
#include"node.h"
#include <QRandomGenerator>
#include<QDebug>
#include <utility>
GameWindow::GameWindow(QWidget *parent,int diff):QMainWindow(parent),ui(new Ui::GameWindow)
{
    int widnode=36;
    int hgtnode=36;
    int obstaclenum=10;
    switch (diff) {
    case difficulty::EASY:
        widnode=24;
        hgtnode=24;
        obstaclenum=20;
        break;
    case difficulty::MIDDLE:
        widnode=36;
        hgtnode=36;
        obstaclenum=50;
        break;
    case difficulty::HARD:
        widnode=36;
        hgtnode=36;
        obstaclenum=100;
        break;
    default:
        break;
    }
    setWindowTitle("游戏窗口");
    ui->setupUi(this);
    // 创建随机数生成器
    QFont font("微软雅黑", 14);
    QPalette palette = ui->scoreui->palette();
    palette.setColor(QPalette::WindowText, Qt::green); // 将字体颜色设置为绿色
    ui->scoreui->setPalette(palette); // 应用调色板
    QRandomGenerator *generator = QRandomGenerator::global();
    int wid=widnode*Node::getWidth();
    int hgt=hgtnode*Node::getHeight();
    score=0;//初始化得分
    int unithgt=hgt/Node::getHeight();//算出高有几块
    int unitwid=wid/Node::getWidth();//算出宽有几块
    setwh(wid,hgt);//设置游戏界面为36*36
    setFixedSize(wid,hgt);
    ui->scoreui->setFont(font); // 应用字体到得分标签
    ui->scoreui->move(wid-5*Node::getWidth(),Node::getHeight());//设置得分画面
    ui->scoreui->setText("得分: 0");
    initObstacle(obstaclenum);//障碍物数量
    int random_number = generator->bounded(0, 4);//方向随机
    timer=new QTimer(this);
    mysnake=new Snake(wid/2,hgt/2,random_number);//生成蛇，并指定坐标  
    walls=new Wall*[unithgt];//初始化墙
    for(int i=0;i<unithgt;i++){
        walls[i]=new Wall[unitwid];
    }
    for(int i=0;i<unithgt;i++){
        for(int j=0;j<unitwid;j++){
            if(i==0||i==unithgt-1){
                walls[i][j]= Wall(j*Node::getWidth(),i*Node::getHeight(),Node::getWidth(),Node::getHeight());
            }else{
                if(j==0||j==unitwid-1){
                    walls[i][j]=Wall(j*Node::getWidth(),i*Node::getHeight(),Node::getWidth(),Node::getHeight());
                }else{
                    walls[i][j]=Wall();
                }
            }
        }

    }
    addReward();//初始化食物
    connect(timer,&QTimer::timeout,this,&GameWindow::timeout);

}

GameWindow::~GameWindow()
{
    delete ui;
    delete mysnake;
    for(int i=0;i<h/Node::getHeight();i++){
        if(walls[i]){
            delete walls[i];
        }
    }
    delete[] walls;
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
    case Qt::Key_Q://按q加速
        if(isspeed==true){
            isspeed=false;
            timer->setInterval(time);
        }else{
            isspeed=true;
            timer->setInterval(time/3);
        }
        break;
    default:
        break;
    }
}

void GameWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPen pen;
    bool gameOver = biteSelf() || checkborder() || isCollide();
    // 网格线、墙、障碍物、食物的绘制
    drawGrid(painter);
    drawWalls(painter);
    drawObstacles(painter);
    drawFood(painter);
    drawSnake(painter);
    if (gameOver) {
        pen.setColor(Qt::red);
        painter.setPen(pen);
        QFont font("方正舒体", w / 10, QFont::Medium, false);
        painter.setFont(font);
        painter.drawText(w / 2 - Node::getWidth() * (w / 45), h / 2, QString("GAME OVER!"));
        timer->stop(); // 停止计时器
    }

}

void GameWindow::setwh(int x, int y)
{

    w=x;
    h=y;
}

bool GameWindow::isCollide()
{
    int x=mysnake->snake[0].x();
    int y=mysnake->snake[0].y();
    std::pair<int,int>pos(x,y);
    if(occupiedPositions.contains(pos)){
        return true;
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
    update();
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

bool GameWindow::checkborder()
{
    QRectF border(Node::getWidth(),Node::getHeight(),w-2*Node::getWidth(),h-2*Node::getHeight());
    if(border.contains(mysnake->snake[0])){
        return false;
    }else return true;
}

void GameWindow::initObstacle(int num)
{
    QRandomGenerator *generator = QRandomGenerator::global();
    int unitWid = w / Node::getWidth();
    int unitHgt = h / Node::getHeight();
    for (int i = 0; i < num;) {
        int x = generator->bounded(1, unitWid - 1);
        int y = generator->bounded(1, unitHgt - 1);
        std::pair<int, int> position(x*Node::getWidth(), y*Node::getHeight());

        // 检查位置是否已占用
        if (occupiedPositions.find(position) != occupiedPositions.end()) {
            continue;  // 重新生成随机坐标
        }
        //障碍物不能出现在蛇的初始位置
        int x1=w-Node::getWidth();
        int x2=w+Node::getWidth();
        int y1=h-Node::getHeight();
        int y2=h+Node::getHeight();
        if(x>=x1&&x<=x2&&y>=y1&&y<=y2){
            continue;
        }
        occupiedPositions.insert(position);
        i++;  // 增加计数器
    }
}

bool GameWindow::checkFoodPos()
{
    QRectF* f=food->getFood();
    int x=f->x();
    int y=f->y();
    std::pair<int,int>pos(x*Node::getWidth(),y*Node::getHeight());
    if(occupiedPositions.contains(pos)){
        return true;
    }else return false;
}

bool GameWindow::checknext()
{
    mysnake->addhead();
    if(biteSelf()||checkborder()||isCollide()){
        mysnake->deletehead();
        return true;
    }else{
        mysnake->deletehead();
        return false;
    }
}

void GameWindow::drawGrid(QPainter& painter)
{
    QPen pen;
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
}

void GameWindow::drawWalls(QPainter& painter)
{
    QPixmap pix(":/wall.png");
    for (int i = 0; i < h / Node::getHeight(); i++) {
        for (int j = 0; j < w / Node::getWidth(); j++) {
            QRectF* p = walls[i][j].getWall();
            if (p != nullptr) {
                painter.drawPixmap(p->left(), p->top(), Node::getWidth(), Node::getHeight(), pix);
            }
        }
    }
}

void GameWindow::drawObstacles(QPainter& painter)
{
    QPixmap pix(":/wall.png"); // 假设你有一个障碍物图像
    for (auto it = occupiedPositions.begin(); it != occupiedPositions.end(); it++) {
        int x = it->first;
        int y = it->second;
        painter.drawPixmap(x, y, Node::getWidth(), Node::getHeight(), pix);
    }
}

void GameWindow::drawFood(QPainter& painter)
{
    QPixmap pix(":/china.png");
    painter.drawPixmap(food->getFood()->left(), food->getFood()->top(), Node::getWidth(), Node::getHeight(), pix);
}

void GameWindow::drawSnake(QPainter &painter)
{
    QPixmap pix;
    // 绘制蛇
    for (int i = 0; i < mysnake->snake.length(); i++) {
        QRectF temp = mysnake->snake[i];
        int direct = mysnake->getDirection();
        if (i == 0) {
            // 画蛇头
            if (direct == dir::UP) {
                pix.load(":/snakeHeadUp.png");
            } else if (direct == dir::DOWN) {
                pix.load(":/snakeHeadDown.png");
            } else if (direct == dir::LEFT) {
                pix.load(":/snakeHeadLeft.png");
            } else {
                pix.load(":/snakeHeadRight.png");
            }
            painter.drawPixmap(temp.x(), temp.y(), Node::getWidth(), Node::getHeight(), pix);
        } else {
            // 画蛇尾
            pix.load(":/snakeTail.png");
            painter.drawPixmap(temp.x(), temp.y(), Node::getWidth(), Node::getHeight(), pix);
        }
    }
}


void GameWindow::timeout()
{
    QPainter painter;
    QPen pen;
    QRectF* f=food->getFood();
    if(mysnake->snake[0].intersects(*f)){
        mysnake->addLength();
        score++;
        ui->scoreui->setText(QString("得分: %1").arg(score)); // 更新得分显示
        delete food;
        addReward();
    }//吃到食物延长蛇，并重新生成食物
    while(checkFoodPos()){
        delete food;
        addReward();
    }//检查食物是否与障碍物重叠，重叠就重新生成食物
    mysnake->deletetail();
    mysnake->addhead();
    update();
}
