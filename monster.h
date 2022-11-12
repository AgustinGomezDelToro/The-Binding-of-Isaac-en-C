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

Item* createItem();

void printItem(Item* obj);

void modifyItem();

void freeItem(Item* obj);

void addItemToFile(Item* obj, char* file);

void deleteItem();

void printAllItem();

#endif