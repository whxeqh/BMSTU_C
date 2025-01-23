CC := gcc
CFLAGS := -std=c99 -Wall -Werror

app.exe: main.o list.o node.o errors.o
	$(CC) -o $@ $^

main.o: main.c list.h errors.h
	$(CC) $(CFLAGS) -g -c $< 

list.o: list.c list.h
	$(CC) $(CFLAGS) -g -c $< 

node.o: node.c node.h
	$(CC) $(CFLAGS) -g -c $< 

errors.o: errors.c errors.h
	$(CC) $(CFLAGS) -g -c $< 

.PHONY: clean
clean:
	$(RM) *.o *.exe