.POSIX:
CC     = cc -std=c99
CFLAGS = -Wall -Wextra -Os -g3

lifegen: lifegen.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ lifegen.c $(LDLIBS)

clean:
	rm -f lifegen
