#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../H/etage.h"

#define COLS 15
#define ROWS 15

Etage *createMap()
{
    Etage *e = malloc(sizeof(Etage));
    e->width = COLS;  // columns
    e->height = ROWS; // rows
    e->etage = malloc(sizeof(int *) * e->height);

    for (int i = 0; i < e->height; i += 1)
    {
        e->etage[i] = malloc(sizeof(int) * e->width);
        for (int j = 0; j < e->width; j += 1)
        {
            e->etage[i][j] = 0;
        }
    }
    e->Idsalles = malloc(sizeof(int) * 14);
    return e;
}

int randomId(Etage *e, int maxSalles)
{
    srand(time(NULL));
    int i = 0;

    if (maxSalles < 10)
    {
        printf("Seulement %d disponibles, veuiller générer plus de salles.\n", maxSalles);
        return 0;
    }

    int id = 0;
    while (i < 10)
    {   
        id = 1 + rand() % maxSalles; 
        int existe = testId(e, id);
        //printf("%d %d\n",id,existe);
        if (existe != 1)
        {
            e->Idsalles[i] = id;
            i += 1;
        }
    }

    int special = -1;
    while (i<14)                    // -1=Spawner , -2 = Item Room , -3= Boss, -4 Item Room Bonus Apres le boss
    {
        e->Idsalles[i] = special;
        special-=1;
        i+=1;
    }
    
    
    return 1;
}

int testId(Etage *e, int id)
{
    for (int i = 0; i < 10; i += 1)
    {
        if (id == e->Idsalles[i])
        {
            return 1;
        }
    }
    return 0;
}

void printEtage(Etage *e)
{
    int cmpt = 0;
    for (int i = 0; i < e->height; i += 1)
    {
        for (int j = 0; j < e->width; j += 1)
        {
            if(e->etage[i][j] == 0){
                printf("  ");
            }else{
                if(e->etage[i][j] == -1){
                    printf("S");
                }else if (e->etage[i][j] == -2){
                    printf("I");
                }else if(e->etage[i][j] == -3){
                    printf("B");
                }else if(e->etage[i][j] == -4){
                    printf("I");
                }else{
                    printf("%d", e->etage[i][j]);
                }
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Id des salles de cette étage: ");
    for(int i =0; i <14;i+=1){
        printf("%d ",e->Idsalles[i]);
    }
    printf("\n");
}

void freeEtage(Etage *e)
{
    free(e->etage);
    free(e);
}

void placerSalles(Etage* e){
    int a=ROWS/2;
    int b=COLS/2;
    //0 = Haut; 1 = Droite; 2 = Bas; 3 = Gauche
    e->etage[a][b] = e->Idsalles[10];    // On place la premiere salle au centre de l'étage sa sera le spawner '0'
    srand(time(NULL));
    int i = 0;
    while(i<14){
        int dir  = randomDirections();
        if(i==10){
            i+=1;
            continue;
        }

        if(dir==0){ // On se déplace en haut
            a = a-1;    //On se déplace
            if(e->etage[a][b] == 0 && a > 0){
                e->etage[a][b] = e->Idsalles[i];
                i+=1;
            }else{
              a = a+1;  // Sionon on revien a la derniere case connu
            }
        }else if(dir==1){   // On se déplace à droite
            b=b+1;
            if(e->etage[a][b] == 0 && b < e->width){
                e->etage[a][b] = e->Idsalles[i];
                i+=1;
            }else{
                b = b-1;
            }
        }else if(dir==2){ // On se déplace en bas
            a = a+1;
            if(e->etage[a][b] == 0 && a < e->height){
                e->etage[a][b] = e->Idsalles[i];
                i+=1;
            }else{
                a = a-1;
            }
        }else if(dir==3){ // On se déplace à gauche
            b = b-1;
            if(e->etage[a][b] == 0 && b > 0){
                e->etage[a][b] = e->Idsalles[i];
                i+=1;
            }else{
                b = b+1;
            }
        }
    }
}

int randomDirections(){
    int i = 0;
    int id = rand() % 4; // Remplacé 10 par le nbrSalles
    char * sortie = "";
    if(id==0){
        sortie="Haut";
    }else if (id==1)
    {
        sortie="Droite";
    }else if (id==2)
    {
        sortie="Bas";
    }else if (id==3)
    {
        sortie="Gauche";
    }
    //printf("Position: %s\n",sortie);
    return id;
}

void randomMonster(Piece* p){

}