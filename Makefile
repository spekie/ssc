SRC = codegen.cpp lexer.cpp main.cpp parser.cpp
OBJ = ${SRC:.cpp=.o}
CC = g++
DESTDIR = /usr/local

all: ssc

.c.o:
	${CC} -c ${CFLAGS} $<

ssc: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ssc ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ssc ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/ssc

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/ssc

.PHONY: all clean install uninstall
