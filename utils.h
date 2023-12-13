#ifndef UTILS_H
#define UTILS_H
#endif


// Color declarations
extern const int BLACK;
extern const int RED;
extern const int GREEN;
extern const int YELLOW;
extern const int BLUE;
extern const int MAGENTA;
extern const int CYAN;
extern const int WHITE;


// Styling functions
extern const void ntype(const char *string);
extern const void type(const char *string, int fg, int bg);
extern const void clear();


// Timing functions
extern const void msleep(int period);
