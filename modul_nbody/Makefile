# Make animate to show a nice window
# Make starsim to only benchmark


starsim: logic.o main.o
	gcc -std=c99 logic.o main.o -o main -lm 
animate: logic.o main.o  
	gcc -std=c99 -DANIMATE logic.c main.c -o main -lm -lX11
main.o: main.c
	gcc -std=c99 -c main.c -lm
logic.o: logic.c
	gcc -std=c99 -c logic.c -lm
run:
	./main
clean:
	rm main *.o
