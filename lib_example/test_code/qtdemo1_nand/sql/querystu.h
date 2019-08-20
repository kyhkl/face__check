#ifndef QUERYSTU_H
#define QUERYSTU_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include "ui_querystu.h"
#include "student.h"


class Querystu: public QDialog,public Ui_queryDlg
{
	Q_OBJECT
public:
	Querystu(QWidget *parent = 0);

    Student *qs;

public slots:
	
     
};


#endif 
