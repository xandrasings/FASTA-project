fasta: fasta.o Match.o
	g++ -g -Wall -std=c++11 -o fasta fasta.o Match.o

fasta.o: fasta.C Match.h Match.C
	g++ -g -Wall -std=c++11 -c fasta.C

Match.o: Match.h Match.C
	g++ -g -Wall -std=c++11 -c Match.C

