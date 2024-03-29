#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int VictoryScene(struct GameOption *option) {
    char message[MAXLINE];

    option->player->exp += option->battle_info->monster->exp;
    option->player->money += option->battle_info->monster->reward;

    sprintf(
        message,
        "<clear>\n"
        "你擊敗了%s！\n"
        "獲得 %d 經驗，獲得 %d 金幣\n",
        option->battle_info->monster->name,
        option->battle_info->monster->exp,
        option->battle_info->monster->reward
    );
    Writen(option->connfd, message, strlen(message));
    option->next = option->battle_info->next;

    msleep(1500);

    return 0;
}
