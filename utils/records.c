#include <stdio.h>
#include <string.h>
#include "../types.h"
#include "../utils.h"
#include "../stages.h"

void save_records(struct StageOption *option, char* filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s\n", option->player->name);
    fprintf(fp, "%d\n", option->player->level);
    fprintf(fp, "%d\n", option->player->hp);
    fprintf(fp, "%d\n", option->player->atk);
    fprintf(fp, "%d\n", option->player->def);
    fprintf(fp, "%d\n", option->player->exp);
    fprintf(fp, "%d\n", option->player->money);
    int inventory_count = 0, skills_count = 0;
    for (int i = 0; i < 10; i++) {
        if (option->player->inventory[i] != NULL) {
            inventory_count+=1;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (option->player->skills[i] != NULL) {
            skills_count+=1;
        }
    }
    fprintf(fp, "%d\n", inventory_count);
    for (int i = 0; i < 10; i++) {
        if (option->player->inventory[i] != NULL) {
            fprintf(fp, "%s\n", option->player->inventory[i]->item.tag);
            fprintf(fp, "%d\n", option->player->inventory[i]->item.price);
            fprintf(fp, "%d\n", option->player->inventory[i]->quantity);
        }
    }
    fprintf(fp, "%d\n", skills_count);
    for (int i = 0; i < 10; i++) {
        if (option->player->skills[i] != NULL) {
            fprintf(fp, "%s\n", option->player->skills[i]->tag);
            fprintf(fp, "%d\n", option->player->skills[i]->atk);
            fprintf(fp, "%d\n", option->player->skills[i]->cd);
        }
    }
    fclose(fp);
}

void read_records(struct StageOption *option, char* filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("冒險者您好，歡迎來到 Labyrinth\n");
        return;
    }
    fscanf(fp, "%s\n", option->player->name);
    fscanf(fp, "%d\n", &option->player->level);
    fscanf(fp, "%d\n", &option->player->hp);
    fscanf(fp, "%d\n", &option->player->atk);
    fscanf(fp, "%d\n", &option->player->def);
    fscanf(fp, "%d\n", &option->player->exp);
    fscanf(fp, "%d\n", &option->player->money);
    printf("歡迎回來，%s\n", option->player->name);
    int inventory_count = 0, skills_count = 0;
    fscanf(fp, "%d\n", &inventory_count);
    for (int i = 0; i < inventory_count; i++) {
        char name[20], tag[20];
        int price, quantity;
        fscanf(fp, "%s", tag);
        fscanf(fp, "%d", &price);
        fscanf(fp, "%d", &quantity);
        option->player->inventory[i]->item.price = price;
        strcpy(option->player->inventory[i]->item.tag, tag);
        option->player->inventory[i]->quantity = quantity;
    }

    fscanf(fp, "%d", &skills_count);
    for (int i = 0; i < skills_count; i++) {
        char name[20], tag[20];
        int atk, cd;
        fscanf(fp, "%s\n", tag);
        fscanf(fp, "%d\n", &atk);
        fscanf(fp, "%d\n", &cd);
        strcpy(option->player->skills[i]->tag, tag);
        option->player->skills[i]->atk = atk;
        option->player->skills[i]->cd = cd;

        
        if(strcmp(tag, "punch") == 0)
        {
            strcpy(option->player->skills[i]->name, "拳擊");
        }
        else if(strcmp(tag, "slash") == 0)
        {
            strcpy(option->player->skills[i]->name, "劈砍");
        }
        else if(strcmp(tag, "fireball") == 0)
        {
            strcpy(option->player->skills[i]->name, "火球術");
        }
        //printf("name = %s\n", option->player->skills[i]->name);
    }
    fclose(fp);
}
