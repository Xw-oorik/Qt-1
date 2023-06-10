#ifndef LOGING_H
#define LOGING_H

#include <QDialog>

namespace Ui {
class loging;
}

class loging : public QDialog
{
    Q_OBJECT

public:
    explicit loging(QWidget *parent = nullptr);
    ~loging();

private:
    Ui::loging *ui;
};

#endif // LOGING_H
