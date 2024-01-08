#include "unp.h"
#include "types.h"
#include "utils.h"


int handle_error(int error) {
    if (error) {
        fbtype("伺服器沒有連線，請稍後再試\n", WHITE, RED);
        clear();
        return 1;
    }
    return 0;
}


int display(char *message, int *is_paused) {
    char *line = strtok(message, "\n");
    int is_options = 0;
    while (line != NULL) {
        if (strcmp(line, "<clear>") == 0) clear();
        else if (strcmp(line, "<options>") == 0) is_options = 1;
        else if (strcmp(line, "<pause>") == 0) *is_paused = 1;
        else if (is_options) {
            ftype(line, BLUE);
            type("\n");
        } else {
            type(line);
            type("\n\n");
        }
        line = strtok(NULL, "\n");
    }
    return is_options;
}


void game_loop(int sockfd) {
    while (1) {
        char recvline[MAXLINE];
        int error = get_message(sockfd, recvline), is_paused = 0;
        if (handle_error(error)) return;
        int has_options = display(recvline, &is_paused);
        if (has_options) {
            printf("\n> ");
            int choice;
            int n = scanf("%d%*c", &choice); // eat up the newline and prevent getchar not working
            if (n == EOF) break;
            char choice_string[MAXLINE];
            sprintf(choice_string, "%d", choice);
            Writen(sockfd, choice_string, strlen(choice_string));
        }
        if (is_paused) {
            type("按下 Enter 鍵以繼續……\n");
            getchar();
        }
    }
}


int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

	if (argc != 2) err_quit("usage: client <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

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
        type("請問您的名字是？\n\n");
        printf("> ");
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
