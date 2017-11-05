graph.exe: dsa2proj3.o heap.o hash.o graph.o
	g++ -o graph.exe dsa2proj3.o heap.o hash.o graph.o

dsa2proj3.o: dsa2proj3.cpp
	g++ -c dsa2proj3.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

debug:
	g++ -g -o graphDebug.exe dsa2proj3.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups