all: CFPS

CFPS: main.o CodonNumRep.o ExtractCF.o CFPS.o
	g++ main.o CodonNumRep.o ExtractCF.o CFPS.o -o CFPS

main.o: main.cpp
	g++ -c main.cpp

CodonNumRep.o: CodonNumRep.cpp CodonNumRep.h
	g++ -c CodonNumRep.cpp

ExtractCF.o: ExtractCF.cpp ExtractCF.h
	g++ -c ExtractCF.cpp

CFPS.o: CFPS.cpp CFPS.h
	g++ -c CFPS.cpp

clean:
	rm -f *.o *.pyc *~ CFPS
