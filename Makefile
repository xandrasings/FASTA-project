GCC_ARGS = -g -Wall -std=c++11
BINARY = ./fasta

.PHONY: test run clean

all: fasta

clean:
	rm *.o $(BINARY)

run: fasta
	$(BINARY) -q < test/testcase_1.txt

test: fasta
	$(BINARY) -q < test/testcase_1.txt | diff test/expected_output_1.txt -

fasta: fasta.o
	g++ $(GCC_ARGS) fasta.o Match.o -o $(BINARY)

fasta.o: fasta.cpp Match.o
	g++ $(GCC_ARGS) -c fasta.cpp

Match.o: Match.h Match.cpp
	g++ $(GCC_ARGS) -c Match.cpp
