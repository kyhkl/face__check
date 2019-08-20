#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QButtonGroup>
//#include <Qt>
#include <QMouseEvent>

class IPMethod;


namespace Ui {
    class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputWidget(IPMethod * ipm,QWidget *parent=0);
    ~InputWidget();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    void SetKeyBoard();

public slots:
    void ButtonJudge(int);


signals:
    void SendInputMessage(QString);
    void SendEnter();
    void SendBackspace();
    void SenEscape();



private slots:


private:
    Ui::InputWidget *ui;
    QButtonGroup *button_group;
    QPoint  mouse_pos;
    QPoint  widget_pos;
    bool should_move;
};

#endif // INPUTWIDGET_H
