GCC_ARGS = -g -Wall -std=c++11
BINARY = ./fasta

.PHONY: test run clean

all: fasta

clean:
	rm *.o $(BINARY)

run: fasta
	$(BINARY) -f test/testcase_1.txt

run-args: fasta
	$(BINARY) -s1 BILLGATES -s2 BILLTOGATES -n 2

wonk: fasta
	$(BINARY) -f test/testcase_1.txt -w 0.5

test: fasta
	$(BINARY) -f test/testcase_1.txt | diff test/expected_output_1.txt -

fasta: fasta.o
	g++ $(GCC_ARGS) fasta.o Match.o -o $(BINARY)

fasta.o: fasta.cpp Match.o arguments.cpp
	g++ $(GCC_ARGS) -c fasta.cpp

Match.o: Match.h Match.cpp
	g++ $(GCC_ARGS) -c Match.cpp
