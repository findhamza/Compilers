//Generic Linked List
#include "syslib.h"
#include "struct.h"


//Functions
void push(struct Node**, void*, size_t);
void printLisa(struct Node*, void(*)(void *));
void printClass(void*);
void printSymbol(void*);
void printToken(void*);
void getSymbolInfo(void*, struct symbol**);
void getTokenInfo(void*, struct tokenClass**);
void normalize(struct Node**);
