CC = clang
CFLAGS  = -Wall 

all: dirwalker imapwalker zmapwalker

%: %.c 
	$(CC) $(CFLAGS) -I./minix/fs -o $@ $< 


clean: 
	rm -rf dirwalker imapwalker zmapwalker
