/*
*  Filename : piece.c
*
*  Made by : MALLIA Jonathan
*
*  Description :
*/

#include "../H/piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_1 "ressources/piece.rtbob"
#define TEMP_FILE "ressources/temp.rtbob"

#define COLS 15
#define ROWS 9

/// \def Create a room
/// \return Un pointeur sur la piece
Piece* createPiece(){

    Piece* s = malloc(sizeof(Piece));
    s->width = COLS; // columns
    s->height = ROWS; // rows
    s->id = 1;
    s->piece = malloc(sizeof(char*) * s->height);
    //piece[ordonne][absisse]

    for(int i = 0; i < s->height; i += 1){
        s->piece[i] = malloc(sizeof(char) * s->width);
            for(int j=0; j < s->width; j +=1 ) {
                s->piece[i][j] = ' ';
                if (j == 0 || j==s->width-1 || i == 0 || i == s->height - 1) {  // On teste les bords
                    s->piece[i][j] = 'W';
                }
            }
    }
    s->piece[0][COLS/2] = 'D'; //HAUT
    s->piece[ROWS/2][COLS-1] = 'D'; //DROITE
    s->piece[ROWS-1][COLS/2] = 'D'; //BAS
    s->piece[ROWS/2][0] = 'D';//GAUCHE
    return s;
}

/// \def Affiche une salle,0 mode normale,1 mode modification
/// \param a Prend un pointeur en entrée
void printPiece(Piece* a,int mode){
    // system("clear");
    if(mode==0){
        for(int i = 0; i < a->height; i+=1){
            for(int j = 0; j < a->width; j+=1){
                printf("%c",a->piece[i][j]);
                printf(" ");
            }
            printf("\n");
        }   
    }else{
        for(int i = 0; i < a->height; i+=1){
            if(i==0){
                printf("  A B C D E F G H I J K L M O N\n");
            } 
            printf("%d ",i);
            for(int j = 0; j < a->width; j+=1){
                printf("%c",a->piece[i][j]);
                printf(" ");
            }
            printf("\n");
        }         
    }

}

/// \def Modifie une piece
void modifyPiece(int id){
    system("clear");

    FILE* f = fopen(FILE_1, "r+");
    FILE* f2 = fopen(TEMP_FILE, "w+");
    int nbrSalles=0;
    fscanf(f,"{%d}\n",&nbrSalles);
    if(id>nbrSalles){
        printf("Salle inexistante.\n");
        return;
    }
    for(int i = 0; i<nbrSalles ;i+=1){
        Piece* s = createPiece();
        fscanf(f,"[%d|%d]%d\n",&s->height, &s->width, &s->id);
        // Lire la matrice dans le fichier
        int x=0;
        int cmpt = 1;
        char c;
        //On recupere le tableau 
        for (int j = 0; j < s->height; j+=1) {  // Ligne par ligne (le curseur bouge tt seul)      
            while ((c = fgetc(f)) != '\n') {    // On lit charactere par charactere jusqua la fin de la ligne ATTENTION:Les espace sont compté
                if(cmpt%2 !=0){                 // Donc il faut esquiver les espaces du fichier
                    s->piece[j][x] = c;         // On stock le tableau en mémoire
                    x+=1;
                }
                cmpt+=1;
            }
            x=0;
            cmpt = 1;
        }
        if(s->id==id){
            printPiece(s,1);
            int xx= 0;
            char y;
            char value;

            printf("Entrer les coordonnées(0 X):");
            scanf("%d %c",&xx,&y);
            printf("Entrer la valeur:");
            getchar();
            scanf("%c",&value);

            if(y=='N'){
                y+=1;
            }else if(y=='O'){
                y-=1;
            }

            int a = placeAlphabet(y);
            s->piece[xx][a-1]= value;
            system("clear");
            printPiece(s,0);
            printf("Piece n°:%d, modifiée.\n\n",s->id);
        }
        addPieceToFile(s,TEMP_FILE);
        freePiece(s);
    }
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    fclose(f);
    fclose(f2);
}

/// \def Libere de la mémoire
/// \param p
void freePiece(Piece* p){
    free(p->piece);
    free(p);
}

/// \def Affiche toutes les pieces du fichier
void printAllPieces(){
    system("clear");
    FILE* f = fopen(FILE_1, "r");
    int nbrSalles=0;
    fscanf(f,"{%d}\n",&nbrSalles);

    for(int i = 0; i<nbrSalles ;i+=1){
        Piece* s = createPiece();
        fscanf(f,"[%d|%d]%d\n",&s->height, &s->width, &s->id);
        // Lire la matrice dans le fichier
        printf("Piece n°%d:\n",s->id);
        for (int j = 0; j < s->height; j+=1) {   // Ligne par ligne (le curseur bouge tt seul)
            char c;
            while ((c = fgetc(f)) != '\n') { // On lit charactere par charactere jusqua la fin de la ligne
                printf("%c",c);
            }
            printf("\n");
        }
        freePiece(s);
    }
    fclose(f);
}

/// \def Ajoute la nouvelle piece au fichier
/// \param p
void addPieceToFile(Piece* p, char* file){
    FILE* f  = fopen(file, "r+");

    int nbrSalles = 0;
    int id = 0;
    int test;

    if(f != NULL) {

        fseek(f,0, SEEK_END);
        if(ftell(f) == 0){  //Premier passage ici si le fichier est vide
            fprintf(f,"{%d}\n",nbrSalles += 1);

            fprintf(f,"[%d|%d]%d\n",p->height, p->width, p->id);

            for(int i = 0; i < p->height; i +=1 ){
                for(int j = 0; j < p->width; j +=1 ){
                    fprintf(f,"%c ",p->piece[i][j]);
                }
                fprintf(f,"\n");
            }
        }else{  //Si le fichier contient déja une ou plusieur pieces on rentre ici
            rewind(f);  // On remonte au début du fichier
            fscanf(f,"{%d}\n",&nbrSalles);  // On récupère le nombre de salles
            fscanf(f,"[%d|%d]%d\n",&p->height, &p->width, &id);  // On récupère le nombre de salles
            fseek(f,0,SEEK_END);    // On revient a la fin du fichier ppour ecrire la nouvelle salle

            test = testeChaine(TEMP_FILE,file);

            if(test==1){
                fprintf(f,"[%d|%d]%d\n",p->height, p->width, p->id); // On garde l'id actuelle en cas de modification

            }else{
                fprintf(f,"[%d|%d]%d\n",p->height, p->width, p->id+nbrSalles); // On met à jour l'id
            }
            
            for(int i = 0; i < p->height; i +=1 ){
                for(int j = 0; j < p->width; j +=1 ){
                    fprintf(f,"%c ",p->piece[i][j]);
                }
                fprintf(f,"\n");
            }

            fseek(f,0,SEEK_SET);    // On revient en haut du fichier
            fprintf(f,"{%d}\n",nbrSalles += 1); // Et on met à jour le nombre de salles
        }
        if(test==0){
            //printf("Piece ajoutée.\n");
            result("Piece ajoutée.");
        }
    }else{
        printf("Error. %s\n",file);
    }

    fclose(f);
}

/// \brief Supprime une salle
/// \param p 
void deletePiece(int id){
    system("clear");
    FILE* f = fopen(FILE_1, "r+");
    FILE* f2 = fopen(TEMP_FILE, "w+");
    int idCmpt = 1;

    int isDeleted = 0;

    int nbrSalles=0;
    fscanf(f,"{%d}\n",&nbrSalles);

    if(id>nbrSalles){
        printf("Salle inexistante.\n");
        return;
    }

    
    for(int i = 0; i<nbrSalles ;i+=1){
        Piece* s = createPiece();
        fscanf(f,"[%d|%d]%d\n",&s->height, &s->width, &s->id);
        // Lire la matrice dans le fichier
        int x=0;
        int cmpt = 1;
        char c;
        //On recupere le tableau 
        for (int j = 0; j < s->height; j+=1) {   // Ligne par ligne (le curseur bouge tt seul)          
            while ((c = fgetc(f)) != '\n') { // On lit charactere par charactere jusqua la fin de la ligne ATTENTION:Les espace sont compté
                if(cmpt%2 !=0){
                  // Donc il faut esquiver les espaces du fichier
                    s->piece[j][x] = c;
                    x+=1;
                }
                cmpt+=1;
            }
            x=0;
            cmpt = 1;
        }
        s->id=idCmpt;

        if(s->id!=id){ // On regarde si on pointe sur la salle a supprimer
            if(isDeleted==1){   // On verifie si on est déja passe ici
                s->id=idCmpt-1;
                idCmpt-=1;
            }
            addPieceToFile(s,TEMP_FILE);
            isDeleted=0;
        }else{
            if(id==1){  // On gere le cas si on supprime la premiere piece, on force pour que la salle suivante devienne la numéro 1
                isDeleted=1;
            }
            isDeleted = 1;  //Si on passe ici on dit quon a "supprimé" la salle
        }
        idCmpt +=1;
        freePiece(s);
    }
    result("Piece supprimé.");
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    fclose(f);
    fclose(f2);
}

/// \brief Permet de tester 2 chaine de charactere
/// \param nom1 
/// \param nom2 
/// \return 
int testeChaine(char* nom1, char* nom2){

    int cmpt = 0;
    for (int i = 0; nom1[i] !='\0'; i+=1)
    {
        if(nom1[i] == nom2[i]){
            cmpt+=1;
        }
    }
    if(strlen(nom1) == cmpt){
        return 1;
    }else{
        return 0;
    }   
}

/// \def Retourne la position d'une lettre dans l'alphabet A=0
/// \param lettre 
/// \return 
int placeAlphabet(char lettre){
    int cmptInt = 1;
    char cmptChar = 'A';
    for(cmptInt;cmptChar!=lettre;cmptChar+=1){
        cmptInt+=1;
        //printf("%d\n",cmptInt);
    }
    return cmptInt;
}

void result(char* result){
    system("clear");
    printf("%s\n\n",result);
}