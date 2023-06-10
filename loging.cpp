#include "loging.h"
#include "ui_loging.h"

loging::loging(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loging)
{
    ui->setupUi(this);
    setFixedSize(337,336);
}

loging::~loging()
{
    delete ui;
}
