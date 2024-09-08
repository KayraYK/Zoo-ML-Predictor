kazanciKayraA1: kazanciKayraA1.o kazanciKayraA1Main.o 
	gcc kazanciKayraA1.o kazanciKayraA1Main.o -o kazanciKayraA1
kazanciKayraA1.o: kazanciKayraA1.c givenA1.h
	gcc -Wall -std=c99 -c kazanciKayraA1.c
kazanciKayraA1Main.o: kazanciKayraA1Main.c givenA1.h
	gcc -Wall -std=c99 -c kazanciKayraA1Main.c
clean:
	rm *.o kazanciKayraA1
