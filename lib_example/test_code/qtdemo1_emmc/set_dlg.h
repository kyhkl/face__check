#ifndef SET_DLG_H
#define SET_DLG_H

#include <QDialog>

namespace Ui {
class set_Dlg;
}

class set_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit set_Dlg(QWidget *parent = 0);
    ~set_Dlg();
    int flag_language();   //mainwindow.c要获取这个语言标志值

private slots:
    void on_saveBtn_language_clicked();
    void on_cancel_Btn_clicked();
    void on_saveBtn_time_clicked();

private:
    Ui::set_Dlg *ui;
    void changeEvent(QEvent *e);
    void time_init();
    int flag_lang;

};

#endif // SET_DLG_H
