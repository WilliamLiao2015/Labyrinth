#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"


int FaustPraiseScene(struct GameOption *option) {
    sprintf(option->stage, __func__);
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "「了不起！」\n"
        "浮士德用力鼓掌，「我果然沒有看錯人！」\n"
        "無視你警惕的目光，他再度躬身，「那麼現在，這座地下大迷宮的大門正式為閣下敞開——」\n"
        "<options>\n"
        "1. 「……」\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice) {
        case 1:
            option->next = &EventDispatcher;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &FaustPraiseScene;
            break;
    }

    return 0;
}
