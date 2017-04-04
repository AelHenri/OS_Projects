CC = clang
CFLAGS  = -Wall -std=c99

OBJ= sys_topic.o\
	main.o\
	structs.o\
	unit_tests.o

SRC= sys_topic.h\
	sys_topic.c\
	structs.h\
	structs.c\
	main.c\
	test_structs.c

BIN= test

all: $(BIN)

test: sys_topic.o main.o
	$(CC) $(CFLAGS) sys_topic.o main.o -o $@ 

structs: test_structs.o structs.o
	$(CC) $(CFLAGS) test_structs.o structs.o -o $@ 

units: unit_tests.o sys_topic.o
	$(CC) $(CFLAGS) sys_topic.o unit_tests.o -o $@ 

main.o: main.c sys_topic.h sys_topic.o
sys_topic.o: sys_topic.c

structs.o: structs.c
test_structs.o: test_structs.c structs.h structs.o

unit_tests.o: unit_tests.c sys_topic.h

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 