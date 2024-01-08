#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"

int GetExperienceBottleEvent(struct GameOption *option){
char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你打起精神，走上了這條寂靜的道路\n"
        "路旁閃爍的亮光吸引了你\n"
        "一個可疑的瓶子，上面寫著陌生的語言，其中有綠光流竄\n"
        "<options>\n"
        "1. 不予理會\n"
        "2. 撿起來，喝下去！\n"
    );

    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice)
    {
    case 1:
        char * message2 = (
            "<clear>\n"
            "太可疑了...還是不碰為妙\n"
        );
        Writen(option->connfd, message2, strlen(message2));
        msleep(1500);
        option->next = &EventDispatcher;
        break;
    case 2:
        char * message3 = (
            "<clear>\n"
            "你一口把瓶子裡的東西給喝了下去\n"
            "薄荷味，還不錯，身體似乎發生了甚麼改變\n"
            "經驗值 +10\n"
        );
        Writen(option->connfd, message3, strlen(message3));
        msleep(1500);
        option->next = &EventDispatcher;
        break;
    default:
        option->next = &InvalidScene;
        option->redirect_to = &GetExperienceBottleEvent;
        break;
    }
    return 0;
}