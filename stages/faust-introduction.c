#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int FaustIntroductionScene(struct StageOption *option) {
    sprintf(option->stage, __func__);
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "「鄙人浮士德，現在是這座地下大迷宮的總管。」\n"
        "男子躬身鞠躬，如是說道，「由於先前魔王死去，現在這座地下大迷宮已經失控。我需要有人幫助它回復正常。」\n"
        "<options>\n"
        "1. 「那就放我出去，我幫你解決。」\n"
        "2. 「……」\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice) {
        case 1:
            option->next = &FaustRejectScene;
            break;
        case 2:
            option->next = &FaustKillScene;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &FaustIntroductionScene;
            break;
    }

    return 0;
}
