# Make animate to show a nice window
# Make starsim to only benchmark
C_OPTIONS = gcc -std=c99

FILES = *.c

starsim: logic.o main.o
	$(C_OPTIONS) logic.o main.o -o main -lm 
animate: logic.o main.o  
	$(C_OPTIONS) -DANIMATE logic.c main.c -o main -lm -lX11
all: $(FILES)
	$(C_OPTIONS) -c $(FILES) 

main.o: main.c
	$(C_OPTIONS) -c main.c -lm
logic.o: logic.c
	$(C_OPTIONS) -c logic.c -lm
run:
	./main

test: logic.o
	$(C_OPTIONS) logic.c test.c -o unittest -lm -lcunit

clean:
	rm main unittests *.o
