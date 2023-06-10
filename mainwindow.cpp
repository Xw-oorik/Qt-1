#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTime>
#include<QTimer>
#include<QDebug>
#include"mydialog.h"
#include <QMessageBox>
#include<QFileDialog>
#include<QFontDialog>
#include<QApplication>
#include<QColorDialog>
#include<QPainter>
#include<QInputDialog>
#include <QProgressDialog>
#include <QCloseEvent>
#include <QResizeEvent>
#include"mybutton.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建定时器对象
    QTimer *tt=new QTimer(this);
    //设置精度
    tt->setTimerType(Qt::PreciseTimer);
    //按钮点击事件，周期性获得当前时间
    connect(ui->startBtn,&QPushButton::clicked,this,[=]()
    {
        //启动定时器
        if(tt->isActive())//如果是启动的状态
        {
            tt->stop();  //关闭 ，设为开始
            ui->startBtn->setText("开始");
        }
        else{
            ui->startBtn->setText("关闭");
            tt->start(1000);//1s
        }
    });
    connect(tt,&QTimer::timeout,this,[=]()
    {
       //获得当前时间
        QTime tm=QTime::currentTime();
        QString str=tm.toString("hh:mm::ss.zzz");
        ui->labshow->setText(str);
    });
    connect(ui->end,&QPushButton::clicked,this,&MainWindow::close);//退出标志

   // setMaximumSize(600,600);
    //setMinimumSize(300,300);
    setWindowTitle("hello hexo");//标题
    setWindowIcon(QIcon(":/img/favicon2.ico"));//图标
    connect(this,&MainWindow::windowTitleChanged,this,[=](const QString &title )
    {
        qDebug()<<"新的标题是:"<<title;
    });
    connect(this,&MainWindow::windowIconChanged,this,[=](const QIcon &icon )
    {
        qDebug()<<"新的图标是:"<<icon;
    });

    //设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&MainWindow::customContextMenuRequested,this,[=](const QPoint& p){
        //创建一个空菜单
        QMenu menu;
        menu.addAction("点餐");
        menu.addAction("住宿");
        menu.addAction("游玩");
        menu.exec(QCursor::pos());//鼠标右键点击的坐标位置，相对于系统屏幕的，而不是当前窗口

    });

    //相映菜单项点击后信号
    connect(ui->openaction,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"clicked","新建成功");
    });
    connect(ui->actionopen,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"clicked","打开成功");
    });
    connect(ui->actionclose,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"clicked","关闭成功");
    });
    //给工具栏添加按钮和单行输入框
    ui->toolBar->addWidget(new QPushButton("搜索"));
    QLineEdit *li=new QLineEdit;
    li->setMaximumWidth(300);
    ui->toolBar->addWidget(li);
    //添加新的一个工具栏
    QToolBar* toolbar=new QToolBar("toolbar2");
    this->addToolBar(Qt::LeftToolBarArea,toolbar);

    //给状态栏添加控件
    ui->statusbar->showMessage("我是状态栏.",4000); //显示4秒，自动清除
    QPushButton* button=new QPushButton("当前行");
    ui->statusbar->addWidget(button);
    QLabel *label=new QLabel("1");
    ui->statusbar->addWidget(label);
    QTimer::singleShot(5000,this,[=](){
        button->show();
        label->show();  //显示出来,showMessage清除后，被覆盖的控件是不会显示的，要手动调用显示
    });

    //给自定义按钮设置图片
    ui->mybt->setImage(":/img/xw1.png",":/img/xw2.png",":/img/xw3.png");
    //处理自定义按钮的鼠标点击事件
    connect(ui->mybt,&MyButton::clicked,this,[=]{
        QMessageBox::information(this, "自定义按钮", "点我...");
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_yd_clicked() //移动
{
    //获取当前窗口位置
    QRect rect=this->frameGeometry();
    //移动 从当前窗口位置左上角 向右下移动
    move(rect.topLeft()+QPoint(rand()%50,rand()%30));

}

void MainWindow::on_yd1_clicked()  //获取位置
{
    QRect rect=this->frameGeometry();
    qDebug()<<"左上角："<<rect.topLeft()
           <<"右上角："<<rect.topRight()
             <<"左下角："<<rect.bottomLeft()
               <<"右下角："<<rect.bottomRight()
                 <<"宽度："<<rect.width()
                   <<"高度："<<rect.height();

}

void MainWindow::on_yd2_clicked()  //修改窗口位置和尺寸
{
    int x=100+rand()%500;
    int y=100+rand()%500;
    int width=this->width()+50;
    int height=this->height()+30;
    setGeometry(x,y,width,height);
}

void MainWindow::on_rebuild_clicked()  //重新设置标题和图标
{
    this->setWindowIcon(QIcon("F:\\PotBa\\public\\favicon1.ico"));
    this->setWindowTitle("新标题");
}

void MainWindow::on_module_clicked()
{
    MyDialog dig;
    connect(&dig,&MyDialog::finished,this,[=](int res){
        qDebug()<<"finished: "<<res;
    });
    connect(&dig,&MyDialog::accepted,this,[=](){
        qDebug()<<"accept 发射--: ";
    });
    connect(&dig,&MyDialog::rejected,this,[=](){
        qDebug()<<"rejected 发射--:" ;
    });
    int ret=dig.exec();
    if(ret==QDialog::Accepted){ //返回1
        qDebug()<<"accept clicked";
    }
    else if(ret==QDialog::Rejected){ //返回0
        qDebug()<<"reject clicked";
    }
    else{
        qDebug()<<"done clicked";
    }
}

void MainWindow::on_msgbox_clicked()
{
    QMessageBox::about(this,"about","这是一个简单的测试消息提示框！");
    QMessageBox::critical(this,"critical","这是一个测试错误对话框!");
    int ret=QMessageBox::question(this,"question","你要保存修改的内容吗？？",
                                  QMessageBox::Save|QMessageBox::Cancel,
                                  QMessageBox::Cancel);
    if(ret==QMessageBox::Save)
    {
        QMessageBox::information(this,"information","恭喜保存成功！");
    }
    else if(ret==QMessageBox::Cancel)
    {
        QMessageBox::warning(this, "warning", "你放弃了保存, ┭┮﹏┭┮ !!!");
    }

}

void MainWindow::on_mulu_clicked()
{
#if 0
    QString arg("Text files(*.txt *.md");//指定以这个格式过滤,意思只显示这两种类型文件
    //打开多个文件，得到文件的绝对路径
    QStringList filenames=QFileDialog::getOpenFileNames(
                this,"open files","F:\\",
                "Images(*.png *.jpg);;Text files(*.txt *.md)",
                &arg);  //指定了多个过滤器，默认是第一个。我这里手动指定是.txt *.md的
    QString names;
    for(auto x:filenames)
    {
        names+=x+"%%%";
    }
    //以QMessageBox提示框显示
     QMessageBox::information(this,"打开文件(s)","您选择的文件是: "+names);

#else
    QString filename=QFileDialog::getSaveFileName(this,"保存文件","F:\\PotBa");
    QMessageBox::information(this,"保存文件成功！","保存的文件是:"+filename);
#endif

}

void MainWindow::on_font_clicked()
{
    bool ok;
    bool is=true;                                                 //默认不倾斜，这里设置倾斜 true
    QFont font=QFontDialog::getFont(&ok,QFont("微软雅黑",12,QFont::Bold,is),this,"选择字体");
    qDebug()<<" ok is : "<<ok;
    //作用到全部窗口 和label标签
    ui->fontlabel->setFont(font);
    QApplication::setFont(font, nullptr);//默认
}

void MainWindow::on_colorbt_clicked()
{
    QColor col=QColorDialog::getColor();
    //绘图操作
    QBrush brush(col);
    QRect rect(0,0,ui->colorshow->width(),ui->colorshow->height());
    QPixmap pix(rect.width(), rect.height());
    QPainter p(&pix);
    p.fillRect(rect, brush);
    ui->colorshow->setPixmap(pix);
    QString text = QString("red: %1, green: %2, blue: %3, 透明度: %4")
               .arg(col.red()).arg(col.green()).arg(col.blue()).arg(col.alpha());
    ui->colorpt->setText(text);
}

#define LINE
void MainWindow::on_chat_clicked()
{
#ifdef INT
    int res=QInputDialog::getInt(this,"设置年龄","年龄:",0,0,100,1);
    QMessageBox::information(this,"成功！","年龄设置为:"+QString::number(res));

#endif

#ifdef ITEM
    QStringList  list;
    list<<"麻婆豆腐"<<"红烧肉"<<"锅包肉";
    QString str=QInputDialog::getItem(this,"菜单","选择菜品:",list,1,true);
    QMessageBox::information(this,"点菜成功！","点的菜为:"+str);
#endif

#ifdef TEXT                                              //默认设置是123456密码
    QString text = QInputDialog::getText(this, "密码", "请输入新的密码", QLineEdit::Password, "123456");
    QMessageBox::information(this, "密码", "您设置的密码是: " + text);
#endif

#ifdef LINE
    QString ss=QInputDialog::getMultiLineText(this,"漂流瓶","写给30年后的自己","你好,30年后的xxx:");
    QMessageBox::information(this, "漂流瓶", "您对30年后的自己写的话是: " + ss);
#endif
}

void MainWindow::on_download_clicked()
{
        //创建进度条对话框窗口对象
        QProgressDialog *pro=new QProgressDialog("正在下载..","取消下载",0,100,this);
        //初始化显示进度条窗口
        pro->setWindowTitle("请稍等..");
        pro->setWindowModality(Qt::WindowModal);//模态
        pro->show();
        //更新进度条，利用定时器演示
        static int value=0;
        QTimer *timer =new QTimer();
        connect(timer,&QTimer::timeout,this,[=](){
           pro->setValue(value);
           value++;
           if(value>pro->maximum())
           {
               //关掉定时器
               timer->stop();
               value=0;
               //手动去析构对象
               delete pro;
               delete timer;
           }
        });

        //点击取消下载，接收到信号，析构对象
        connect(pro,&QProgressDialog::canceled,this,[=](){
           timer->stop();
           value=0;
           delete pro;
           delete timer;
        });


        timer->start(50);//50毫秒更新一次
}
//添加并重写主窗口的事件处理函数
void MainWindow::closeEvent(QCloseEvent *ev)
{
    QMessageBox::Button btn=QMessageBox::question(this,"关闭窗口","你确定要关闭窗口吗?");
    if(btn==QMessageBox::Yes)
    {
        //接收并处理这个事件
        ev->accept();
    }
    else{
        ev->ignore();
    }
}
void MainWindow::resizeEvent(QResizeEvent *ev)
{
    qDebug()<<"oldsize:"<<ev->oldSize()<<"newsize::"<<ev->size();
}
