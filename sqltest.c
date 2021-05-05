/**
 * first reads host, user, passwd, db (if you need to change more then change the source code)
 * from a supplied file specified in the #define FILE_NAME, with 
 * max length of these lines being in #define MAX_SIZE.
 * connects to mysql with this information,
 * then drops and creates a table named "items", inserts two items,
 * and displays them using a simple SELECT query.
 **/

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "./.env"
#define MAX_SIZE 10

void finish_with_error(MYSQL *con) {
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc, char **argv) {

	/** 
	 * first some file operations
	 * try to make a function later
	 **/
	FILE *fp;
	fp=fopen(FILE_NAME, "r");
	char info[4][MAX_SIZE];
	fscanf(fp, "%s %s %s %s", 
		info[0], info[1], info[2], info[3]);
	fclose(fp);

	/** 
	 * mysql stuff
	 **/
	MYSQL * con = mysql_init(NULL);

	if (con == NULL){
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, info[0], info[1], info[2], info[3], 0, NULL, 0) == NULL) {
		finish_with_error(con);
	} else {
		printf("CONNECTION SUCCESSFUL\n");
	}

	if(mysql_query(con, "drop table if exists items")) {
		finish_with_error(con);
	} else {
		printf("probably dropped table items\n");
	}

	if(mysql_query(con, "create table items(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(20), value INT)")) {
		finish_with_error(con);
	} else {
		printf("created table items\n");
	}

	if(mysql_query(con, "insert into items values (1, 'potion', '20')")) {
		finish_with_error(con);
	} else {
		printf("inserted potion into table items\n");
	}

	if(mysql_query(con, "insert into items values (2, 'rations', '10')")) {
		finish_with_error(con);
	} else {
		printf("inserted rations into table items\n");
	}

	if(mysql_query(con, "select * from items")) {
		finish_with_error(con);
	} else {
		printf("obtained query results...\n");
	}

	MYSQL_RES *result = mysql_store_result(con);

	if(result == NULL) {
		finish_with_error(con);
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result))) {
		for (int i = 0; i < num_fields; i++) {
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(con);

	return 0;
}
