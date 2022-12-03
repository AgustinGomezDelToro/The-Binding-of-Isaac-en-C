#ifndef MONSTER_H
#define MONSTER_H

struct Monster {
    char nameItem[20];
    float hpMax;
    int shoot; //bool pour les tirs
    int ss; //bool pour les tirs spectrals
    int flight; //bool pour le vol
};

typedef struct Monster Monster;

Monster* createMonster();

void printMonster(Monster* obj);

void modifyMonster();

void freeMonster(Monster* obj);

void addMonsterToFile(Monster* obj, char* file);

void deleteMonster();

void printAllMonster();

int foundMonster(char nameItem[20]);


#endif