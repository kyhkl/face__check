#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "serial_dlg.h"
#include "audio_dlg.h"
#include "set_dlg.h"
#include <QtCore>
#include <QtCore/QTranslator>
#include "keyPad/ipmethod.h"
#include "can/socketcan.h"
#include "sql/student.h"
#include "led_gpiokey/qtkeyledctrl.h"
#include "buzzer.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void close_show();
     QLabel  *label_date;

     QWSInputMethod *p_ipmethod;

private slots:
    void on_buzzerBtn_clicked();
    void on_led_keyBtn_clicked();
    void on_sqlBtn_clicked();
    void on_canBtn_clicked();
    void timerUpDate();

    void on_audioBtn_clicked();
    void on_setting_btn_clicked();
    void on_serial_btn_clicked();
    void on_tslibBtn_clicked();


private:
    Ui::MainWindow *ui;

    serial_Dlg serial;
    audio_Dlg  audio;
    set_Dlg   setDLG;
    SocketCAN canDLG;
    Student sqlDLG;
    QtKeyLedCtrl led_keyDLG;
    buzzer buzzerDLG;

    QTranslator Translator;
    int install_num;

    QDateTime time;//获取系统现在的时间
};

#endif // MAINWINDOW_H
