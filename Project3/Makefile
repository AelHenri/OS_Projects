CC = clang
CFLAGS  = -Wall 

all: dirwalker 

%: %.c 
	$(CC) $(CFLAGS) -I./minix/fs -o $@ $< 


clean: 
	rm -rf dirwalker
