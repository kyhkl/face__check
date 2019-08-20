#include "can/socketcan.h"
#include <QPushButton>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

static int sockwfd = -1;
static int nbytes;

static struct can_frame wframe;
static struct sockaddr_can addr;
static struct ifreq wifr;
//char ifname[5];

SocketCAN::SocketCAN(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("CAN总线测试"));
    // set the background color
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xcc, 0xff, 0xff));
    this->setPalette(palette);

    //this->setFixedSize(800, 480);
    teRecv = new QTextEdit();
    teRecv->setReadOnly(true);

    gbSettings = new QGroupBox();
    gbSettings->setMinimumWidth(200);


    cbCanID = new QComboBox;
    cbCanID->setMinimumHeight(50);
    cbCanID->setFont(QFont("helvetica", 18));
    cbCanID->addItem(tr("can0"));
    cbCanID->addItem(tr("can1"));
    cbCanID->setCurrentIndex(0);

  //  lblBaudrate = new QLabel(tr("波特率"));
  //  lblBaudrate->setMinimumHeight(50);
    cbBaudrate = new QComboBox;
    cbBaudrate->setMinimumHeight(50);
    cbBaudrate->setFont(QFont("helvetica", 18));
    cbBaudrate->addItem(tr("1000kbps"));
    cbBaudrate->addItem(tr("800kbps"));
    cbBaudrate->addItem(tr("500kbps"));
    cbBaudrate->addItem(tr("250kbps"));
    cbBaudrate->addItem(tr("125kbps"));
    cbBaudrate->addItem(tr("100kbps"));
    cbBaudrate->addItem(tr("50kbps"));
    cbBaudrate->addItem(tr("20kbps"));
    cbBaudrate->addItem(tr("10kbps"));
    cbBaudrate->addItem(tr("5kbps"));
    cbBaudrate->setCurrentIndex(4);


    btnConnect = new QPushButton(tr("连接"));
    btnConnect->setMinimumHeight(50);
    connect(btnConnect, SIGNAL(clicked()), this, SLOT(slotOnBtnConnectClicked()));

    btnDisconnect = new QPushButton(tr("断开连接"));
    btnDisconnect->setMinimumHeight(50);
    btnDisconnect->setEnabled(false);
    connect(btnDisconnect, SIGNAL(clicked()), this, SLOT(slotOnBtnDisconnectClicked()));

    btnSendMsg = new QPushButton(tr("发送"));
    btnSendMsg->setEnabled(false);
    btnSendMsg->setMinimumHeight(50);
    connect(btnSendMsg, SIGNAL(clicked()), this, SLOT(slotOnBtnSendMsgClicked()));

    lblMsgToSnd = new QLabel(tr("cantest"));
    lblMsgToSnd->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lblMsgToSnd->setMinimumHeight(50);
    lblMsgToSnd->setFont(QFont("helvetica", 18));
    lblMsgToSnd->setStyleSheet("color:blue");
    lblMsgToSnd->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vLayoutSettings = new QVBoxLayout;
    vLayoutSettings->addWidget(cbCanID);
//    vLayoutSettings->addWidget(lblBaudrate);
    vLayoutSettings->addWidget(cbBaudrate);
    vLayoutSettings->addStretch();
    vLayoutSettings->addWidget(btnConnect);
    vLayoutSettings->addWidget(btnDisconnect);
    vLayoutSettings->addWidget(btnSendMsg);
    vLayoutSettings->addWidget(lblMsgToSnd);

    gbSettings->setLayout(vLayoutSettings);

    QHBoxLayout *hLayoutTop = new QHBoxLayout;
    hLayoutTop->addWidget(teRecv);
    hLayoutTop->addWidget(gbSettings);


    lblStatus = new QLabel(tr("测试设置：帧类型->标准帧 帧格式->数据帧  显示：传输方向 CAN_ID 数据长度 数据[HEX] 数据[ASCII]"));
    lblCompanyInfo = new QLabel(tr("www.embedall.com"));
    lblCompanyInfo->setStyleSheet("color:blue");
    lblCompanyInfo->setAlignment(Qt::AlignCenter);
    lblCompanyInfo->setFont(QFont("helvetica", 18));

    QVBoxLayout *mvLayout = new QVBoxLayout(this);
    mvLayout->addLayout(hLayoutTop);
    mvLayout->addWidget(lblStatus);
    mvLayout->addWidget(lblCompanyInfo);


}

SocketCAN::~SocketCAN()
{
    threadCANRdMonitor->terminate();
    threadCANRdMonitor->wait();
}

void SocketCAN::slotOnBtnConnectClicked()
{
    QString strbaud = cbBaudrate->currentText();
    strbaud.chop(4);

    QString sCanId = cbCanID->currentText();
    QString strcmd = "ifconfig "+ sCanId +" down; ip link set "+ sCanId +" type can bitrate " + strbaud + "000 triple-sampling on; ifconfig "+ sCanId +" up";
    QByteArray bacmd = strcmd.toLatin1();
    system(bacmd.data());

    if ((sockwfd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0){
        perror("Error while opening socket");
        return;
    }


    char *ifname = (char*)malloc(5);
    QByteArray baCaId = sCanId.toLatin1();
    strcpy(ifname,baCaId.data());
    strcpy(wifr.ifr_name, ifname);
    ioctl(sockwfd, SIOCGIFINDEX, &wifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = wifr.ifr_ifindex;

    printf("%s at index %d\n", ifname, wifr.ifr_ifindex);

    if (bind(sockwfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("Error in socket bind");
        return;
    }

    wframe.can_id = 0x123;
    wframe.can_dlc = 7;
    wframe.data[0] = 'c';
    wframe.data[1] = 'a';
    wframe.data[2] = 'n';
    wframe.data[3] = 't';
    wframe.data[4] = 'e';
    wframe.data[5] = 's';
    wframe.data[6] = 't';

    threadCANRdMonitor = new ThreadCANReadMonitor(this);
    strcpy(threadCANRdMonitor->ifname,ifname);
    connect(threadCANRdMonitor, SIGNAL(signalRecvMsg(QByteArray, uint)), this, SLOT(slotMsgReady(QByteArray, uint)));
    threadCANRdMonitor->start();

    cbCanID->setEnabled(false);
    btnConnect->setEnabled(false);
    cbBaudrate->setEnabled(false);
    btnDisconnect->setEnabled(true);
    btnSendMsg->setEnabled(true);

    free(ifname);
}

void SocketCAN::slotOnBtnSendMsgClicked()
{
    nbytes = write(sockwfd, &wframe, sizeof(struct can_frame));
    printf("Wrote %d bytes\n", nbytes);
}

void SocketCAN::slotMsgReady(QByteArray baRecv, uint canid)
{
    static int cnt = 20;
    int fsz = baRecv.size();
    char str[256] = {0};

    if (canid == wframe.can_id)
        sprintf(str, "发送: 0x%08x %d [HEX: ", canid, fsz);
    else
        sprintf(str, "接收: 0x%08x %d [HEX: ", canid, fsz);
    QString strRecv(str);
    for (int i=0; i<fsz; i++)
        strRecv += QString(" %1").arg((uint)baRecv.at(i), 2, 16, QLatin1Char('0'));
    strRecv += "]    " + baRecv; 

    if (++cnt >= 21){
        teRecv->clear();
        cnt = 0;
    }

    teRecv->append(strRecv);
}

void SocketCAN::slotOnBtnDisconnectClicked()
{
    threadCANRdMonitor->terminate();
    threadCANRdMonitor->wait();
    //delete [] threadCANRdMonitor;
    cbCanID->setEnabled(true);
    cbBaudrate->setEnabled(true);
    btnConnect->setEnabled(true);
    btnSendMsg->setEnabled(false);
    btnDisconnect->setEnabled(false);

}
