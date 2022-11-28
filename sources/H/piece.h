/*
*  Filename : piece.h
*
*  Made by : MALLIA Jonathan
*
*  Description : "Interface"
*/

#ifndef PIECE_H
#define PIECE_H

struct Piece {
    char** piece;
    int id;
    int width;
    int height;
};

typedef struct Piece Piece;

Piece* createPiece();           //FAIT

void printPiece(Piece* P,int mode);      // FAIT

void modifyPiece(int id);       // A Revoir

void freePiece(Piece* p);       // FAIT

void addPieceToFile(Piece* p, char* file);  // FAIT

void deletePiece(int id);       // FAIT

void printAllPieces();          //FAIT

Piece* getAllPieces(); //FAIT

int getNumberPieces();  //FAIT

int testeChaine(char* nom1, char* nom2);    //FAIT

int placeAlphabet(char lettre);

void result(char* result);

#endif