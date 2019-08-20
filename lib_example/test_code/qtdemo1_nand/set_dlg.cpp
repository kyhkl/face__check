/*
功能：是桌面上的设置功能，主要包括  时间设置和语言设置
*/

#include "set_dlg.h"
#include "ui_set_dlg.h"
#include <QtCore>

set_Dlg::set_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_Dlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint );//标题栏只有关闭按钮
    time_init();         //初始化时间对话框
    flag_lang=0;
}

set_Dlg::~set_Dlg()
{
    delete ui;
}

/*
名称：void time_init()
功能：打开设置界面后，获取系统时间，并在时间spinBox里显示出来
*/
void set_Dlg::time_init()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统当前的时间

    //获取年/月/日/时/分的数值并写入spinBox
    QString str_year = time.toString("yyyy");
    QString str_month = time.toString("MM");
    QString str_day = time.toString("dd");
    QString str_hour = time.toString("hh");
    QString str_min = time.toString("mm");

    bool ok = false;
    ui->year_spinBox->setValue(str_year.toInt(&ok));
    ui->month_spinBox->setValue(str_month.toInt(&ok));
    ui->day_spinBox->setValue(str_day.toInt(&ok));
    ui->hour_spinBox->setValue(str_hour.toInt(&ok));
    ui->min_spinBox->setValue(str_min.toInt(&ok));
}

/*
功能：点击取消按钮之后，重新获取系统时间并显示
*/
void set_Dlg::on_cancel_Btn_clicked()
{
    time_init();
}

/*
功能：点击保存时间按钮，获取所设置的时间，并设置系统时间，然后写入硬件
*/
void set_Dlg::on_saveBtn_time_clicked()
{
    QString str_time;//获取时间数据字符串 例如 “082716142012”月日时分年
    if(ui->month_spinBox->value() < 10)
        str_time = "0" + QString::number(ui->month_spinBox->value());
    else
         str_time =  QString::number(ui->month_spinBox->value());

    if(ui->day_spinBox->value() > 9)
        str_time = str_time + QString::number(ui->day_spinBox->value());
    else
        str_time = str_time + "0" + QString::number(ui->day_spinBox->value());

    if(ui->hour_spinBox->value()  > 9)
        str_time = str_time + QString::number(ui->hour_spinBox->value());
    else
        str_time = str_time  + "0" + QString::number(ui->hour_spinBox->value());

    if(ui->min_spinBox->value() > 9)
        str_time = str_time  + QString::number(ui->min_spinBox->value());
    else
        str_time = str_time  + "0" + QString::number(ui->min_spinBox->value());

    str_time ="date " + str_time + QString::number(ui->year_spinBox->value());

    system(str_time.toLatin1().data());//设置系统时间

    system("hwclock -w");//写入硬件
}



/*
功能：点击保存语言设置按钮，获取语言标志
*/
void  set_Dlg::on_saveBtn_language_clicked()
{
    QString language_Name = ui->comboBox->currentText();
    if(language_Name == "中文")
    {
      flag_lang = 0;
    }
    else  if(language_Name == "English")
    {
      flag_lang = 1;
    }
}
/*
功能：点击保存语言设置按钮，获取语言标志
返回值：  0  中文
        1  英文
*/
int set_Dlg::flag_language()
{
    return flag_lang;
}

/*
功能：切换语言
*/
void set_Dlg::changeEvent(QEvent *e)
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

