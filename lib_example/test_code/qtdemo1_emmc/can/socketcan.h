#ifndef SOCKETCAN_H
#define SOCKETCAN_H

#define PF_CAN 29
#define AF_CAN 29

#include <QtGui/QWidget>
#include "can/threadcanreadmonitor.h"

class QPushButton;
class QGroupBox;
class QTextEdit;
class QLabel;
class QComboBox;

class SocketCAN : public QWidget
{
    Q_OBJECT
    
public:
    SocketCAN(QWidget *parent = 0);
    ~SocketCAN();

private slots:
    void slotOnBtnConnectClicked();
    void slotOnBtnSendMsgClicked();
    void slotOnBtnDisconnectClicked();

    void slotMsgReady(QByteArray, uint);

private:
    ThreadCANReadMonitor *threadCANRdMonitor;
    QPushButton *btnSendMsg;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QTextEdit *teRecv;
    QLabel *lblMsgToSnd;
    QLabel *lblBaudrate;
    QComboBox *cbBaudrate;
    QComboBox *cbCanID;

    QLabel *lblStatus;
    QLabel *lblCompanyInfo;
    QGroupBox *gbSettings;
};

#endif // SOCKETCAN_H
