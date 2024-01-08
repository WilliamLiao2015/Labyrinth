#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"

int GetTreasureEvent(struct GameOption *option) {
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你打起精神，走上了這條寂靜的道路\n"
        "一個破舊的木偶坐在路邊\n"
        "你湊近木偶，發現木偶的胸腔中好像藏著甚麼\n"
        "<options>\n"
        "1. 不予理會\n"
        "2. 撿起來\n"
    );
    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    switch (choice) {
        case 1:
            char *ignore_message = (
                "<clear>\n"
                "你沒有理會木偶，繼續前進\n"
            );
            Writen(option->connfd, ignore_message, strlen(ignore_message));
            msleep(500);
            option->next = &EventDispatcher;
            break;
        case 2:
            char *pick_message_positive = (
                "<clear>\n"
                "你撿起了木偶，發現木偶的胸腔中藏著一袋金幣\n"
                "似乎是無主之物...你獲得了 10 金幣\n"
            );
            char *pick_message_negative = (
                "<clear>\n"
                "你撿起了木偶，發現木偶的胸腔中藏著一顆寶石\n"
                "寶石上散發著不詳的氣息，你趕緊把他丟在地上，手心卻仍被燒了一道傷口\n"
                "你損失了 5 生命\n"
            );
            int random = randint(0, 5);
            char *pick_message = (random) ? pick_message_positive : pick_message_negative;
            if(random) {
                option->player->money += 10;
            } else{
                option->player->hp -= 5;
            }
            Writen(option->connfd, pick_message, strlen(pick_message));
            msleep(1500);
            option->next = &EventDispatcher;
            break;
        default:
            option->next = &InvalidScene;
            option->redirect_to = &GetTreasureEvent;
            break;
    }
    return 0;
}