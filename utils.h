#ifndef UTILS_H
#define UTILS_H


// Color declarations
extern const int BLACK;
extern const int RED;
extern const int GREEN;
extern const int YELLOW;
extern const int BLUE;
extern const int MAGENTA;
extern const int CYAN;
extern const int WHITE;


// Socket functions
extern const int get_message(int sockfd, char *message);


// Styling functions
extern const void type(const char *string);
extern const void ftype(const char *string, int fg);
extern const void btype(const char *string, int bg);
extern const void fbtype(const char *string, int fg, int bg);
extern const void clear();


// Timing functions
extern const void msleep(int period);


// Recording functions
extern const void save_records(struct GameOption *option, char* filename);
extern const void read_records(struct GameOption *option, char* filename);

#endif
