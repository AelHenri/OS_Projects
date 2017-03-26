CC = clang
CFLAGS  = -Wall -std=c99

OBJ= sys_coucou.o\
	test_main.o\
	structs.o

SRC= sys_coucou.h\
	sys_coucou.c\
	structs.h\
	structs.c\
	test_main.c

BIN= test

all: $(BIN)

test: sys_coucou.o test_main.o structs.o
	$(CC) $(CFLAGS) $(OBJ) -o $@ 

test_main.o: test_main.c sys_coucou.h sys_coucou.o structs.h structs.o
sys_coucou.o: sys_coucou.c
structs.o: structs.c

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 