#ifndef BUZZER_H
#define BUZZER_H

#include <QDialog>

namespace Ui {
    class buzzer;
}

class buzzer : public QDialog {
    Q_OBJECT
public:
    buzzer(QWidget *parent = 0);
    ~buzzer();

public:
    bool buzzerState;

protected:


private:
    Ui::buzzer *ui;


private slots:
    void on_buzzerCtrlBtn_clicked();
};

#endif // BUZZER_H
