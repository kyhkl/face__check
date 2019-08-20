/*
功能：调用madplay 播放音频
*/
#include "audio_dlg.h"
#include "ui_audio_dlg.h"
#include "config_all.h"

audio_Dlg::audio_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::audio_Dlg)
{
    ui->setupUi(this);
  //  this->setWindowTitle(tr("音频测试"));//设置标题栏
    this->setWindowFlags(Qt::WindowCloseButtonHint );//标题栏只有关闭按钮
    ui->volume->setMaximum(127);//设置音量滑快的最大最小值
    ui->volume->setMinimum(50);
    ui->stopBtn->setEnabled(false);//暂停按钮不可用
    flag=0;
    langu_flag=0;

    connect(&audioPcs,SIGNAL(finished(int,QProcess::ExitStatus)),this,
                  SLOT(showFinished(int,QProcess::ExitStatus)));
}

audio_Dlg::~audio_Dlg()
{
    delete ui;
}

void audio_Dlg::on_playBtn_clicked()
{
    flag=1;
    ui->stopBtn->setEnabled(true);//暂停按钮可用
    ui->stopBtn->setStyleSheet(STOP_NOR);
    ui->playBtn->setEnabled(false);
    ui->playBtn->setStyleSheet(PLAY_DIS);
//  QString program = "aplay";
    QString program = "madplay";
    QStringList arguments;
    arguments << AUDIO;
    audioPcs.start(program, arguments);
    ui->label_audio->setText(tr("正在播放音乐"));

}

void audio_Dlg::on_stopBtn_clicked()
{
    flag=0;
    ui->playBtn->setEnabled(true);
    ui->playBtn->setStyleSheet(PLAY_NOR);
    ui->stopBtn->setStyleSheet(STOP_DIS);
    audioPcs.close();
    ui->label_audio->setText(tr("音乐已停止"));
}

//音乐播放结束
void audio_Dlg::showFinished(int exitCode,QProcess::ExitStatus exitStatus)
{
    ui->playBtn->setEnabled(true);
    ui->playBtn->setStyleSheet(PLAY_NOR);
    ui->stopBtn->setStyleSheet(STOP_DIS);
    ui->label_audio->setText(tr("音乐已停止"));
}



void audio_Dlg::on_volume_valueChanged()
{
    if(flag==1)
    {
        QString str_volume = "amixer cset numid=28 ";
        str_volume = str_volume + QString::number(ui->volume->value());
        system(str_volume.toLatin1().data());
    }
}

 void audio_Dlg::closeEvent(QCloseEvent *event)
 {
     ui->playBtn->setEnabled(true);
     ui->playBtn->setStyleSheet(PLAY_NOR);
     ui->stopBtn->setStyleSheet(STOP_DIS);
     audioPcs.close();
     ui->label_audio->setText(tr("欢迎使用音乐播放器"));
 }

 void audio_Dlg::changeEvent(QEvent *e)
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

void audio_Dlg::on_label_2_linkActivated(const QString &link)
{

}
