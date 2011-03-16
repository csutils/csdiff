CXXFLAGS = -Wall -Wextra -O2
OBJS = csdiff.o csdiff.yy.o
csdiff: $(OBJS)
	g++ -o $@ $(OBJS) -lboost_regex

csdiff.yy.cc: csdiff.lex
	flex -o $@ $<

clean:
	rm -f csdiff csdiff.o csdiff.yy.o csdiff.yy.cc
