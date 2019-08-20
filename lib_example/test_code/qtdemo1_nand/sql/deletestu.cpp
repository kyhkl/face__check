#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include "deletestu.h"
#include <QString>
#include <string>


Deletestu::Deletestu(QWidget *parent):QDialog(parent)
{
   setupUi(this);
   connect(pushButton,SIGNAL(clicked()),this,SLOT(deldt()));
   connect(pushButton_2,SIGNAL(clicked()),this,SLOT(close()));

   del=(Student *)parent;
   
}


void Deletestu::deldt()
{
	char sql[200]={0};
    QString s1=lineEdit->text();
	QByteArray ba = s1.toLatin1();
	int i,ret;
	int nrow , ncolumn ;
	char **azResult;
	char sqlw[]="SELECT * FROM QtStudentData";
	sqlite3_get_table(del->db , sqlw, &azResult , &nrow , &ncolumn , &(del->zErrMsg ));
	
	for(i=3 ; i<( nrow + 1 ) * (ncolumn) ; i++ ) 
	{
		if(!strcmp(azResult[i],ba.data()))
		{
			le2->setText(QString::fromLocal8Bit(azResult[i+1]));
         	le3->setText(azResult[i+2]);
			ret = QMessageBox::question(this, tr("Application"),
			tr("The document has been modified","Do you want to save your changes?"),
			QMessageBox::Ok | QMessageBox::Cancel,
                        QMessageBox::Ok);
     
			if (ret == QMessageBox::Ok)
			{
			    sprintf(sql,"DELETE FROM QtStudentData WHERE ID = '%s' ;",azResult[i]);
				sqlite3_exec(del->db , sql , 0 , 0 , &(del->zErrMsg));	
				qDebug("Already remove a information of student!\n");
			}
	 
		
		}
	}

}


