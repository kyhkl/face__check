#include <QLineEdit>
#include <QDebug>
#include "querystu.h"
#include <QString>
#include "student.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QTableView>


Querystu::Querystu(QWidget *parent):QDialog(parent)
{
    setupUi(this);
   // connect(pushButton,SIGNAL(clicked()),this,SLOT(close()));

    qs=(Student *)parent;

	int nrow , ncolumn ;
	char *sqlw2="SELECT * FROM QtStudentData";
	char **azResult2;

	sqlite3_get_table(qs->db , sqlw2 , &azResult2, &nrow , &ncolumn , &(qs->zErrMsg) );
	
    QTableWidget *table = new QTableWidget(this);
	table->setColumnCount(ncolumn); 
    table->setRowCount(nrow); 

	table->setGeometry(QRect(20,20, 350,300));
	adjustSize ();
	
    QStringList headers; 


    headers << "ID"<<"NAME"<<"SCORE"; 
	
    table->setHorizontalHeaderLabels(headers); 

	int i,j;
	for (i = 1; i < nrow+1; i++)	 
	{
		for (j = 0; j <ncolumn;j++)
		{
			table->setItem(i-1,j, new QTableWidgetItem(QString::fromLocal8Bit(azResult2[i*ncolumn+j]))); 
		}
	}	

}


