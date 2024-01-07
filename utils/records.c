#include <stdio.h>
#include <string.h>
#include "../types.h"
#include "../utils.h"
#include "../stages.h"


void save_records(struct StageOption *option, char* filename) {
    int error;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    error = fprintf(fp, "%s\n", option->player->name);
    error = fprintf(fp, "%d\n", option->player->level);
    error = fprintf(fp, "%d\n", option->player->hp);
    error = fprintf(fp, "%d\n", option->player->atk);
    error = fprintf(fp, "%d\n", option->player->def);
    error = fprintf(fp, "%d\n", option->player->exp);
    error = fprintf(fp, "%d\n", option->player->money);
    int inventory_count = 0, skills_count = 0;
    for (int i = 0; i < 10; i++) {
        if (option->player->inventory[i] != NULL) {
            inventory_count += 1;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (option->player->skills[i] != NULL) {
            skills_count += 1;
        }
    }
    error = fprintf(fp, "%d\n", inventory_count);
    for (int i = 0; i < 10; i++) {
        if (option->player->inventory[i] != NULL) {
            error = fprintf(fp, "%s\n", option->player->inventory[i]->item.tag);
            error = fprintf(fp, "%d\n", option->player->inventory[i]->item.price);
            error = fprintf(fp, "%d\n", option->player->inventory[i]->quantity);
        }
    }
    error = fprintf(fp, "%d\n", skills_count);
    for (int i = 0; i < 10; i++) {
        if (option->player->skills[i] != NULL) {
            error = fprintf(fp, "%s\n", option->player->skills[i]->tag);
            error = fprintf(fp, "%d\n", option->player->skills[i]->atk);
            error = fprintf(fp, "%d\n", option->player->skills[i]->cd);
        }
    }
    error = fprintf(fp, "%s\n", option->stage);
    if (error < 0) printf("Error writing to file!\n");
    fclose(fp);
}

void read_records(struct StageOption *option, char* filename) {
    int error;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("冒險者您好，歡迎來到 Labyrinth\n");
        return;
    }
    error = fscanf(fp, "%s\n", option->player->name);
    error = fscanf(fp, "%d\n", &option->player->level);
    error = fscanf(fp, "%d\n", &option->player->hp);
    error = fscanf(fp, "%d\n", &option->player->atk);
    error = fscanf(fp, "%d\n", &option->player->def);
    error = fscanf(fp, "%d\n", &option->player->exp);
    error = fscanf(fp, "%d\n", &option->player->money);
    printf("歡迎回來，%s\n", option->player->name);
    int inventory_count = 0, skills_count = 0;
    error = fscanf(fp, "%d\n", &inventory_count);
    for (int i = 0; i < inventory_count; i++) {
        char tag[20];
        int price, quantity;
        error = fscanf(fp, "%s", tag);
        error = fscanf(fp, "%d", &price);
        error = fscanf(fp, "%d", &quantity);
        option->player->inventory[i]->item.price = price;
        strcpy(option->player->inventory[i]->item.tag, tag);
        option->player->inventory[i]->quantity = quantity;
    }
    error = fscanf(fp, "%d", &skills_count);
    for (int i = 0; i < skills_count; i++) {
        char tag[20];
        int atk, cd;
        error = fscanf(fp, "%s\n", tag);
        error = fscanf(fp, "%d\n", &atk);
        error = fscanf(fp, "%d\n", &cd);
        strcpy(option->player->skills[i]->tag, tag);
        option->player->skills[i]->atk = atk;
        option->player->skills[i]->cd = cd;

        if (strcmp(tag, "punch") == 0) {
            strcpy(option->player->skills[i]->name, "拳擊");
        } else if(strcmp(tag, "slash") == 0) {
            strcpy(option->player->skills[i]->name, "劈砍");
        } else if(strcmp(tag, "fireball") == 0) {
            strcpy(option->player->skills[i]->name, "火球術");
        }
        //printf("name = %s\n", option->player->skills[i]->name);
    }
    error = fscanf(fp, "%s", option->stage);
    if (strcmp(option->stage, "PrologueScene") == 0) {
        option->next = &PrologueScene;
    } else if (strcmp(option->stage, "BreakChainScene") == 0) {
        option->next = &BreakChainScene;
    } else if (strcmp(option->stage, "StayInPlaceScene") == 0) {
        option->next = &StayInPlaceScene;
    } else if (strcmp(option->stage, "FaustIntroductionScene") == 0) {
        option->next = &FaustIntroductionScene;
    } else if (strcmp(option->stage, "FaustRejectScene") == 0) {
        option->next = &FaustRejectScene;
    } else if (strcmp(option->stage, "FaustKillScene") == 0) {
        option->next = &FaustKillScene;
    } else if (strcmp(option->stage, "EpilogueScene") == 0) {
        option->next = &EpilogueScene;
    }
    if (error < 0) printf("Error reading from file!\n");
    fclose(fp);
}
