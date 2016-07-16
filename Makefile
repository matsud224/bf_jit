CFLAGS := -Wall -O2

bf_jit: main.o emit.o
	g++ -o bf_jit main.o emit.o
main.o emit.o: emit.h

clean:
	$(RM) *.o
	$(RM) bf_jit

