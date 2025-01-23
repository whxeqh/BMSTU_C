CC := gcc
CFLAGS := -std=c99 -g -Wall -Werror

app.exe: arr_alloc.o arr_io.o arr_op.o main.o
	$(CC) -o $@ $^

main.o: main.c arr_alloc.h arr_io.h arr_op.h errors.h
	$(CC) $(CFLAGS) -c $<

arr_alloc.o: arr_alloc.c arr_alloc.h errors.h
	$(CC) $(CFLAGS) -c $<

arr_io.o: arr_io.c arr_io.h errors.h
	$(CC) $(CFLAGS) -c $<

arr_op.o: arr_op.c arr_op.h arr_alloc.h errors.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean: 
	$(RM) *.exe *.o