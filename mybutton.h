#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QWidget>
class MyButton:public QWidget
{
    Q_OBJECT
public:
    explicit MyButton(QWidget*parent=nullptr);
    void setImage(QString normal,QString hover,QString pressed);
protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void enterEvent(QEvent *ev) ;
    void leaveEvent(QEvent *ev);
     void paintEvent(QPaintEvent* ev);
signals:
    void clicked();

private:
    QPixmap m_normal;
    QPixmap m_press;
    QPixmap m_hover;
    QPixmap m_current;
};

#endif // MYBUTTON_H
