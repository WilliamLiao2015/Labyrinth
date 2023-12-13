#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../utils.h"


void type(const char *string, int fg, int bg) {
    printf("\033[3%d;4%dm", fg, bg);
    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
        fflush(stdout);
        usleep(10000);
    }
    printf("\n\033[0m");
}

void clear() {
    printf("\033[2J");
    printf("\033[0;0H");
    fflush(stdout);
}
