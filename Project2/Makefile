CC = clang
CFLAGS  = -Wall -std=c99

OBJ= sys_coucou.o\
	test_main.o

SRC= sys_coucou.h\
	sys_coucou.c\
	test_main.c

BIN= test

all: $(BIN)

test: sys_coucou.o test_main.o
	$(CC) $(CFLAGS) $(OBJ) -o $@ 

test_main.o: test_main.c sys_coucou.h sys_coucou.o
sys_coucou.o: sys_coucou.c

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 