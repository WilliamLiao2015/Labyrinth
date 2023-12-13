#include "../unp.h"
#include "../utils.h"


int get_message(int sockfd, char *message) {
    int n = Read(sockfd, message, MAXLINE);
    if (n == 0) return 1;
    message[n] = 0;
    return 0;
}
