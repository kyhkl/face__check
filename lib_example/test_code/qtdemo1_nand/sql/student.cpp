#include <math.h>
#include <QPainter>
#include <stdio.h>
#include <QLineEdit>
#include <QDebug>
#include "student.h"
#include "insert.h"
#include "change.h"
#include "findstu.h"
#include "deletestu.h"
#include "querystu.h"
#include <QString>
#include <string>
#include <QTextCodec>



Student::Student(QWidget *parent):QDialog(parent)
{

   setupUi(this);
   this->setWindowTitle(tr("Sqlite3 Test"));
   connect(pushButton,SIGNAL(clicked()),this,SLOT(firstdata()));
   connect(pushButton_2,SIGNAL(clicked()),this,SLOT(updata()));
   connect(pushButton_3,SIGNAL(clicked()),this,SLOT(nextdat()));
   connect(pushButton_4,SIGNAL(clicked()),this,SLOT(lastdata()));
   connect(pushButton_5,SIGNAL(clicked()),this,SLOT(intoinsert()));
   connect(pushButton_6,SIGNAL(clicked()),this,SLOT(intochange()));
   connect(pushButton_7,SIGNAL(clicked()),this,SLOT(intodelete()));
   connect(pushButton_8,SIGNAL(clicked()),this,SLOT(intoquery()));
   connect(pushButton_9,SIGNAL(clicked()),this,SLOT(intofind()));

	int nrow , ncolumn ,rc;
	char sqlw[]="SELECT * FROM QtStudentData";
	
        //
	rc = sqlite3_open("Qtstudent.db", &db); 
	if( rc )	
	{
		qDebug("Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	char sql[200]=" CREATE TABLE QtStudentData(\
			  ID INTEGER PRIMARY KEY,\
					name VARCHAR(10),\
					 score INTEGER);";

	sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );
	
	sqlite3_get_table(db , sqlw , &azResult , &nrow , &ncolumn , &zErrMsg );
        if(nrow > 0)
        {
        x=3;
	lineEdit->setText(azResult[x]);
        lineEdit_2->setText(QString::fromLocal8Bit(azResult[x+1]));
	lineEdit_3->setText(azResult[x+2]);
        }
}


Student::~Student()
{
	sqlite3_free_table( azResult ); 

	sqlite3_close(db);

	qDebug("destroy!");
}


void Student::firstdata()
{
	int nrow , ncolumn ;
	char sqlw1[]="SELECT * FROM QtStudentData";
	char **azResult1;

        x=3;
	sqlite3_get_table(db , sqlw1 , &azResult1 , &nrow , &ncolumn , &zErrMsg );
        if(nrow > 0)
        {
        lineEdit->setText(azResult[x]);
        lineEdit_2->setText(QString::fromLocal8Bit(azResult[x+1]));
        lineEdit_3->setText(azResult[x+2]);
        }
}


void Student::updata()
{
	int nrow , ncolumn ,ret;
	char sqlw2[]="SELECT * FROM QtStudentData";
	char **azResult2;
	
	if(x==3)
	{
		ret = QMessageBox::warning(this, tr("My Application"),
					   tr("The data has been firest data!"),
					   QMessageBox::Ok ,QMessageBox::Ok);	
	}
	else
	{ 
		sqlite3_get_table(db , sqlw2 , &azResult2 , &nrow , &ncolumn , &zErrMsg );
		x-=ncolumn;   
		
		if(x<(nrow+1)*ncolumn && x>2)
		{
			lineEdit->setText(azResult2[x]);
			lineEdit_2->setText(QString::fromLocal8Bit(azResult2[x+1]));
			lineEdit_3->setText(azResult2[x+2]);
		}
		
	}
	
}


void Student::nextdat()
{
	int nrow , ncolumn ;
	char sqlw3[]="SELECT * FROM QtStudentData";
	char **azResult3;
	int ret;
	sqlite3_get_table(db , sqlw3 , &azResult3 , &nrow , &ncolumn , &zErrMsg );
	x+=ncolumn;

	if(x<(nrow+1)*ncolumn && x>2)
	{
		lineEdit->setText(azResult3[x]);
		lineEdit_2->setText(QString::fromLocal8Bit(azResult3[x+1]));
		lineEdit_3->setText(azResult3[x+2]);
	}
	else
	{
		x=nrow*ncolumn;
		ret = QMessageBox::warning(this, tr("My Application"),
						   tr("The data has been last data!"),
						   QMessageBox::Ok ,QMessageBox::Ok);	
	}
	
}


void Student::lastdata()
{
	int nrow , ncolumn ;
	char sqlw4[]="SELECT * FROM QtStudentData";
	char **azResult4;

	
	sqlite3_get_table(db , sqlw4 , &azResult4 , &nrow , &ncolumn , &zErrMsg );
        if(nrow > 0)
        {
        x=nrow*ncolumn;
	lineEdit->setText(azResult4[x]);
	lineEdit_2->setText(QString::fromLocal8Bit(azResult4[x+1]));
	lineEdit_3->setText(azResult4[x+2]);
        }
}


void Student::intoinsert()
{
	Insert *t= new Insert(this);
	t->show();
}


void Student::intochange()
{
	Change *c= new Change(this);
	c->show();
}

void Student::intodelete()
{
	Deletestu *d= new Deletestu(this);
	d->show();
}


void Student::intofind()
{
	Findstu *fd= new Findstu(this);
	fd->show();
}


void Student::intoquery()
{
	Querystu *qu = new Querystu(this);
	qu->show();   
}

