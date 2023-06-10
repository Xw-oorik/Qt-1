#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_ac_clicked()
{
    //结束模态对话框的阻塞，隐藏
    this->accept();
}

void MyDialog::on_re_clicked()
{
    this->reject();
}

void MyDialog::on_do_2_clicked()
{
    this->done(10); //自定义的返回值
}
