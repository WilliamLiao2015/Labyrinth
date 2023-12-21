#include <pthread.h>
#include "unp.h"
#include "types.h"
#include "utils.h"
#include "stages.h"

#define MAX_PLAYER 2


// Global variables
int num_players = 0;

struct Player players[MAX_PLAYER];


// Reject connection
void *reject_connection(void *arg) {
    int connfd = *(int *)arg;
    char *flag = "Rejected";
    Writen(connfd, flag, strlen(flag));
    Close(connfd);
    pthread_exit(NULL);
}


// Accept connection
void *accept_connection(void *arg) {
    int connfd = ((struct ThreadArg *)arg)->connfd;
    int index = ((struct ThreadArg *)arg)->index;
    char *flag = "Accepted", recvline[MAXLINE];

    Writen(connfd, flag, strlen(flag));

    int error = get_message(connfd, recvline);
    if (error) {
        Close(connfd);
        pthread_exit(NULL);
    }
    if (DEBUG) printf("Player name: %s\n", recvline);

    strcpy(players[index].name, recvline);
    players[index].money = 1000;
    memset(players[index].inventory, 0, sizeof(players[index].inventory));

    StageFunction *next = &PrologueScene;
    struct StageOption *option = (struct StageOption *)malloc(sizeof(struct StageOption));
    option->connfd = connfd;

    while (1) {
        error = (*next)(option);
        if (error) {
            Close(connfd);
            pthread_exit(NULL);
        }
        next = option->next;
    }

    free(option);

    Close(connfd);
    return NULL;
}


int main() {
    int listenfd;
    struct sockaddr_in servaddr;
    pthread_t thread_ids[MAX_PLAYER] = {0};

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    while (1) {
        int connfd;
        struct sockaddr_in cliaddr;
        socklen_t clilen = sizeof(cliaddr);

        connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

        for (int i = 0; i < MAX_PLAYER; i++) {
            if (thread_ids[i] == 0) {
                struct ThreadArg *thread_args = (struct ThreadArg *)malloc(sizeof(struct ThreadArg));
                thread_args->connfd = connfd;
                thread_args->index = i;
                pthread_create(&thread_ids[i], NULL, accept_connection, (void *)thread_args);
                if (DEBUG) printf("Connection #%d established: %d\n", i, connfd);
                num_players++;
                break;
            }
            if (i == MAX_PLAYER - 1) {
                pthread_t reject_thread;
                pthread_create(&reject_thread, NULL, reject_connection, (void *)&connfd);
                if (DEBUG) printf("Connection #%d closed: %d\n", i, connfd);
            }
        }
    }

    for (int i = 0; i < MAX_PLAYER; i++) {
        if (thread_ids[i] != 0) {
            pthread_join(thread_ids[i], NULL);
            if (DEBUG) printf("Connection #%d closed\n", i);
            num_players--;
            thread_ids[i] = 0;
        }
    }

    return 0;
}
