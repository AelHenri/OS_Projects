
CC = clang
CFLAGS  = -Wall -std=c99 -I./minix/fs

OBJ= main.o\
	utilities.o\
	dirwalker.o\
	imapwalker.o\
	zmapwalker.o\
	check_imap.o\
	check_zmap.o\


SRC= utilities.h\
	dirwalker.h\
	utilities.c\
	imapwalker.c\
	zmapwalker.h\
	dirwalker.c\
	main.c\
	imapwalker.c\
	zmapwalker.h\
	check_imap.h\
	check_imap.c\
	check_zmap.h\
	check_zmap.c\

BIN= main

all: $(BIN)

main: main.o utilities.o dirwalker.o imapwalker.o zmapwalker.o check_imap.o check_zmap.o
	$(CC) $(CFLAGS) $^ -o $@ 

utilities.o: utilities.h utilities.c
dirwalker.o: utilities.h dirwalker.h dirwalker.c
imapwalker.o: utilities.h imapwalker.h imapwalker.c		
zmapwalker.o: utilities.h zmapwalker.h zmapwalker.c
main.o: main.c utilities.h dirwalker.h imapwalker.h zmapwalker.h
check_imap.o: utilities.h imapwalker.h check_imap.h check_imap.c
check_zmap.o: utilities.h zmapwalker.h check_zmap.h check_zmap.c

clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(OBJ) $(BIN) core.*

.PHONY: all clean cleanall 