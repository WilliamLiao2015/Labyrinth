#include <unistd.h>


void msleep(int period) {
    usleep(period * 1000);
}
