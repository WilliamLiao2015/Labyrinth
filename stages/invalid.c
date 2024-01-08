#include "../unp.h"
#include "../types.h"
#include "../stages.h"


int InvalidScene(struct GameOption *option) {
    char *message = (
        "<clear>\n"
        "選擇無效，請重新選擇！\n"
        "<pause>\n"
    );

    Writen(option->connfd, message, strlen(message));

    option->next = option->redirect_to;
    option->redirect_to = NULL;

    return 0;
}
