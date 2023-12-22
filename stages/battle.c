#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int BattleScene(struct StageOption *option) {
    char recvline[MAXLINE], message[MAXLINE];

    sprintf(
        message,
        "<clear>\n"
        "你遭遇了%s！\n"
        "你決定……\n"
        "<options>\n",
        option->battle_info->monster->name
    );

    for (int i = 0; i < sizeof(option->player->skills) / sizeof(struct Skill *); i++) {
        if (option->player->skills[i] == NULL) continue;
        sprintf(
            message + strlen(message),
            "%d. %s\n",
            i + 1,
            option->player->skills[i]->name
        );
    }

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice) {
        case 1:
            option->next = &BattleScene;
            break;
        case 2:
            option->next = &BattleScene;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &BattleScene;
            break;
    }

    return 0;
}
