#include "ipmethod.h"
#include <QMessageBox>
IPMethod::IPMethod()
{
    this->p_inputwidget =NULL;
}
IPMethod::~IPMethod()
{
    delete this->p_inputwidget;
}

void IPMethod::PreeditContent(QString newcontent)
{
    sendCommitString(newcontent);
    //content += newcontent;
    //sendPreeditString(content,0);
}
void IPMethod::ConfirmContent()
{
        //sendCommitString(content);
        //content.clear();
}
void IPMethod::BackspaceContent()
{
    QWSServer::sendKeyEvent(0x01000003,Qt::Key_Backspace,Qt::NoModifier,true,false);
    //this->content.chop(1);
    //sendPreeditString(content,0);
}
void IPMethod::Escape()
{
    if(NULL==this->p_inputwidget)
       return;
    else
        delete this->p_inputwidget;
    this->p_inputwidget=NULL;
}

void IPMethod::updateHandler(int type)
{
        switch(type)
        {
        case QWSInputMethod::FocusIn:
               if(NULL==this->p_inputwidget)
                   this->p_inputwidget=new InputWidget(this);

               this->p_inputwidget->show();
              // QMessageBox::information(0,"Focusin","Focusin");
               break;
        case QWSInputMethod::FocusOut:
                if(NULL==this->p_inputwidget)
                    break;
                else
                    delete this->p_inputwidget;
                this->p_inputwidget=NULL;
                //QMessageBox::information(0,"Focusout","Focusout");
                break;
        default:
                break;
        }
}
