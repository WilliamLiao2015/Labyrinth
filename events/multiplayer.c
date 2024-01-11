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

    strcat(message, "<options>\n"
                    "1. 離開\n"
                    "2. 留下\n"
                    "3. 留下一些物資\n"
                    "4. 取走先前留下的物資\n");
    if((option->otherPlayer->skills[0]) != NULL) {
        
    }
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
    else if(choice == 3) {
        char message2[MAXLINE];
        sprintf(message2, ("<clear>\n"
             "你留下了 100 個金幣\n"));
        Writen(option->connfd, message2, strlen(message2));
        msleep(1500);
        option->player->money -= 100;
        option->self_resources += 100;
        option->next = &EncounterPlayerEvent;
        return 0;
    }
    else if(choice ==4) {
        char message2[MAXLINE];
        sprintf(message2, ("<clear>\n"
             "你取走了 %d 個金幣\n"), option->server_shared_resources);
        Writen(option->connfd, message2, strlen(message2));
        msleep(1500);
        option->player->money += option->server_shared_resources;
        option->server_shared_resources = -1;
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