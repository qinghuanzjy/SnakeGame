#ifndef FAILDIALOG_H
#define FAILDIALOG_H

#include <QDialog>

namespace Ui {
class FailDialog;
}

class FailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FailDialog(QWidget *parent = nullptr);
    ~FailDialog();

private:
    Ui::FailDialog *ui;
};

#endif // FAILDIALOG_H
