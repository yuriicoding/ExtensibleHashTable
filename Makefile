all: driver

driver: main.o ExtensibleHashTable.o Bucket.o
	g++ -Wall -std=c++17  -o  driver main.o  ExtensibleHashTable.o Bucket.o

main.o: main.cpp ExtensibleHashTable.cpp ExtensibleHashTable.h
	g++ -Wall -std=c++17  -o main.o -c main.cpp	

ExtensibleHashTable.o:  ExtensibleHashTable.cpp  ExtensibleHashTable.h Bucket.h
	g++ -Wall -std=c++17  -o  ExtensibleHashTable.o  -c  ExtensibleHashTable.cpp 

Bucket.o:  Bucket.cpp  Bucket.h 
	g++ -Wall -std=c++17 -o  Bucket.o  -c  Bucket.cpp
	
clean:
	rm -f  main.o Bucket.o ExtensibleHashTable.o driver
