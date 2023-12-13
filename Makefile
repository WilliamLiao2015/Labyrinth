include ../Make.defines


PROGS =	server client

STAGES = $(wildcard ./stages/*.c)
UTILS = $(wildcard ./utils/*.c)


all: ${PROGS} ${STAGES} ${UTILS}


server: server.o
	${CC} ${CFLAGS} -o $@ server.o ${LIBS}

client: client.o
	${CC} ${CFLAGS} -o $@ client.o ${STAGES} ${UTILS} ${LIBS}
