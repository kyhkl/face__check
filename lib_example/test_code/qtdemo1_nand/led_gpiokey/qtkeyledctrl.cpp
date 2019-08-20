#include "qtkeyledctrl.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QTimer>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/poll.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LEDDEVICE "/sys/class/leds/user-led:red/brightness"
//#define KEYDEVICE "/dev/input/event0"

QtKeyLedCtrl::QtKeyLedCtrl(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("LED测试"));
//    move((this->width() - this->width())/2, (this->height() - this->height())/2);
    setFixedSize(260,150);
//    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::WindowCloseButtonHint );//标题栏只有关闭按钮

    uiInit();
    //connect(chbLed, SIGNAL(clicked()), this, SLOT(slotLedCtrl()));/////
    //connect(chbLed, SIGNAL(clicked()), this, SLOT(slotLedCtrl()));
    connect(btnLed, SIGNAL(clicked()), this, SLOT(slotOnBtnLedclicked()));
    // 定时器线程
//    _keyThread = new QThread;
//    _keyTimer = new QTimer;
//    _keyTimer->setSingleShot(false);
//    _keyTimer->start(100);
//    _keyTimer->moveToThread(_keyThread);
//    connect(_keyTimer, SIGNAL(timeout()), this, SLOT(slotKeyCtrl()), Qt::DirectConnection);
//    _keyThread->start();
}

QtKeyLedCtrl::~QtKeyLedCtrl()
{
//    _keyThread->quit();
//    _keyThread->wait();
//    delete _keyTimer;
//    delete _keyThread;
}


void QtKeyLedCtrl::uiInit()
{
//    lblBtnInfo = new QLabel(tr("底板按键状态信息"));
//    teBtnMsg = new QTextEdit();
//    teBtnMsg->setEnabled(false);
//    teBtnMsg->setStyleSheet("color:blue");
//    QVBoxLayout *vLayoutKey = new QVBoxLayout;
//    vLayoutKey->addWidget(lblBtnInfo);
//    vLayoutKey->addWidget(teBtnMsg);

//    QGroupBox *gbKey = new QGroupBox(tr("按键控制"));
//    gbKey->setLayout(vLayoutKey);

/*
    chbLed = new QCheckBox(tr("LED"));
    QVBoxLayout *vLayoutLed = new QVBoxLayout;
    vLayoutLed->addWidget(chbLed);
    QGroupBox *gbLed = new QGroupBox(tr("LED控制"));
    gbLed->setLayout(vLayoutLed);
*/
    btnLed = new QPushButton(tr(""));
    static int fd_led;
    fd_led = ::open(LEDDEVICE, O_RDWR);
    write(fd_led, "0", strlen("0"));
    btnLed->setText("开灯");
    ::close(fd_led);
//    btnLed->setEnabled(false); //////////////////
    QVBoxLayout *vLayoutLed = new QVBoxLayout;
    vLayoutLed->addWidget(btnLed);
    QGroupBox *gbLed = new QGroupBox(tr("LED控制"));
    gbLed->setLayout(vLayoutLed);


//    lblCompany = new QLabel(tr("www.embedall.com"));
//    lblCompany->setStyleSheet("color:blue");
//    lblCompany->setAlignment(Qt::AlignCenter);


    QVBoxLayout *mvLayout = new QVBoxLayout(this);
//    mvLayout->addWidget(gbKey);
    mvLayout->addWidget(gbLed);
//    mvLayout->addWidget(lblCompany);
}

void QtKeyLedCtrl::slotOnBtnLedclicked()
{
    char buf[3] = {};
    static int fd_led;
    fd_led = ::open(LEDDEVICE, O_RDWR);
    if (-1 == fd_led)
    {
        perror("Led Device Open Failed");
        exit(-1);
    }
    ::read(fd_led, buf, sizeof(buf));
    if ('0' == buf[0])
    {
        write(fd_led, "1", strlen("1"));
        btnLed->setText("关灯");
    }
    else
    {
        write(fd_led, "0", strlen("0"));
        btnLed->setText("开灯");
    }
    ::close(fd_led);
}

/*
void QtKeyLedCtrl::slotLedCtrl()
{
    static bool ledStatus = false;
    static int fd_led;
    fd_led = ::open(LEDDEVICE, O_RDWR);
    if (-1 == fd_led)
    {
        perror("Led Device Open Failed");
        exit(-1);
    }
    if (ledStatus)
    {
        ledStatus = false;
        write(fd_led, "1", strlen("1"));
    }
    else
    {
        ledStatus = true;
        write(fd_led, "0", strlen("0"));
    }
    ::close(fd_led);
}
*/
/*
void QtKeyLedCtrl::slotKeyCtrl()
{
    int fd_key;
    static struct input_event ev;
    static int ret;

    fd_key = ::open(KEYDEVICE, O_RDONLY);
    if (-1 == fd_key)
    {
        perror("Key Device Open Failed");
        exit(-1);
    }
    ret = ::read(fd_key, &ev, sizeof(struct input_event));

    if (ret == sizeof(struct input_event))
    {
        switch (ev.type)
        {
        case EV_SYN:
            break;
        case EV_KEY:
            if (ev.value)
            {
                teBtnMsg->append(QString("key[0x%1=%2] down").arg(ev.code, 0, 16).arg(ev.code));
            }
            else
            {
                teBtnMsg->append(QString("key[0x%1=%2] up").arg(ev.code, 0, 16).arg(ev.code));
            }
            break;
        case EV_ABS:
        default:
            teBtnMsg->append(QString("ev.type=%1 ev.code=%2 ev.value=%3\n").arg(ev.type).arg(ev.code).arg(ev.value));
            break;
        }
    }
    else
    {
        teBtnMsg->append(QString("Wrong Data Read, size[%1]\n").arg(ret));
    }

    ::close(fd_key);
}
*/
