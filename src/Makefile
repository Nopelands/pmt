SRCS = aho_corasick.cpp boyer_moore.cpp knuth_morris_pratt.cpp main.cpp sellers.cpp shift_or.cpp ukkonen.cpp wu_manber.cpp

KERNEL = $(shell uname -s)
ifeq ($(KERNEL),Linux)
	EXE = ../bin/pmt
else
	EXE = ../bin/pmt.exe
endif

build:
	@mkdir -p ../bin
	g++ -o $(EXE) $(SRCS) -O3 -Wall -Wcast-qual -std=c++20

build-old:
	@mkdir -p ../bin
	g++ -o $(EXE) $(SRCS) -O3 -w

clean:
	@rm -f -r ../bin
