#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_ac_clicked();

    void on_re_clicked();

    void on_do_2_clicked();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
