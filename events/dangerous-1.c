#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"

int EncounterBeastEvent(struct GameOption *option)
{
    char recvline[MAXLINE], *message = (
        "<clear>\n"
        "你決定冒險走上這條看似凶險的路\n"
        "此時你調整了前進的步伐\n"
        "<options>\n"
        "1. 緩慢前進\n"
        "2. 警戒的前進\n"
    );
    Writen(option->connfd, message, strlen(message));
    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    struct Monster *beast = (struct Monster *)malloc(sizeof(struct Monster));
    strcpy(beast->name, "被汙染的野獸");
    beast->level = randint(1, 3);
    beast->exp = 10 * beast->level;
    beast->reward = 10 * beast->level;
    beast->hp = 10 * beast->level;
    beast->atk = 5 + beast->level;
    beast->def = 0;

    switch (choice)
    {
        case 1:
            char* message1 = (
                "<clear>\n"
                "你緩步前進\n"
                "突然，你感覺到有什麼東西從你的身後襲來\n"
            );
            Writen(option->connfd, message1, strlen(message1));
            option->battle_info->monster = beast;
            option->battle_info->next = &EventDispatcher;
            option->next = &BattleScene;
            msleep(1500);
            break;
        case 2:
            char* message2 = (
                "<clear>\n"
                "你警戒的前進\n"
                "突然，你感覺到有什麼東西從你的身後襲來\n"
                "足夠的謹慎使你有時間做出反應，你決定...\n"
                "<options>\n"
                "1. 逃跑\n"
                "2. 迎戰\n"
            );
            Writen(option->connfd, message2, strlen(message2));
            char recvline2[MAXLINE];
            int error2 = get_message(option->connfd, recvline2);
            if (error2) return 1;
            if (DEBUG) printf("Player's choice: %s\n", recvline2);
            int choice2 = atoi(recvline2);
            if(choice2 == 1)
            {
                char *escape_message = (
                "<clear>\n"
                "你成功逃脫了野獸的攻擊！\n"
                "你獲得了 10 經驗\n"
                );
                Writen(option->connfd, escape_message, strlen(escape_message));
                msleep(500);
                option->player->exp += 10;
                option->next = &EventDispatcher;
                break;
            }
            else if(choice2 == 2)
            {
                option->battle_info->monster = beast;
                option->battle_info->next = &EventDispatcher;
                option->next = &BattleScene;
                msleep(1500);
                break;
            }
            else
            {
                option->next = &InvalidScene;
                option->redirect_to = &EncounterBeastEvent;
                break;
            }
        default:
            option->next = &InvalidScene;
            option->redirect_to = &EncounterBeastEvent;
            break;
    }
    return 0;
}