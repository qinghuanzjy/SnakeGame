#include "startwindow.h"
#include "ui_startwindow.h"
#include"gamewindow.h"


StartWindow::StartWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    setWindowTitle("开始窗口");

}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}


void StartWindow::on_pushButton_clicked()
{
    this->hide();
    gamewindow=new GameWindow(this,diff);
    gamewindow->show();
    connect(gamewindow,&GameWindow::restart,this,[=](){
        gamewindow->hide();  // 隐藏游戏窗口
        this->show();        // 显示开始窗口
    });
}


void StartWindow::on_comboBox_activated(int index)
{
    switch (index) {
    case 0:
        diff=0;
        break;
    case 1:
        diff=1;
        break;
    case 2:
        diff=2;
        break;
    default:
        break;
    }
}



