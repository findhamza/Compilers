#ifndef LISA_H
#define LISA_H
//Generic Linked List
#include "syslib.h"
#include "struct.h"


//Functions
void push(struct Node**, void*, size_t);
void *pop(struct Node**,size_t);
bool is_empty(struct Node**);
void pleaseEmpty(struct Node**);
void printLisa(struct Node*, void(*)(void *));
void printClass(void*);
void printSymbol(void*);
void printToken(void*);
void printQuad(void*);
void getSymbolInfo(void*, struct symbol**);
void getTokenInfo(void*, struct tokenClass**);
void getQuadInfo(void*, struct Quads**);
void normalize(struct Node**);

#endif
