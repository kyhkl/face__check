#include <QLineEdit>
#include <QDebug>
#include "findstu.h"
#include <QString>
#include <string>


Findstu::Findstu(QWidget *parent):QDialog(parent)
{
   setupUi(this);
   connect(pushButton,SIGNAL(clicked()),this,SLOT(finddt()));
   connect(pushButton_2,SIGNAL(clicked()),this,SLOT(close()));

   fd=(Student *)parent;
}


void Findstu::finddt()
{
    QString s2=lineEdit->text();
	QByteArray ba = s2.toLatin1();
	int nrow , ncolumn ;
	char sqlw1[]="SELECT * FROM QtStudentData";
	char **azResult1;
	sqlite3_get_table(fd->db , sqlw1 , &azResult1 , &nrow , &ncolumn , &(fd->zErrMsg) );
	
	int i;	
	for( i=3 ; i<(nrow+1)*(ncolumn); i++ )	
	{
	    if(!strcmp(azResult1[i],ba.data()))
	    {
		    lineEdit_2->setText(QString::fromLocal8Bit(azResult1[i+1]));
			lineEdit_3->setText(azResult1[i+2]);
	    }
	  
	}
			 
}

