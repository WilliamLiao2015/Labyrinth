#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int FaustRejectScene(struct StageOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "男子搖搖頭，「不、不，那可不行。」\n"
        "他手一揮，一把生鏽的短劍頓時落在你的腳邊。\n"
        "「除非……你能夠戰勝我的寵物！」\n"
        "<options>\n"
        "1. 「我答應你。」\n"
        "2. 「……」\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    option->battle_info = (struct BattleInfo *) malloc(sizeof(struct BattleInfo));
    option->battle_info->monster = (struct Monster *) malloc(sizeof(struct Monster));
    strcpy(option->battle_info->monster->name, "浮士德的寵物");
    option->battle_info->monster->level = 5;
    option->battle_info->monster->hp = 100;
    option->battle_info->monster->atk = 10;
    option->battle_info->monster->def = 0;
    option->battle_info->monster->exp = 100;
    option->battle_info->monster->reward = 100;

    switch (choice) {
        case 1:
            option->next = &BattleScene;
            break;
        case 2:
            option->next = &BattleScene;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &FaustRejectScene;
            break;
    }

    return 0;
}
