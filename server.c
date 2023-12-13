#include <sqlite3.h>
#include "unp.h"

#define DEBUG 0


int main() {
    printf("%s\n", sqlite3_libversion());

    return 0;
}
