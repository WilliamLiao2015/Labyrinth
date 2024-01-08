#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"

int EncounterMarketEvent(struct GameOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你打起精神，往前行進\n"
        "周圍開始變的嘈雜，你似乎聽到有攤販在大聲吆喝\n"
        "看來這裡是市集，一名商人來到你面前，向你展示了貨物\n"
        "<options>\n"
        "1. ($100)隱約散發著氤氳紫氣的肉塊\n"
        "2. ($200)流竄藍光的瓶子\n"
        "3. ($10000)老闆的傳家寶\n"
        "4. 離開市集\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch(choice) {
        case 1:
            if(option->player->money >= 100){
                option->player->money -= 100;
                option->player->hp += 50;
                char *buy_message = (
                    "<clear>\n"
                    "你購買了散發著紫氣的肉塊\n"
                    "hp + 50\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            } else{
                char *buy_message = (
                    "<clear>\n"
                    "餘額不足，無法購買\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            }
        break;
        case 2:
            if(option->player->money >= 200){
                option->player->money -= 200;
                option->player->atk += 10;
                char *buy_message = (
                    "<clear>\n"
                    "你購買了流竄藍光的瓶子\n"
                    "atk + 10\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            } else{
                char *buy_message = (
                    "<clear>\n"
                    "餘額不足，無法購買\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            }
        break;
        case 3:
            if(option->player->money >= 10000){
                option->player->money -= 10000;
                char *buy_message = (
                    "<clear>\n"
                    "你購買了老闆的傳家寶\n"
                    "甚麼事都沒發生\n"
                    "該死，被騙了\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            } else{
                char *buy_message = (
                    "<clear>\n"
                    "餘額不足，無法購買\n"
                );
                Writen(option->connfd, buy_message, strlen(buy_message));
                msleep(500);
                option->next = &EncounterMarketEvent;
            }
        break;
        case 4:
            option->next = &EventDispatcher;
        break;
        default:
        option->next = &InvalidScene;
        option->redirect_to = &EncounterGhostEvent;
        break;
    }

    return 0;
}