#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

#define MAX_PLAYER 2


extern int num_players;

extern struct Player players[MAX_PLAYER];
extern pthread_t thread_ids[MAX_PLAYER];

#endif
