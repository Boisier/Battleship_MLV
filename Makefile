TARGET = main

DEPS = headers/structs.h headers/functions.h
OBJ = main.o include/helpers.o include/mainFunctions.o include/printElements.o include/coreFunctions.o include/monitoring.o

##########################################################"
CC=gcc

#Do not include ASan
CFLAGS = -g -O2 -Wall -std=c89 -pedantic -Werror -lMLV `pkg-config --cflags MLV`

#Include ASan
#CFLAGS = -g -O2 -Wall -std=c89 -pedantic -Werror -fsanitize=address -fno-omit-frame-pointer -ggdb `pkg-config --cflags MLV`

LDLIBS = `pkg-config --libs MLV`

all: $(TARGET) clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(TARGET): $(OBJ)
	gcc -o $@ $^ $(LDLIBS)

.PHONY: clean

clean: 
	$(RM) count *.o *~
	$(RM) count include/*.o *~
