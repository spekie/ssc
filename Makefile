.POSIX:

SRC = codegen.cpp lexer.cpp main.cpp parser.cpp
OBJ = ${SRC:.cpp=.o}
CXXFLAGS = -Wall -Wextra -pedantic
DESTDIR = /usr/local

all: ssc

.c.o:
	${CXX} -c ${CXXFLAGS} $<

ssc: ${OBJ}
	${CXX} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ssc ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ssc ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/ssc

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/ssc

.PHONY: all clean install uninstall
