#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"


int EncounterGhostEvent(struct GameOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你打起精神，往前行進\n"
        "突然一陣狂風大作，你抬起手遮擋襲來的風砂\n"
        "忽然間，你敏銳地察覺到身後似乎有什麼東西\n"
        "<options>\n"
        "1. 轉過身\n"
        "2. 往前跑\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    struct Monster *ghost = (struct Monster *)malloc(sizeof(struct Monster));
    strcpy(ghost->name, "幽靈");
    ghost->level = randint(1, 3);
    ghost->exp = 10 * ghost->level;
    ghost->reward = 10 * ghost->level;
    ghost->hp = 10 * ghost->level;
    ghost->atk = 5 + ghost->level;
    ghost->def = 0;

    switch (choice) {
        case 1:
            option->battle_info->monster = ghost;
            option->battle_info->next = &EventDispatcher;
            option->next = &BattleScene;
            break;
        case 2:
            char *escape_message = (
                "<clear>\n"
                "你成功逃脫了幽靈的攻擊！\n"
                "你獲得了 10 經驗\n"
            );
            Writen(option->connfd, escape_message, strlen(escape_message));
            msleep(500);
            option->player->exp += 10;
            option->next = &EventDispatcher;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &EncounterGhostEvent;
            break;
    }

    return 0;
}
