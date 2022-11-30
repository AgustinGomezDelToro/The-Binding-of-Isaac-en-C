/*
*  Filename : pieceMain.c
*
*  Made by : MALLIA Jonathan
*
*  Description : Point d'entrée de la partie 1
*/

#include "../H/piece.h"
#include "../H/menu.h"
#include <stdlib.h>
#include <stdio.h>

void pieceMain(){
    char choice = '0';
    char *file = "ressources/piece.rtbob";
    system("clear");
    while(choice != -1) {
        do {
            //system("clear");
            printf("!!! ATTENTION CE PPROGRAMME EST SENSIBLE A LA CASSE !!!\n\n");
            printf("1 - Créer une pièce\n");
            printf("2 - Modifier une pièce\n");
            printf("3 - Supprimer une pièce\n");
            printf("4 - Afficher toutes les pièce\n");
            printf("5 - Quitter\n");
            printf("Faites votre choix et appuyé sur entrer : ");
            getchar();
            scanf("%c", &choice);
        } while (choice <= '0' || choice > '5');
        int id = 0;
        switch (choice) {
            case '1': 
                system("clear");
                Piece *a = createPiece();
                addPieceToFile(a, file);
                freePiece(a);
                break;
            case '2':
                system("clear");
                printAllPieces();
                printf("Entrer l'id de la salle a modifier : ");
                scanf("%d", &id);
                modifyPiece(id);
                break;
            case '3':
                system("clear");
                id = 0;
                printAllPieces();
                printf("Entrer l'id de la salle a supprimer : ");
                scanf("%d", &id);
                deletePiece(id);
                break;
            case '4':
                system("clear");
                printAllPieces();
                printf("\n\n");
                break;
            case '5':
                system("clear");
                choice = -1;
                break;
        }
    }
}