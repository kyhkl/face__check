#ifndef DELETESTU_H
#define DELETESTU_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include "ui_deletestu.h"
#include "student.h"


class Deletestu: public QDialog,public Ui_deleteDlg
{
	Q_OBJECT
public:
	Deletestu(QWidget *parent = 0);

	Student *del;

public slots:
	
	void deldt();

};

#endif 

