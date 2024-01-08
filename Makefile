include ../Make.defines


PROGS =	server client

STAGES = $(wildcard ./stages/*.c)
EVENTS = $(wildcard ./events/*.c)
UTILS = $(wildcard ./utils/*.c)


all: ${PROGS} ${STAGES} ${UTILS}


server: server.o
	${CC} ${CFLAGS} -o $@ server.o ${STAGES} ${EVENTS} ${UTILS} ${LIBS}

client: client.o
	${CC} ${CFLAGS} -o $@ client.o ${STAGES} ${EVENTS} ${UTILS} ${LIBS}
