#include "returnwindow.h"
#include "ui_returnwindow.h"

ReturnWindow::ReturnWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReturnWindow)
{
    ui->setupUi(this);
}

ReturnWindow::~ReturnWindow()
{
    delete ui;
}

void ReturnWindow::on_return_2_clicked()
{
    this->hide();
    emit toStart();
}

