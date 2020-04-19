#ifndef glarr_H
#define glarr_H

//Global Arrays
//The following two arrays need to be in sync for proper results
static char *keywords[] = {"class", "const", "var", "read", "write", "{", "}", ",", ";", "=", "-", "+", "/", "*"};
static char *label[] = {"~CLASS", "~CONST", "~VAR", "~READ", "~WRITE", ">lcb", ">rcb", ">comma", ">semicolon",
			">assign", ">minus", ">plus", ">divi", ">mul", "$string", "$int", "?UNKOWN"};
enum label_codes { sClass, sConst, sVar, sRead, sWrite, sLcb, sRcb, sComma, sSemicolon, sAssgin,
			sMinus, sPlus, sDivi, sMul, sString, sInt, sUnknown};
static char *segment[] = {"CS", "DS"};

#endif
