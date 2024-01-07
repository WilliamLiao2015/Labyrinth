#include <pthread.h>
#include "unp.h"
#include "types.h"
#include "utils.h"
#include "stages.h"
#include "globals.h"


// Global variables initialization
int num_players = 0;
struct Player players[MAX_PLAYER] = {0};
pthread_t thread_ids[MAX_PLAYER] = {0};


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
        thread_ids[index] = 0;
        num_players--;
        Close(connfd);
        pthread_exit(NULL);
    }
    if (DEBUG) printf("Player name: %s\n", recvline);

    strcpy(players[index].name, recvline);
    players[index].level = 1;
    players[index].hp = 100;
    players[index].atk = 10;
    players[index].def = 0;
    players[index].exp = 0;
    players[index].money = 1000;
    memset(players[index].inventory, 0, sizeof(players[index].inventory));
    players[index].skills[0] = &(struct Skill) {
        .name = "拳擊",
        .tag = "punch",
        .atk = 5,
        .cd = 0,
    };
    players[index].skills[1] = &(struct Skill) {
        .name = "劈砍",
        .tag = "slash",
        .atk = 10,
        .cd = 1,
    };
    players[index].skills[2] = &(struct Skill) {
        .name = "火球術",
        .tag = "fireball",
        .atk = 20,
        .cd = 2,
    };

    StageFunction *next = &PrologueScene;
    struct StageOption *option = (struct StageOption *)malloc(sizeof(struct StageOption));

    option->connfd = connfd;
    option->player = &players[index];

    char filename[MAXLINE];
    sprintf(filename, "player-data/%s.txt", players[index].name);
    read_records(option, filename);

    while (1) {
        error = (*next)(option);
        save_records(option, filename);
        option->player->money += 100;
        option->player->skills[0]->atk+=1;
        if (error) {
            save_records(option, filename); // TODO: save player records
            thread_ids[index] = 0;
            num_players--;
            Close(connfd);
            pthread_exit(NULL);
        }
        next = option->next;
    }

    free(option);

    Close(connfd);
    return NULL;
}


int main(int argc, char **argv) {
    int listenfd;
    struct sockaddr_in servaddr;

	if (argc != 2) err_quit("usage: server <IPaddress>");

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

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
