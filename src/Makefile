SRCS = aho_corasick.cpp boyer_moore.cpp knuth_morris_pratt.cpp main.cpp sellers.cpp shift_or.cpp ukkonen.cpp wu_mamber.cpp

OBJS = $(SRCS:.cpp=.o))

KERNEL = $(shell uname -s)
ifeq ($(KERNEL),Linux)
	EXE = ../bin/pcc
else
	EXE = ../bin/pcc.exe
endif

build:
	mkdir -p ../bin
	g++ -o $(EXE) $(SRCS) -O3 -Wall -Wcast-qual

clean:
	@rm -f .depend *~ core
