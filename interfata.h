#ifndef INTERFATA_H_INCLUDED
#define INTERFATA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include <assert.h>
#include <stdbool.h>

#include "data.h"

typedef struct dictionar *DEX;
// typedef struct word *WORD;
typedef struct word Word;

DEX newd();
void destroyd(DEX d);

DEX adaugare(DEX, Word);
DEX actualizare(DEX, char*, char*, int);
DEX adaugareTraducere(DEX, char*, int);
DEX stergereCuvant(DEX, char*, int);

void setCuvant(DEX, char*, int);
void setParteDeVorbire(DEX, char*, int);
void setDescriere(DEX, char*, int);
void setProvenienta(DEX, char*, int);
void setSursa(DEX, char*, int);
void setAparitiiCuvant(DEX, int);
void setTraducere(DEX d, int i);

void toString(DEX);

bool isEmptyd(DEX);
bool isFull(DEX);

int cautare_cuvant(DEX, char*);
char* getCuvant(DEX, int);
char* getParteDeVorbire(DEX, int);
char* getDescriere(DEX, int);
char* getProvenienta(DEX, int);
char* getSursa(DEX, int);
char* getTraducere(DEX, int);

int getRandom(DEX);

char* data_curenta(char*);

void afisareComplet(DEX d, int i);
void cuvantulLunii(DEX);
void generare_fisier(DEX);

#endif // INTERFATA_H_INCLUDED
