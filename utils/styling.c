#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../utils.h"


int typing_delay = 15;
int reading_delay = 300;


// Typing function without color
void type(const char *string) {
    printf("\033[0m");
    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
        fflush(stdout);
        msleep(typing_delay);
    }
    msleep(reading_delay);
    printf("\n");
}

// Typing function with only foreground color
void ftype(const char *string, int fg) {
    printf("\033[3%dm", fg);
    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
        fflush(stdout);
        msleep(typing_delay);
    }
    msleep(reading_delay);
    printf("\n\033[0m");
}

// Typing function with only background color
void btype(const char *string, int bg) {
    printf("\033[4%dm", bg);
    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
        fflush(stdout);
        msleep(typing_delay);
    }
    msleep(reading_delay);
    printf("\n\033[0m");
}

// Typing function with colors
void fbtype(const char *string, int fg, int bg) {
    printf("\033[3%d;4%dm", fg, bg);
    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
        fflush(stdout);
        msleep(typing_delay);
    }
    msleep(reading_delay);
    printf("\n\033[0m");
}


// Clear screen
void clear() {
    printf("\033[2J");
    printf("\033[0;0H");
    fflush(stdout);
}
