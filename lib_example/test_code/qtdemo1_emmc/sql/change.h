#ifndef HELLO55_H
#define HELLO55_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include "ui_change.h"
#include "student.h"


class Change: public QDialog,public  Ui_chaneDlg
{
	Q_OBJECT
public:
	Change(QWidget *parent = 0);
	~Change();

public:
	Student *ch;

public slots:
	void rewrite();


private:
	
};


#endif 
