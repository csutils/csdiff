CXXFLAGS = -Wall -Wextra -O2
PARSER_OBJS = csparser.o csparser.yy.o
csdiff: csdiff.o $(PARSER_OBJS)
	g++ -o $@ csdiff.o $(PARSER_OBJS) -lboost_regex

csparser.yy.cc: csparser.lex
	flex -o $@ $<

# .hh deps (built manually for now)
$(PARSER_OBJS): csparser-priv.hh
csparser.o csdiff.o: csparser.hh

clean:
	rm -fv csdiff csdiff.o $(PARSER_OBJS) csparser.yy.cc
