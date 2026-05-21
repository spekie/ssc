.POSIX:

CXX = g++
OBJ = main.o lexer.o parser.o codegen.o
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
PREFIX = /usr/local

all: ssc

ssc: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ)

main.o: main.cpp lexer.hpp parser.hpp codegen.hpp token.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

lexer.o: lexer.cpp lexer.hpp token.hpp
	$(CXX) $(CXXFLAGS) -c lexer.cpp

parser.o: parser.cpp parser.hpp token.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

codegen.o: codegen.cpp codegen.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -c codegen.cpp

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f ssc $(DESTDIR)$(PREFIX)/bin/ssc
	chmod 755 $(DESTDIR)$(PREFIX)/bin/ssc
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f ssc.1 $(DESTDIR)$(MANPREFIX)/man1/ssc.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/ssc.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/ssc
	rm -f $(DESTDIR)$(MANPREFIX)/man1/ssc.1

clean:
	rm -f ssc $(OBJ)

.PHONY: all install uninstall clean
