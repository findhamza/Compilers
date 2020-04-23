#ifndef OPHELIA_H
#define OPHELIA_H
//Generic Linked List
#include "../lexy/syslib.h"
#include "../lexy/struct.h"
#include "../lexy/lisa.h"
#include "../lexy/glarr.h"

char* getCode(void*);
char* readCode(char*);
char* writeCode(char*);
char* assignCode(char*, char*);
char* mulCode(char*, char*, char*);
char* diviCode(char*, char*, char*);
char* plusCode(char*, char*, char*);
char* minusCode(char*, char*, char*);

char* NumToLit(char*);
#endif
