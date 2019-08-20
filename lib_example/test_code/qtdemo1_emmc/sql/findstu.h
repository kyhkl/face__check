#ifndef FINDESTU_H
#define FINDESTU_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include "ui_find.h"
#include "student.h"


class Findstu: public QDialog,public Ui_findDlg
{
	Q_OBJECT
public:
	Findstu(QWidget *parent = 0);


public:

	Student *fd;

public slots:
	void finddt();


};

#endif 

