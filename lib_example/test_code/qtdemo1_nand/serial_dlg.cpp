#include "serial_dlg.h"
#include "ui_serial_dlg.h"
#include "serial_app.h"
#include <stdio.h>
#include <string.h>
#include  <QtGui>
#include <QtCore/QTranslator>
#include "set_dlg.h"
#include "config_all.h"

serial_Dlg::serial_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serial_Dlg)
{
    ui->setupUi(this);
//    this->setWindowTitle(tr("串口工具"));//设置标题栏
    this->setWindowFlags(Qt::WindowCloseButtonHint );//标题栏只有关闭按钮
    startTimer(100);//定时的时间
    ui->send_Btn->setEnabled(false);
    ui->date_send->textCursor().insertText("0123456789abcdef");
}

serial_Dlg::~serial_Dlg()
{
    delete ui;
}

//ComboBox能否使用状态
void serial_Dlg::setComboBoxEnabled(bool status)
{
    ui->port_comboBox->setEnabled(status);
    ui->speed_comboBox->setEnabled(status);
    ui->datebit_comboBox->setEnabled(status);
    ui->parity_comboBox->setEnabled(status);
    ui->stopbit_comboBox->setEnabled(status);
}


//检测设置的波特率 数据位  停止位  校验位  RS232/485
////////////////////////////////////
char *Port=NULL;
//波特率 数据位  停止位  校验位
static int Speed;
static int Databits;
static int Stopbits;
static int Parity;
static int Mode;
///////////////////////////////////
void serial_Dlg::setSpeed_Date_Stop_Pari()
{
//串口
    QString portName = ui->port_comboBox->currentText();
    if(portName == tr("COM1"))
    {
       Port = SERIAL1;
       Mode = 0;    //RS232
    }
    else if(portName == tr("COM2"))
    {
       Port = SERIAL2;
       Mode = 0;    //RS232
    }
    else  if(portName == tr("COM3"))
    {
        Port=SERIAL3;
         Mode = 0;    //RS232
    }
    else  if(portName == tr("COM4"))
    {
       Port=SERIAL4;
        Mode = 0;    //RS232
    }
    else  if(portName == tr("COM5"))
    {
       Port=SERIAL5;
        Mode = 1;    //RS485
    }
    else  if(portName == tr("COM6"))
    {
       Port=SERIAL6;
        Mode = 1;    //RS485
    }
//    else  if(portName == tr("COM7"))
//    {
//       Port=SERIAL7;
//        Mode = 0;    //RS232
//    }
//    else  if(portName == tr("COM8"))
//    {
//       Port=SERIAL8;
//        Mode = 1;    //RS485
//    }
//    else  if(portName == tr("COM9"))
//    {
//       Port=SERIAL9;
//        Mode = 1;    //RS485
//    }

//波特率
    QString speedName = ui->speed_comboBox->currentText();
    if(speedName == tr("115200") )
        Speed = 115200;
    else  if(speedName == tr("9600") )
        Speed = 9600;
    else if(speedName == tr("4800"))
        Speed = 4800;
    else if(speedName == tr("38400"))
        Speed = 38400;
    //  printf("speed:%d\n",Speed);
//停止位
    QString stopbitsName = ui->stopbit_comboBox->currentText();
    if(stopbitsName == tr("1"))
       Stopbits = 1;
    else if(stopbitsName == tr("2"))
       Stopbits = 2;
    //  printf("Stopbits:%d\n",Stopbits);
//数据位
    QString databitsName = ui->datebit_comboBox->currentText();
    if(databitsName == tr("8"))
        Databits = 8;
    else if(databitsName == tr("7"))
        Databits = 7;
    //  printf("Databits:%d\n",Databits);
//校验位
    QString parityName = ui->parity_comboBox->currentText();
    if(parityName == tr("NONE"))
       Parity='N';
    else if(parityName == tr("ODD"))
       Parity='O';
    else if(parityName == tr("EVEN"))
        Parity='E';
    //  printf("1Parity:%c\n",Parity);
}




int fd2,fd3;
int nwrite;
int nread;
char buf_recv[5120];

pthread_t tid;
void *RecvDate(void *args)
{
    while (1) //循环读取数据
    {
        while((nread = read(fd2, buf_recv, 5120))>0)
        {
            break;
        }
    }
}


void serial_Dlg::on_open_close_Btn_clicked()
{
    if((ui->open_close_Btn->text() == "打开串口" ) | (ui->open_close_Btn->text() == "OPEN" ) )
    {

        setSpeed_Date_Stop_Pari();//读取端口 波特率 数据位  停止位  校验位
        fd2=OpenDev(Port);
        if(fd2<0 )
        {
            QMessageBox::critical(this, tr("打开失败"), tr("未能打开串口 ") + Port + tr("\n该串口设备不存在或已被占用"), QMessageBox::Ok);
            return;
        }
        else
        {
            ui->label_select->setStyleSheet(SERIAL_NOR);//选择正常对号图片
            ui->open_close_Btn->setText(tr("关闭串口"));

            set_speed(fd2,Speed);//设置波特率
            //数据位为 8  停止位为 1 校验位 NONE
            if (set_Parity(fd2,Databits,Stopbits,Parity,Mode) ==  -1)
            {
                printf("Set Parity Errorn\n");
                exit (0);
            }
            setComboBoxEnabled(false);//打开串口后 combobox 不能设置
            ui->send_Btn->setEnabled(true);

            memset(buf_recv,0,sizeof(buf_recv));
            if(pthread_create(&tid, NULL, RecvDate, NULL) != 0)//创建线程进行接收数据
            {
                exit(1);
            }
        }


    }
    else
    {
        ui->label_select->setStyleSheet(SERIAL_DIS);
        ui->open_close_Btn->setText(tr("打开串口"));

        setComboBoxEnabled(true);
        ui->send_Btn->setEnabled(false);
        CloseDev(fd2);
        memset(buf_recv,0,sizeof(buf_recv));
    }
}

//定时扫描把要显示的数字显示在界面上
void  serial_Dlg::timerEvent(QTimerEvent *t)
{
   if((ui->open_close_Btn->text() == "关闭串口") | (ui->open_close_Btn->text() == "STOP"))//是否打开串口
   {
        ui->date_recv->insertPlainText(buf_recv);
        memset(buf_recv,0,sizeof(buf_recv));
        ui->date_recv->moveCursor(QTextCursor::End);//把光标移动到最后
   }
}


//发送按钮
void serial_Dlg::on_send_Btn_clicked()
{
    //QSting类型变量转化成字符转
    QString content;
    content=ui->date_send->toPlainText();
    QByteArray ba = content.toLatin1();
    const char * ss=ba.data();
    nwrite = write(fd2,ss,strlen(ss));
    if(nwrite==-1)
    {
         perror("write");
    }
}

//两个清空按钮
void serial_Dlg::on_clr_recv_btn_clicked()
{
    ui->date_recv->clear();
}
void serial_Dlg::on_clr_send_btn_clicked()
{
    ui->date_send->clear();
}


//关闭窗口
void serial_Dlg::closeEvent(QCloseEvent *event)
{
    ui->label_select->setStyleSheet(SERIAL_DIS);
    ui->open_close_Btn->setText(tr("打开串口"));
    setComboBoxEnabled(true);
    ui->send_Btn->setEnabled(false);
    CloseDev(fd2);
    ui->date_recv->clear();
    ui->date_send->clear();
    memset(buf_recv,0,sizeof(buf_recv));
}

//////////////////////////////////////////////////////////////
//下面是0-f按键
//////////////////////////////////////////////////////////////
void serial_Dlg::on_btn_0_clicked()
{
    ui->date_send->textCursor().insertText("0");
}

void serial_Dlg::on_btn_1_clicked()
{
    ui->date_send->textCursor().insertText("1");
}

void serial_Dlg::on_btn_2_clicked()
{
    ui->date_send->textCursor().insertText("2");
}

void serial_Dlg::on_btn_3_clicked()
{
    ui->date_send->textCursor().insertText("3");
}

void serial_Dlg::on_btn_4_clicked()
{
    ui->date_send->textCursor().insertText("4");
}

void serial_Dlg::on_btn_5_clicked()
{
    ui->date_send->textCursor().insertText("5");
}

void serial_Dlg::on_btn_6_clicked()
{
    ui->date_send->textCursor().insertText("6");
}

void serial_Dlg::on_btn_7_clicked()
{
    ui->date_send->textCursor().insertText("7");
}

void serial_Dlg::on_btn_8_clicked()
{
    ui->date_send->textCursor().insertText("8");
}

void serial_Dlg::on_btn_9_clicked()
{
    ui->date_send->textCursor().insertText("9");
}

void serial_Dlg::on_btn_a_clicked()
{
    ui->date_send->textCursor().insertText("a");
}

void serial_Dlg::on_btn_b_clicked()
{
    ui->date_send->textCursor().insertText("b");
}

void serial_Dlg::on_btn_c_clicked()
{
    ui->date_send->textCursor().insertText("c");
}

void serial_Dlg::on_btn_d_clicked()
{
    ui->date_send->textCursor().insertText("d");
}

void serial_Dlg::on_btn_e_clicked()
{
    ui->date_send->textCursor().insertText("e");
}

void serial_Dlg::on_btn_f_clicked()
{
    ui->date_send->textCursor().insertText("f");
}

//切换语言版本
void serial_Dlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

