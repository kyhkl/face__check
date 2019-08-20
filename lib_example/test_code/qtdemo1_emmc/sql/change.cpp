#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include "change.h"
#include "student.h"
#include <QString>
#include <string>


Change::Change(QWidget *parent):QDialog(parent)
{
   setupUi(this);
   connect(pushButton,SIGNAL(clicked()),this,SLOT(rewrite()));
   connect(pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
   ch=(Student *)parent;
   
}


Change::~Change()
{
   qDebug("destroy!");
}


void Change::rewrite()
{
	int ret;
	char buf[100];
	ret = QMessageBox::question(this, tr("Application"),
				tr("Do you sure want to change your data?"),
				QMessageBox::Ok | QMessageBox::Cancel,
                                QMessageBox::Ok);
		 
	if (ret == QMessageBox::Ok)
	{
		char ids[100]={0};
		char name[100]={0};
		char scores[100]={0};
		
		memcpy(ids,lineEdit->text().toLocal8Bit().data(),strlen(lineEdit->text().toLocal8Bit().data()));
		memcpy(name,lineEdit_2->text().toLocal8Bit().data(),strlen(lineEdit_2->text().toLocal8Bit().data()));
		memcpy(scores,lineEdit_3->text().toLocal8Bit().data(),strlen(lineEdit_3->text().toLocal8Bit().data()));
	

		sprintf(buf,"UPDATE \"QtStudentData\" SET name='%s',score='%s' WHERE ID = '%s' ;",name,scores,ids);
		sqlite3_exec(ch->db , buf , 0 , 0 , &(ch->zErrMsg));
	}
	 
}

