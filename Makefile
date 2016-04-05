#Makefile
ERR = $(shell which icpc >/dev/null; echo $$?)
ifeq "$(ERR)" "0"
    CC := icc
else	
    CC := g++
endif

EXEC := life

info:
	@echo "usage: make all\nmake clean"

all: life

life: main.o conway.o
	$(CC) main.o conway.o -lncurses -o life
	$(RM) main.o conway.o

main.o: main.cpp
	$(CC) -c ./main.cpp

conway.o: conway.cpp
	$(CC) -c ./conway.cpp

clean:
	$(RM) $(EXEC) main.o conway.o 
