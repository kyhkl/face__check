/*
功能：主要是显示桌面上的一些模块功能，及时间显示
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config_all.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QtGui/qwindowdefs.h>
#include <QApplication>
#include <QPainter>
#include "set_dlg.h"
#include "config_all.h"



#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);  //去掉标题栏

//定时器
    QTimer *timer = new QTimer(this);
    //新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    //关联定时器计满信号和相应的槽函数
    timer->start(1000);

//设置状态栏
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border:0px}"));//去掉要显示的label边框.
    QPixmap pm;//EAC logo
    pm.load(EAC);
    QLabel *eac_Label;
    eac_Label=new QLabel;
    eac_Label->setPixmap(pm);  //EAC logo显示
    ui->statusbar->addWidget(eac_Label);//添加时间显示

    label_date=new QLabel(this);//显示时间用
    label_date->setStyleSheet("color:white");
    label_date->setText("00:00:00");//在标签上显示时间
    ui->statusbar->addPermanentWidget(label_date);  //显示时间
//加载语言翻译
    install_num=0;
    Translator.load(ENGLISH);
//启用键盘
    p_ipmethod = new IPMethod;
    QWSServer::setCurrentInputMethod(this->p_ipmethod);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
功能：定时时间到了之后，执行此函数
     主要是更新时间,有BUG，需要修改
*/
void MainWindow::timerUpDate()
{
    time = QDateTime::currentDateTime();//获取系统现在的时间
    label_date->setText(time.toString("hh:mm:ss"));//在标签上更新时间

//定时检测语言是否需要翻译,1为英文，0为中文
    if(setDLG.flag_language())
    {
        if(install_num==0)
        {
            qApp->installTranslator(&Translator);
            install_num=1;
        }
    }
    else
    {
        if(install_num==1)
        {
            install_num=0;
            qApp->removeTranslator(&Translator);
        }
    }
     ui->retranslateUi(this);///////////////////////

}

/**********************************************************************/
//1 串口测试
void MainWindow::on_serial_btn_clicked()
{
    serial.show();
    serial.setStyleSheet(QString(COLOUR)); //设置字体颜色
//   serial.setStyleSheet(QString("color:palette(highlight)"));//字体高亮
}
//2 音频测试
void MainWindow::on_audioBtn_clicked()
{
    system("amixer cset numid=1  127");//初始化音量
    system("amixer cset numid=28  80");
    audio.show();
    audio.setStyleSheet(QString(COLOUR));
}
//3 设置按钮
void MainWindow::on_setting_btn_clicked()
{
    setDLG.show();
    setDLG.setStyleSheet(QString(COLOUR));
}

//屏幕校准
void MainWindow::on_tslibBtn_clicked()
{
#if 1

#if 0
    QMessageBox msgBox;
    msgBox.setText("是否进行屏幕校准？校准后需要重启才能生效");
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    switch (ret)
    {
        case QMessageBox::No:
        break;

        case QMessageBox::Yes:
            this->close_show();
            system(TSLIB);
            this->showNormal();
            this->showFullScreen();
        break;
        default:
        break;
    }
#endif
    this->close_show();
    system(TSLIB);
    this->showNormal();
    this->showFullScreen();
    int ret3= QMessageBox::warning(this,tr(""), tr("是否要重新校准？\n\n重启后校准生效"), tr("重新校准"), tr("重启"), tr("取消"));

    switch (ret3)
    {
        case 0:
            this->close_show();
            system(TSLIB);
            this->showNormal();
            this->showFullScreen();
        break;

        case 1:
             system("reboot");
        break;

        case 2:
        break;

        default:
        break;
    }
#endif

}
//关闭所有窗口
void MainWindow::close_show()
{
    serial.close();
    audio.close();
    setDLG.close();
    canDLG.close();
    sqlDLG.close();
    led_keyDLG.close();
    buzzerDLG.close();
}

void MainWindow::on_canBtn_clicked()
{
    canDLG.showMaximized();
}

void MainWindow::on_sqlBtn_clicked()
{
    sqlDLG.show();
}

void MainWindow::on_led_keyBtn_clicked()
{
    led_keyDLG.show();
}

void MainWindow::on_buzzerBtn_clicked()
{
    buzzerDLG.show();
}

