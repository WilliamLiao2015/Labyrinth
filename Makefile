include ../Make.defines


PROGS =	server client

STAGES = $(wildcard ./stages/*.c)


all: ${PROGS} ${STAGES}


server: server.o
	${CC} ${CFLAGS} -o $@ server.o ${STAGES} ${LIBS}

client: client.o
	${CC} ${CFLAGS} -o $@ client.o ${LIBS}
