#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int VictoryScene(struct StageOption *option) {
    char message[MAXLINE];

    sprintf(
        message,
        "<clear>\n"
        "你擊敗了%s！\n"
        "獲得 %d 經驗，獲得 %d 金幣\n"
        "<options>\n",
        option->battle_info->monster->name,
        option->battle_info->monster->exp,
        option->battle_info->monster->reward
    );
    Writen(option->connfd, message, strlen(message));
    option->next = &VictoryScene; // TODO: Plot

    return 0;
}
