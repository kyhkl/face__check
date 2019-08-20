#ifndef IPMETHOD_H
#define IPMETHOD_H

#include <QWSInputMethod>
#include "inputwidget.h"

class IPMethod : public QWSInputMethod
{
    Q_OBJECT

public:
    IPMethod();
    ~IPMethod();
    void updateHandler(int);
private:
        InputWidget* p_inputwidget;
        QString content;

private slots:
        void PreeditContent(QString);
        void ConfirmContent();
        void BackspaceContent();
        void Escape();
};

#endif // IPMETHOD_H
