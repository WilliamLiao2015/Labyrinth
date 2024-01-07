#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int DefeatedScene(struct StageOption *option) {
    char message[MAXLINE];

    sprintf(
        message,
        "<clear>\n"
        "身體的疲憊無法再忽視，失血使你的視野逐漸昏暗，身上的傷痕越來越多...\n"
        "你最終敗給了%s\n",
        option->battle_info->monster->name
    );
    Writen(option->connfd, message, strlen(message));
    option->next = &EpilogueScene;

    return 0;
}
