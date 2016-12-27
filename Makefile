TARGET = main

DEPS = headers/structs.h headers/functions.h
OBJ = main.o include/helpers.o include/mainFunctions.o include/printFunctions.o include/coreFunctions.c include/monitoring.o

##########################################################"
CC=gcc

CFLAGS = -g -O2 -Wall -fsanitize=address -fno-omit-frame-pointer -ggdb -std=c89 -pedantic -Werror -lMLV `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

all: $(TARGET) clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean: 
	$(RM) count *.o *~
	$(RM) count include/*.o *~