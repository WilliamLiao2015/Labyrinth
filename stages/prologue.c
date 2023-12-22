#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int PrologueScene(struct StageOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "再次睜開雙眼，你發現自己身在一處陌生的地牢中\n"
        "周遭空蕩蕩的，見不到半個人影\n"
        "你試著站起身，卻發現自己的雙手被鐵鏈鎖住\n"
        "你決定……\n"
        "<options>\n"
        "1. 掙脫鐵鍊\n"
        "2. 留在原地\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice) {
        case 1:
            option->next = &BreakChainScene;
            break;
        case 2:
            option->next = &StayInPlaceScene;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &PrologueScene;
            break;
    }

    return 0;
}
