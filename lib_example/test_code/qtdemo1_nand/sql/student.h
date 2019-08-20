#ifndef STUDENTSQ_H
#define STUDENTSQ_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include "ui_student.h"
#include <sqlite3.h>
#include <QStringList>
#include <QMessageBox>
#include "keyPad/ipmethod.h"



class Student: public QDialog, public Ui_sqliteDlg
{
Q_OBJECT
public:
	Student(QWidget *parent = 0);
	~Student();

public:
	
	sqlite3 *db;
	int x;
	char *zErrMsg ;
	char **azResult;

        QWSInputMethod *p_ipmethod;
	
public slots:

	void firstdata();
	void updata();
	void nextdat();
	void lastdata();
	void intoinsert();	
	void intochange();
	void intodelete();	
	void intoquery();	
	void intofind();
 
 
};

#endif 
