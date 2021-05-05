first reads host, user, passwd, db (if you need to change more then change the source code)
from a supplied file specified in the #define FILE_NAME, with 
max length of these lines being in #define MAX_SIZE.
connects to mysql with this information,
then drops and creates a table named "items", inserts two items,
and displays them using a simple SELECT query.