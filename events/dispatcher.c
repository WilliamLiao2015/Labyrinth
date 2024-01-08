#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"
#include "../events.h"


struct EventType event_types[] = {
    {
        .name = "陰森",
        .description = "陰風拂面而來，令你感到一股刺骨的寒意",
        .instances = {&EncounterGhostEvent}
    },
    // {
    //     .name = "靜謐",
    //     .description = "遠方一片寂靜，好像路的另一頭什麼也沒有",
    // },
    // {
    //     .name = "凶險",
    //     .description = "你感覺到一股危險的氣息，好像有什麼東西在等著你",
    // }
};


int EventDispatcher(struct GameOption *option) {
    sprintf(option->stage, __func__);
    int num_branches = randint(1, 5);
    char quantifier[5][4] = {"一", "二", "三", "四", "五"};
    char recvline[MAXLINE], message[MAXLINE];
    GameStage *events[num_branches];

    sprintf(
        message,
        "<clear>\n"
        "你來到了一處分岔口\n"
        "這裡有%s條道路\n"
        "你決定……\n"
        "<options>\n",
        quantifier[num_branches - 1]
    );
    for (int i = 0; i < num_branches; i++) {
        int instances_count = 0;
        char option_string[100];
        struct EventType *event_type = &event_types[randint(0, sizeof(event_types) / sizeof(struct EventType) - 1)];
        for (int j = 0; j < sizeof(event_type->instances) / sizeof(GameStage *); j++) {
            if (event_type->instances[j] == NULL) break;
            instances_count++;
        }
        events[i] = event_type->instances[randint(0, instances_count - 1)];
        sprintf(
            option_string,
            "%d. 一條%s的路\n",
            i + 1,
            event_type->description
        );
        strcat(message, option_string);
    }
    Writen(option->connfd, message, strlen(message));

    int error = get_message(option->connfd, recvline);
    if (error) return 1;
    if (DEBUG) printf("Player's choice: %s\n", recvline);

    int choice = atoi(recvline);

    if (choice < 1 || choice > num_branches) {
        option->next = &InvalidScene;
        option->redirect_to = &EventDispatcher;
        return 0;
    }
    for (int i = 0; i < num_branches; i++) {
        printf("choice: %d, i: %d\n", choice, i);
        if (choice == i + 1) {
            option->next = events[i];
            break;
        }
    }

    return 0;
}
