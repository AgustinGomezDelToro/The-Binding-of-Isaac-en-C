#ifndef ITEM_H
#define ITEM_H

struct Item {
    char nameItem[20];
    float hpMax;
//    float shield;
    //  float dmg;
    int shoot; //bool pour les tirs
    int ss; //bool pour les tirs spectrals
    int flight; //bool pour le vol
};

typedef struct Item Item;

Item* createMonster();

void printMonster(Item* obj);

void modifyMonster();

void freeMonster(Item* obj);

void addMonsterToFile(Item* obj, char* file);

void deleteMonster();

void printAllMonster();

#endif