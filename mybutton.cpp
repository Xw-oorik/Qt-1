#include "mybutton.h"

#include<QPainter>


MyButton::MyButton(QWidget *parent):QWidget(parent)
{

}
void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    // 加载图片
    m_normal.load(normal);
    m_hover.load(hover);
    m_press.load(pressed);
    m_current = m_normal;
    // 设置按钮和图片大小一致
    setFixedSize(m_normal.size());
}

void MyButton::mouseMoveEvent(QMouseEvent *ev)
{
    //鼠标被按下，发射自定义信号
    emit clicked();
    m_current=m_press;
    update();
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev); //不使用这个参数，编译给我报错
    m_current = m_normal;
    update();
}

void MyButton::enterEvent(QEvent *ev)
{
    Q_UNUSED(ev); //不使用这个参数，编译给我报错
    m_current = m_hover;
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev); //不使用这个参数，编译给我报错
    m_current = m_normal;
    update();
}
void MyButton::paintEvent(QPaintEvent *ev)//图片显示，绘图
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(), m_current);
}


