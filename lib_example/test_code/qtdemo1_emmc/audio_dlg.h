#ifndef AUDIO_DLG_H
#define AUDIO_DLG_H

#include <QDialog>
#include <QProcess>
namespace Ui {
class audio_Dlg;
}

class audio_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit audio_Dlg(QWidget *parent = 0);
    ~audio_Dlg();
     void closeEvent(QCloseEvent *event);
      void changeEvent(QEvent *e);


private slots:
    void on_playBtn_clicked();

    void on_stopBtn_clicked();

    void on_volume_valueChanged();

    void showFinished(int,QProcess::ExitStatus);

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::audio_Dlg *ui;
    QProcess  audioPcs;
    int flag;
    int langu_flag;
};

#endif // AUDIO_DLG_H
