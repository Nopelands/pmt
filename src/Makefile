SRCS = main.cpp shift_or.cpp knuth_morris_pratt.cpp boyer_moore.cpp

OBJS = $(SRCS:.cpp=.o))

build:
	g++ -o pcc.exe $(SRCS) -O3 -Wall -Wcast-qual

clean:
	@rm -f .depend *~ core
