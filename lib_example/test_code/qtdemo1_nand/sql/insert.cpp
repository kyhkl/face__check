#include <QLineEdit>
#include <QDebug>
#include "insert.h"
#include "student.h"
#include <QString>
#include <string.h>


Insert::Insert(QWidget *parent):QDialog(parent)
{
   setupUi(this);
   connect(pushButton,SIGNAL(clicked()),this,SLOT(insertdata()));
   connect(pushButton_2,SIGNAL(clicked()),this,SLOT(close()));

   inp=(Student *)parent;
   
}


Insert::~Insert()
{
   qDebug("destroy insetDialg!");
}


void Insert::insertdata()
{
	QString s1=lineEdit->text();
	QString s2=lineEdit_2->text();
	QString s3=lineEdit_3->text();
	
	char sqlbuf[300]={0};
	int ids;
	char name[20]={0};
	int score;
	bool ok;
    ids=s1.toInt(&ok,10);
	score=s3.toInt(&ok,10);
	
	memcpy(name,lineEdit_2->text().toLocal8Bit().data(),strlen(lineEdit_2->text().toLocal8Bit().data()));
	
	sprintf(sqlbuf,"INSERT INTO \"QtStudentData\" VALUES(%d ,'%s' ,%d );",ids,name,score);

	sqlite3_exec(inp->db , sqlbuf , 0 , 0 , &(inp->zErrMsg));


	qDebug(" You have insert new data^-^ \n");
	lineEdit->setText("");
	lineEdit_2->setText("");
	lineEdit_3->setText("");
	
		
}

