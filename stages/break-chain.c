#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int BreakChainScene(struct StageOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你決定嘗試掙脫，但是鐵鍊太過堅固，一時之間無法掙脫\n"
        "鐵鍊撞擊，發出了清脆的聲響\n"
        "突然間，一陣清亮的腳步聲自外頭傳來\n"
        "你警惕地看著地牢的入口，只見一名身穿黑色正裝、臉上戴著單片眼鏡的男子步履從容地走了進來\n"
        "<options>\n"
        "1. 「放我出去！」\n"
        "2. 「你是誰？」\n"
        "3. 「……」\n"
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
            option->next = &BreakChainScene;
            break;
        case 3:
            option->next = &BreakChainScene;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &PrologueScene;
            break;
    }

    return 0;
}
