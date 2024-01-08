#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../globals.h"


int BattleScene(struct GameOption *option) {
    int num_skills = 0;
    char recvline[MAXLINE], message[MAXLINE], battle_log[MAXLINE];
    struct Monster *monster = option->battle_info->monster;

    sprintf(
        message,
        "<clear>\n"
        "你遭遇了%s！\n"
        "你決定……\n"
        "<options>\n",
        monster->name
    );

    for (int i = 0; i < sizeof(option->player->skills) / sizeof(struct Skill *); i++) {
        if (option->player->skills[i] == NULL) break;
        sprintf(
            message + strlen(message),
            "%d. %s\n",
            i + 1,
            option->player->skills[i]->name
        );
        num_skills++;
    }

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    if (choice < 1 || choice > num_skills) {
        option->next = &InvalidScene;
        option->redirect_to = &BattleScene;
        return 0;
    }

    struct Skill *skill = option->player->skills[choice - 1];

    sprintf(battle_log, "<clear>\n你使用%s攻擊了%s！\n", skill->name, monster->name);
    Writen(option->connfd, battle_log, strlen(battle_log));
    monster->hp -= skill->atk - monster->def;
    if (monster->hp <= 0) {
        option->next = &VictoryScene;
        return 0;
    }
    msleep(500);

    sprintf(battle_log, "<clear>\n%s攻擊了你！\n", monster->name);
    Writen(option->connfd, battle_log, strlen(battle_log));
    option->player->hp -= monster->atk - option->player->def;
    if (option->player->hp <= 0) {
        option->next = &DefeatedScene;
        return 0;
    }
    msleep(500);

    option->next = &BattleScene;

    return 0;
}
