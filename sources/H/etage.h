#ifndef ETAGE_H

#define ETAGE_H
#include "../H/piece.h"

#define COLS 20
#define ROWS 20

struct Etage {
    int* Idsalles;
    int** etage;
    int width;
    int height;
    Piece** piece;
};

typedef struct Etage Etage;

Etage* createMap();

int randomId(Etage* e,int maxSalle); // Renvoie un nombre 

int testId(Etage* e,int id); //Renvoie si la salle existe dans l'etage

int randomDirections();

void placerSalles(Etage* e); // Permet de placer les salle dans l'étages: le plus gros du travail

void printEtage(Etage* e);

void freeEtage(Etage* e);

int randomNbMonster();

int* randomCoordonnee();
#endif
