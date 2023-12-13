#include <pthread.h>
#include "unp.h"

#define DEBUG 1


// Settings
const int MAX_PLAYER = 2;


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
    int connfd = *(int *)arg;
    char *flag = "Accepted";
    Writen(connfd, flag, strlen(flag));
    Close(connfd);
    return NULL;
}


int main() {
    int listenfd, num_players = 0;
    struct sockaddr_in servaddr;

    pthread_t thread_ids[MAX_PLAYER];
    memset(thread_ids, 0, sizeof(thread_ids));

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
                pthread_create(&thread_ids[i], NULL, accept_connection, (void *)&connfd);
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

        for (int i = 0; i < MAX_PLAYER; i++) {
            if (thread_ids[i] != 0) {
                pthread_join(thread_ids[i], NULL);
                if (DEBUG) {
                    printf("Connection #%d closed: %d\n", i, connfd);
                }
                thread_ids[i] = 0;
            }
        }
    }

    return 0;
}
