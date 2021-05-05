CC = gcc
CFLAGS = -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -lssl -lcrypto -ldl
 
sqltest: sqltest.o
	$(CC) -o sql sqltest.o $(CFLAGS)

clean:
	rm sql sqltest.o 
