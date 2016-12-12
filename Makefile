TARGET = main

DEPS = headers/structs.h headers/functions.h
OBJ = main.o include/helpers.o include/mainFunctions.o 

##########################################################"
CC=gcc

CFLAGS = -g -O2 -Wall -Werror -lMLV `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: 
	$(RM) count *.o *~
	$(RM) count include/*.o *~