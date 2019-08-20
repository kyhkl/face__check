#ifndef QTKEYLEDCTRL_H
#define QTKEYLEDCTRL_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>
#include <QTimer>
#include <QCheckBox>
#include <QThread>

class QtKeyLedCtrl : public QWidget
{
    Q_OBJECT

public:
    QtKeyLedCtrl(QWidget *parent = 0);
    ~QtKeyLedCtrl();

private:
    void uiInit();
public slots:
//    void slotLedCtrl();
    void slotOnBtnLedclicked();
//    void slotKeyCtrl();

private:
//    QLabel *lblBtnInfo;
    QTextEdit *teBtnMsg;

    //QCheckBox *chbLed;
    QPushButton *btnLed;

//    QThread *_keyThread;
//    QTimer *_keyTimer;
//    QLabel *lblCompany;
};

#endif // QTKEYLEDCTRL_H
