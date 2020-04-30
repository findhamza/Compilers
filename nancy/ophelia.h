#ifndef OPHELIA_H
#define OPHELIA_H
//Generic Linked List
#include "../lexy/syslib.h"
#include "../lexy/struct.h"
#include "../lexy/lisa.h"
#include "../lexy/glarr.h"

char* getCode(void*, int*);
char* readCode(char*);
char* writeCode(char*);

char* elseCode(int*);
char* endifCode(int*);

char* assignCode(char*, char*);
char* mulCode(char*, char*, char*);
char* diviCode(char*, char*, char*);
char* plusCode(char*, char*, char*);
char* minusCode(char*, char*, char*);

char* jeCode(char*, char*, int*);
char* jgeCode(char*, char*, int*);
char* jleCode(char*, char*, int*);
char* jgCode(char*, char*, int*);
char* jlCode(char*, char*, int*);

char* NumToLit(char*);
#endif
