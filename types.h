#ifndef TYPES_H
#define TYPES_H
#endif


struct ThreadArg {
    int connfd;
    int index;
};


struct Item {
    char name[20];
    int price;
};

struct Slot {
    struct Item item;
    int quantity;
};

struct Player {
    char name[20];
    int money;
    struct Slot inventory[10];
};
