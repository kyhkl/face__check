#include <QtGui/QApplication>
#include "serial_dlg.h"
#include <QTextCodec>
#include <QWSServer>
#include "mainwindow.h"
#include "keyPad/inputwidget.h"
#include "keyPad/ipmethod.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));       //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));//支持中文文件名显示

    // QWSServer::setCursorVisible(false);//去掉鼠标

    MainWindow  main_desk;
    main_desk.showFullScreen();//全屏显示

    return a.exec();
}
