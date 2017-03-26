CC = clang
CFLAGS  = -Wall -std=c99

OBJ= sys_coucou.o\
	test_main.o\
	structs.o

SRC= sys_coucou.h\
	sys_coucou.c\
	structs.h\
	structs.c\
	test_main.c\
	test_structs.c

BIN= test

all: $(BIN)

test: sys_coucou.o test_main.o
	$(CC) $(CFLAGS) sys_coucou.o test_main.o -o $@ 

structs: test_structs.o structs.o
	$(CC) $(CFLAGS) test_structs.o structs.o -o $@ 

test_main.o: test_main.c sys_coucou.h sys_coucou.o
sys_coucou.o: sys_coucou.c

structs.o: structs.c
test_structs.o: test_structs.c structs.h structs.o

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 