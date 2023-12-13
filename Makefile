include ../Make.defines

PROGS =	server client


all: ${PROGS}


server: server.o
	${CC} ${CFLAGS} -o $@ server.o ${LIBS} -lsqlite3 -std=c99

client: client.o
	${CC} ${CFLAGS} -o $@ client.o ${LIBS}


clean:
	rm -f ${PROGS} ${CLEANFILES}
