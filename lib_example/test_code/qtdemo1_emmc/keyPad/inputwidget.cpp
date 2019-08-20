#include "inputwidget.h"
#include "ipmethod.h"
#include "ui_inputwidget.h"
#include <QDebug>

static bool isCaps = false;

InputWidget::InputWidget(IPMethod * ipm,QWidget *parent) :
    QWidget(parent, Qt::Tool| Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);

    this->button_group=new QButtonGroup;
    this->SetKeyBoard();
    QObject::connect(this->button_group,SIGNAL(buttonClicked (int)),this,SLOT(ButtonJudge(int)));
    QObject::connect(this,SIGNAL(SendInputMessage(QString)),ipm,SLOT(PreeditContent(QString)));
    QObject::connect(this,SIGNAL(SendEnter()),ipm,SLOT(ConfirmContent()));
    QObject::connect(this,SIGNAL(SendBackspace()),ipm,SLOT(BackspaceContent()));
    QObject::connect(this,SIGNAL(SenEscape()),ipm,SLOT(Escape()));

    this->should_move=false;
    this->setMouseTracking(true);
}
InputWidget::~InputWidget()
{
    delete this->button_group;
    delete ui;
}

void InputWidget::mousePressEvent (QMouseEvent *event)
{

    if (event->button()!=Qt::LeftButton) return;
    this->should_move = true;
    this->widget_pos = this->pos();
    this->mouse_pos = event->globalPos();

}
void InputWidget::mouseReleaseEvent(QMouseEvent *event)
{
        if (event->button()!=Qt::LeftButton) return;
        this->should_move = false;

}
void InputWidget::mouseMoveEvent ( QMouseEvent * event )
{


    if (this->should_move)
    {
        QPoint pos = event->globalPos();
        int x = pos.x()-this->mouse_pos.x();
        int y = pos.y()-this->mouse_pos.y();
        QWidget::move(this->widget_pos.x()+x,this->widget_pos.y()+y);
    }

}


void InputWidget::SetKeyBoard()
{
    this->button_group->addButton(ui->key_0,Qt::Key_0);
    this->button_group->addButton(ui->key_1,Qt::Key_1);
    this->button_group->addButton(ui->key_2,Qt::Key_2);
    this->button_group->addButton(ui->key_3,Qt::Key_3);
    this->button_group->addButton(ui->key_4,Qt::Key_4);
    this->button_group->addButton(ui->key_5,Qt::Key_5);
    this->button_group->addButton(ui->key_6,Qt::Key_6);
    this->button_group->addButton(ui->key_7,Qt::Key_7);
    this->button_group->addButton(ui->key_8,Qt::Key_8);
    this->button_group->addButton(ui->key_9,Qt::Key_9);

    this->button_group->addButton(ui->key_A,Qt::Key_A);
    this->button_group->addButton(ui->key_B,Qt::Key_B);
    this->button_group->addButton(ui->key_C,Qt::Key_C);
    this->button_group->addButton(ui->key_D,Qt::Key_D);
    this->button_group->addButton(ui->key_E,Qt::Key_E);
    this->button_group->addButton(ui->key_F,Qt::Key_F);
    this->button_group->addButton(ui->key_G,Qt::Key_G);
    this->button_group->addButton(ui->key_H,Qt::Key_H);
    this->button_group->addButton(ui->key_I,Qt::Key_I);
    this->button_group->addButton(ui->key_J,Qt::Key_J);
    this->button_group->addButton(ui->key_K,Qt::Key_K);
    this->button_group->addButton(ui->key_L,Qt::Key_L);
    this->button_group->addButton(ui->key_M,Qt::Key_M);
    this->button_group->addButton(ui->key_N,Qt::Key_N);
    this->button_group->addButton(ui->key_O,Qt::Key_O);
    this->button_group->addButton(ui->key_P,Qt::Key_P);
    this->button_group->addButton(ui->key_Q,Qt::Key_Q);
    this->button_group->addButton(ui->key_R,Qt::Key_R);
    this->button_group->addButton(ui->key_S,Qt::Key_S);
    this->button_group->addButton(ui->key_T,Qt::Key_T);
    this->button_group->addButton(ui->key_U,Qt::Key_U);
    this->button_group->addButton(ui->key_V,Qt::Key_V);
    this->button_group->addButton(ui->key_W,Qt::Key_W);
    this->button_group->addButton(ui->key_X,Qt::Key_X);
    this->button_group->addButton(ui->key_Y,Qt::Key_Y);
    this->button_group->addButton(ui->key_Z,Qt::Key_Z);

   // this->button_group->addButton(ui->pushButton_78 ,Qt::Key_Escape);
  //this->button_group->addButton(ui->pushButton_75,Qt::PushButton_75);
  //this->button_group->addButton(ui->pushButton_76,Qt::PushButton_76);

  //  this->button_group->addButton(ui->pushButton_45,Qt::Key_Space);
  //  this->button_group->addButton(ui->pushButton_68,Qt::Key_Enter);
    this->button_group->addButton(ui->key_Backspace,Qt::Key_Backspace);
  //  this->button_group->addButton(ui->key_Escape,Qt::Key_Escape);

/////////////////////////////////////////////////////////////////////////////////////
    // Edit By ELF 2013.06.27.AM

    this->button_group->addButton(ui->key_equal, Qt::Key_Equal);
    this->button_group->addButton(ui->key_caps, Qt::Key_CapsLock);
    this->button_group->addButton(ui->key_enter, Qt::Key_Enter);
    this->button_group->addButton(ui->key_comma, Qt::Key_Comma);
    this->button_group->addButton(ui->key_dot, Qt::Key_Period);

    this->button_group->addButton(ui->key_dash, Qt::Key_Minus);
    this->button_group->addButton(ui->key_quotation, Qt::Key_QuoteLeft);
    this->button_group->addButton(ui->key_semicolon, Qt::Key_Semicolon);
    this->button_group->addButton(ui->key_backslash, Qt::Key_Backslash);
    this->button_group->addButton(ui->key_slash, Qt::Key_Slash);

    this->button_group->addButton(ui->key_lbracket, Qt::Key_BracketLeft);
    this->button_group->addButton(ui->key_rbracket, Qt::Key_BracketRight);
/////////////////////////////////////////////////////////////////////////////////////
}

void InputWidget::ButtonJudge(int id )
{
    if (isCaps)
    {
        switch (id)
        {
        case Qt::Key_0 :
            emit this->SendInputMessage(")");
            break;
        case Qt::Key_1 :
            emit this->SendInputMessage("!");
            break;
        case Qt::Key_2 :
            emit this->SendInputMessage("@");
            break;
        case Qt::Key_3 :
            emit this->SendInputMessage("#");
            break;
        case Qt::Key_4 :
            emit this->SendInputMessage("$");
            break;
        case Qt::Key_5 :
            emit this->SendInputMessage("%");
            break;
        case Qt::Key_6 :
            emit this->SendInputMessage("^");
            break;
        case Qt::Key_7 :
            emit this->SendInputMessage("&");
            break;
        case Qt::Key_8 :
            emit this->SendInputMessage("*");
            break;
        case Qt::Key_9 :
            emit this->SendInputMessage("(");
            break;


        case Qt::Key_A :
            emit this->SendInputMessage("A");
            break;
        case Qt::Key_B :
            emit this->SendInputMessage("B");
            break;
        case Qt::Key_C :
            emit this->SendInputMessage("C");
            break;
        case Qt::Key_D :
            emit this->SendInputMessage("D");
            break;
        case Qt::Key_E :
            emit this->SendInputMessage("E");
            break;
        case Qt::Key_F :
            emit this->SendInputMessage("F");
            break;
        case Qt::Key_G :
            emit this->SendInputMessage("G");
            break;
        case Qt::Key_H :
            emit this->SendInputMessage("H");
            break;
        case Qt::Key_I :
            emit this->SendInputMessage("I");
            break;
        case Qt::Key_J :
            emit this->SendInputMessage("J");
            break;
        case Qt::Key_K :
            emit this->SendInputMessage("K");
            break;
        case Qt::Key_L :
            emit this->SendInputMessage("L");
            break;
        case Qt::Key_M :
            emit this->SendInputMessage("M");
            break;
        case Qt::Key_N :
            emit this->SendInputMessage("N");
            break;
        case Qt::Key_O :
            emit this->SendInputMessage("O");
            break;
        case Qt::Key_P :
            emit this->SendInputMessage("P");
            break;
        case Qt::Key_Q :
            emit this->SendInputMessage("Q");
            break;
        case Qt::Key_R :
            emit this->SendInputMessage("R");
            break;
        case Qt::Key_S :
            emit this->SendInputMessage("S");
            break;
        case Qt::Key_T :
            emit this->SendInputMessage("T");
            break;
        case Qt::Key_U :
            emit this->SendInputMessage("U");
            break;
        case Qt::Key_V :
            emit this->SendInputMessage("V");
            break;
        case Qt::Key_W :
            emit this->SendInputMessage("W");
            break;
        case Qt::Key_X :
            emit this->SendInputMessage("X");
            break;
        case Qt::Key_Y :
            emit this->SendInputMessage("Y");
            break;
        case Qt::Key_Z :
            emit this->SendInputMessage("Z");
            break;

    //    case Qt::PushButton_38 :
     //       emit this->SendInputMessage(";");
      //      break;
    /*
       case Qt::PushButton_75 :
            emit this->SendInputMessage("?");
            break;
       case Qt::PushButton_76 :
            emit this->SendInputMessage("@");
            break;
    */
      case Qt::Key_Escape :
           emit this->SendInputMessage("?");
           break;

       case Qt::Key_Space :
            emit this->SendInputMessage("@");
            break;


        case Qt::Key_Backspace :
            emit this->SendBackspace();
            break;

/////////////////////////////////////////////////////////////////////////////////////
            // Edit By ELF @2013.06.27.AM
        case Qt::Key_Equal:
            emit this->SendInputMessage("+");
            break;
        case Qt::Key_CapsLock:
            isCaps = !isCaps;
            break;
        case Qt::Key_Enter:
            emit this->SendInputMessage("\n");
            break;
        case Qt::Key_Comma:
            emit this->SendInputMessage("<");
            break;
        case Qt::Key_Period:
            emit this->SendInputMessage(">");
            break;

        case Qt::Key_Minus:
            emit this->SendInputMessage("_");
            break;
        case Qt::Key_QuoteLeft:
            emit this->SendInputMessage("\"");
            break;
        case Qt::Key_Semicolon:
            emit this->SendInputMessage(":");
            break;
        case Qt::Key_Backslash:
            emit this->SendInputMessage("|");
            break;
        case Qt::Key_Slash:
            emit this->SendInputMessage("?");
            break;

        case Qt::Key_BracketLeft:
            emit this->SendInputMessage("{");
            break;
        case Qt::Key_BracketRight:
            emit this->SendInputMessage("}");
            break;
/////////////////////////////////////////////////////////////////////////////////////
        default:
            emit this->SendInputMessage("wrong");
            break;

        }
    }
    else
    {
        switch (id)
        {
        case Qt::Key_0 :
            emit this->SendInputMessage("0");
            break;
        case Qt::Key_1 :
            emit this->SendInputMessage("1");
            break;
        case Qt::Key_2 :
            emit this->SendInputMessage("2");
            break;
        case Qt::Key_3 :
            emit this->SendInputMessage("3");
            break;
        case Qt::Key_4 :
            emit this->SendInputMessage("4");
            break;
        case Qt::Key_5 :
            emit this->SendInputMessage("5");
            break;
        case Qt::Key_6 :
            emit this->SendInputMessage("6");
            break;
        case Qt::Key_7 :
            emit this->SendInputMessage("7");
            break;
        case Qt::Key_8 :
            emit this->SendInputMessage("8");
            break;
        case Qt::Key_9 :
            emit this->SendInputMessage("9");
            break;


        case Qt::Key_A :
            emit this->SendInputMessage("a");
            break;
        case Qt::Key_B :
            emit this->SendInputMessage("b");
            break;
        case Qt::Key_C :
            emit this->SendInputMessage("c");
            break;
        case Qt::Key_D :
            emit this->SendInputMessage("d");
            break;
        case Qt::Key_E :
            emit this->SendInputMessage("e");
            break;
        case Qt::Key_F :
            emit this->SendInputMessage("f");
            break;
        case Qt::Key_G :
            emit this->SendInputMessage("g");
            break;
        case Qt::Key_H :
            emit this->SendInputMessage("h");
            break;
        case Qt::Key_I :
            emit this->SendInputMessage("i");
            break;
        case Qt::Key_J :
            emit this->SendInputMessage("j");
            break;
        case Qt::Key_K :
            emit this->SendInputMessage("k");
            break;
        case Qt::Key_L :
            emit this->SendInputMessage("l");
            break;
        case Qt::Key_M :
            emit this->SendInputMessage("m");
            break;
        case Qt::Key_N :
            emit this->SendInputMessage("n");
            break;
        case Qt::Key_O :
            emit this->SendInputMessage("o");
            break;
        case Qt::Key_P :
            emit this->SendInputMessage("p");
            break;
        case Qt::Key_Q :
            emit this->SendInputMessage("q");
            break;
        case Qt::Key_R :
            emit this->SendInputMessage("r");
            break;
        case Qt::Key_S :
            emit this->SendInputMessage("s");
            break;
        case Qt::Key_T :
            emit this->SendInputMessage("t");
            break;
        case Qt::Key_U :
            emit this->SendInputMessage("u");
            break;
        case Qt::Key_V :
            emit this->SendInputMessage("v");
            break;
        case Qt::Key_W :
            emit this->SendInputMessage("w");
            break;
        case Qt::Key_X :
            emit this->SendInputMessage("x");
            break;
        case Qt::Key_Y :
            emit this->SendInputMessage("y");
            break;
        case Qt::Key_Z :
            emit this->SendInputMessage("z");
            break;

    //    case Qt::PushButton_38 :
     //       emit this->SendInputMessage(";");
      //      break;
    /*
       case Qt::PushButton_75 :
            emit this->SendInputMessage("?");
            break;
       case Qt::PushButton_76 :
            emit this->SendInputMessage("@");
            break;
    */
      case Qt::Key_Escape :
           emit this->SendInputMessage("?");
           break;

       case Qt::Key_Space :
            emit this->SendInputMessage("@");
            break;


        case Qt::Key_Backspace :
            emit this->SendBackspace();
            break;

/////////////////////////////////////////////////////////////////////////////////////
            // Edit By ELF @2013.06.27.AM
        case Qt::Key_Equal:
            emit this->SendInputMessage("=");
            break;
        case Qt::Key_CapsLock:
            isCaps = !isCaps;
            break;
        case Qt::Key_Enter:
            emit this->SendInputMessage("\n");
            break;
        case Qt::Key_Comma:
            emit this->SendInputMessage(",");
            break;
        case Qt::Key_Period:
            emit this->SendInputMessage(".");
            break;

        case Qt::Key_Minus:
            emit this->SendInputMessage("-");
            break;
        case Qt::Key_QuoteLeft:
            emit this->SendInputMessage("'");
            break;
        case Qt::Key_Semicolon:
            emit this->SendInputMessage(";");
            break;
        case Qt::Key_Backslash:
            emit this->SendInputMessage("\\");
            break;
        case Qt::Key_Slash:
            emit this->SendInputMessage("/");
            break;

        case Qt::Key_BracketLeft:
            emit this->SendInputMessage("[");
            break;
        case Qt::Key_BracketRight:
            emit this->SendInputMessage("]");
            break;
/////////////////////////////////////////////////////////////////////////////////////
        default:
            emit this->SendInputMessage("wrong");
            break;

        }
    }
}
