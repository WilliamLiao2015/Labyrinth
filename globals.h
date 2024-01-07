#ifndef GLOBALS_H
#define GLOBALS_H
#endif

#include <pthread.h>

#define MAX_PLAYER 2


int num_players;

struct Player players[MAX_PLAYER];
pthread_t thread_ids[MAX_PLAYER];
