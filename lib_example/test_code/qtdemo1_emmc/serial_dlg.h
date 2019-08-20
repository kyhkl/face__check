#ifndef SERIAL_DLG_H
#define SERIAL_DLG_H

#include <QDialog>

namespace Ui {
class serial_Dlg;
}

class serial_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit serial_Dlg(QWidget *parent = 0);
    ~serial_Dlg();
    void timerEvent(QTimerEvent *);//定时器
    void setSpeed_Date_Stop_Pari();//
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *e);
protected:
   // void setActionsEnabled(bool status);
    void setComboBoxEnabled(bool status);

private slots:

    void on_clr_recv_btn_clicked();

    void on_open_close_Btn_clicked();

    void on_clr_send_btn_clicked();

    void on_send_Btn_clicked();

    void on_btn_0_clicked();

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_a_clicked();

    void on_btn_b_clicked();

    void on_btn_c_clicked();

    void on_btn_d_clicked();

    void on_btn_e_clicked();

    void on_btn_f_clicked();


private:
    Ui::serial_Dlg *ui;
    int langu_flag;
};




#endif // SERIAL_DLG_H
