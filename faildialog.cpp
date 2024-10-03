#include "faildialog.h"
#include "ui_faildialog.h"

FailDialog::FailDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FailDialog)
{
    ui->setupUi(this);
}

FailDialog::~FailDialog()
{
    delete ui;
}
