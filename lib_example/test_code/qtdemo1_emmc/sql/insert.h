#ifndef INSERT_H
#define INSERT_H

#include <QPushButton>
#include <QDialog>
#include <QWidget>
#include "ui_insert.h"
#include "student.h"


class Insert: public QDialog,public Ui_insertDlg
{
	Q_OBJECT
public:
	Insert(QWidget *parent = 0);
	~Insert();

	Student *inp;
public:

public slots:
	void insertdata();


private:
	
};


#endif 
