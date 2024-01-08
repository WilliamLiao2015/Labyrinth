#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int EpilogueScene(struct GameOption *option) {
    sprintf(option->stage, __func__);
    char *message = (
        "<clear>\n"
        "盛大的演出也需要中場休息，你的眼神失去了光彩，雙眼緩緩的闔上\n"
        "你的意識逐漸模糊，開始感覺不到自己的身體...\n"
        "<pause>\n"
    );

    Writen(option->connfd, message, strlen(message));

    return 1;
}
