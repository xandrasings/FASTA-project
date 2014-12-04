GCC_ARGS = -g -Wall -std=c++11

.PHONY: test run clean

all: fasta

test: fasta
	./fasta < test/test_input.txt | diff test/test_output.txt

fasta: fasta.o
	g++ $(GCC_ARGS) fasta.o Match.o -o fasta

fasta.o: fasta.C Match.o
	g++ $(GCC_ARGS) -c fasta.C

Match.o: Match.h Match.C
	g++ $(GCC_ARGS) -c Match.C
