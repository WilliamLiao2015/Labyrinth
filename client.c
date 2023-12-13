#include "unp.h"
#include "utils.h"

#define DEBUG 0


int handle_error(int error) {
    if (error) {
        fbtype("伺服器沒有連線，請稍後再試\n", WHITE, RED);
        clear();
        return 1;
    }
    return 0;
}


void display(char *message) {
    char *line = strtok(message, "\n");
    while (line != NULL) {
        if (strcmp(line, "<clear>") == 0) clear();
        else type(line);
        type("\n");
        line = strtok(NULL, "\n");
    }
}


void game_loop(int sockfd) {
    while (1) {
        char recvline[MAXLINE];
        int error = get_message(sockfd, recvline);
        if (handle_error(error)) return;
        display(recvline);
    }
}


int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    char recvline[MAXLINE];
    int error = get_message(sockfd, recvline);

    if (handle_error(error)) return 0;

    clear();

    if (strcmp(recvline, "Rejected") == 0) {
        fbtype("伺服器已滿，請稍後再試\n", WHITE, RED);
        clear();
        Shutdown(sockfd, SHUT_WR);
        return 0;
    } else if (strcmp(recvline, "Accepted") == 0) {
        fbtype("冒險者您好，歡迎來到 Labyrinth\n\n", WHITE, GREEN);
        type("請問您的名字是？");
        int n = scanf("%s", recvline);
        clear();
        if (n != EOF) {
            Writen(sockfd, recvline, strlen(recvline));
            game_loop(sockfd);
        }
        Shutdown(sockfd, SHUT_WR);
        return 0;
    }

    return 0;
}
