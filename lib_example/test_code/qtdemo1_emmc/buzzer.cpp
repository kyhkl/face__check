#include "buzzer.h"
#include "ui_buzzer.h"
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

//#define BUZZERDEVICE "/dev/buzzer"

buzzer::buzzer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buzzer)
{
    ui->setupUi(this);
    buzzerState = false;

    this->setWindowTitle(tr("蜂鸣器测试"));
    setFixedSize(260,180);
    initbzr();
}

buzzer::~buzzer()
{
    delete ui;
}


void buzzer::initbzr()
{
    int fd_export = ::open("/sys/class/gpio/export", O_WRONLY);
    if (fd_export < 0)
    {
            qDebug("Export Buzzer_GPIO failed!");
    }
    else
    {
        char* blkNum = "100";
     ::write(fd_export,blkNum,strlen(blkNum));

    }
    ::close(fd_export);

    int fd_dir = ::open("/sys/class/gpio/gpio100/direction", O_WRONLY);
    if (fd_dir < 0)
    {
            qDebug("Set the dirction of Buzzer_GPIO failed!");
    }
    else
    {
        char* dir = "out";
        ::write(fd_export,dir,strlen(dir));
    }
    ::close(fd_dir);
}

void buzzer::on_buzzerCtrlBtn_clicked()
{
    static int fd_buzzer;
//    fd_buzzer = ::open(BUZZERDEVICE, O_WRONLY);
//    if (fd_buzzer < 0)
//    {
//        perror("Buzzer Device Open Failed");
//        exit(-1);
//    }
    fd_buzzer = ::open("/sys/class/gpio/gpio100/value", O_WRONLY);
    if (fd_buzzer < 0)
    {
            perror("Buzzer Device Open Failed");
            exit(-1);
    }
    if (!buzzerState)
    {
       write(fd_buzzer, "1", strlen("1"));
       ui->buzzerCtrlBtn->setText("关闭蜂鸣器");
       buzzerState = true;
    }
    else
    {
        write(fd_buzzer, "0", strlen("0"));
        ui->buzzerCtrlBtn->setText("打开蜂鸣器");
        buzzerState = false;
    }
    ::close(fd_buzzer);

}
