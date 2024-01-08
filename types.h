#ifndef TYPES_H
#define TYPES_H
#define DEBUG 1


struct ThreadArg {
    int connfd;
    int index;
};


struct Item {
    char name[20];
    char tag[20];
    int price;
};

struct Slot {
    struct Item item;
    int quantity;
};

struct Skill {
    char name[20];
    char tag[20];
    int atk;
    int cd; // Cooldown
};

struct Player {
    char name[20];
    int level;
    int hp;
    int atk;
    int def;
    int exp;
    int money;
    struct Slot *inventory[10];
    struct Skill *skills[10];
};


struct GameOption;

typedef int GameStage(struct GameOption *option);

struct Monster {
    char name[20];
    int level;
    int hp;
    int atk;
    int def;
    int exp;
    int reward;
};

struct BattleInfo {
    struct Monster *monster;
    GameStage *next;
};

struct GameOption {
    int connfd;
    char stage[50];
    GameStage *next;
    GameStage *redirect_to;
    struct Player *player;
    struct BattleInfo *battle_info;
};

#endif
