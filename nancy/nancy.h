#ifndef NANCY_H
#define NANCY_H

/* Author:      Hamza Syed      */
/* COSC4317:    Compilers       */
/* Part-1:      Lexical         */


//Include Sector
//Header Files
#include "../lexy/syslib.h"
#include "../lexy/struct.h"
#include "../lexy/lisa.h"
#include "../lexy/glarr.h"
#include "ophelia.h"

//driver
void NancyDriver(char*);

//Func Init Sector
char *PrsReader(char*);
void getNodes(char*, struct Node**, struct Node**, struct Node**);
int getLabel_nancy(char*);
void writeAsm(char*, struct Node*, struct Node*);
void initAsm(char*);
void appendAsm(char*, char*);
void endAsm(char*);

#endif
