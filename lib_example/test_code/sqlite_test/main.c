/*
 * main.c
 *
 *  Created on: 2013-3-30
 *      Author: tom
 */
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

int main(int args, char *argv[])
{
	sqlite3 *db = 0;
//	char *err_msg = 0;
	int rc;

	//Open the database.If it doesn't exist, then create it.
	rc = sqlite3_open("test.db", &db);
	if(rc)
	{
		printf("Can't open database:%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	// Create a table
	char *sql = "CREATE TABLE SensorData( ID INTEGER PRIMARY KEY,SensorID INTEGER,SiteNum INTEGER,Time VARCHAR(12),SensorParameter REAL);";
	sqlite3_exec( db , sql , 0 , 0 , 0);

	// insert  data record
	sql = "INSERT INTO SensorData VALUES( NULL , 1 , 1 , '200605011206', 18.9 );" ;
	sqlite3_exec( db , sql , 0 , 0 , 0);

	sql = "INSERT INTO SensorData VALUES(NULL, 2, 1, '200605011207', 19.0);";
	sqlite3_exec( db , sql , 0 , 0 , 0);

	// inquiry data
	int row=0, col=0;
	char **result;
	sql = "SELECT * FROM SensorData ";
	sqlite3_get_table( db , sql , &result , &row , &col , 0 );
	printf( "row:%d column=%d \n" , row , col);
//	int i,j;
	for(int i=0;i!=(row+1);i++)
	{
		for(int j=0;j<col;j++)
			printf("%s	",result[i*col+j]);
		printf("\n");
	}
	sqlite3_free_table(result);

	sqlite3_close(db);

	return 0;
}

