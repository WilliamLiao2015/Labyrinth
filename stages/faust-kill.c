#include "../unp.h"
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


int FaustKillScene(struct StageOption *option) {
    char *message = (
        "<clear>\n"
        "見你保持沉默，浮士德扶額，一臉無奈，「那還真是遺憾，那我就只能送你上路了。」\n"
        "他抬起手指，一道猩紅的射線頓時貫穿了你的心臟。\n"
        "你感覺一切的知覺都在離你遠去……\n"
    );

    Writen(option->connfd, message, strlen(message));

    option->next = &PrologueScene;

    return 0;
}
