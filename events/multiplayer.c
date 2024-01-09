#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"
#include "../globals.h"

int EncounterPlayerEvent(struct GameOption *option) {
    char message[MAXLINE];
    sprintf(message, ("<clear>\n"
             "你遇到了 %d 名其他玩家\n"), 1);
    
    if((option->otherPlayer->skills[0]) != NULL) {
        strcat(message, option->otherPlayer->name);
        strcat(message, "\n");
    }

    strcat(message, "<options>\n"
                    "1. 離開\n"
                    "2. 留下\n");
    Writen(option->connfd, message, strlen(message));
    msleep(500);

    char recvline[MAXLINE];
    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);
    if(choice == 1) {
        option->next = &EventDispatcher;
        return 0;
    }
    else if(choice ==2){
        option->next = &EncounterPlayerEvent;
        return 0;
    }
    else {
        option->next = &InvalidScene;
        option->redirect_to = &EncounterPlayerEvent;
        return 0;
    }
    return 0;
}