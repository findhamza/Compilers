#ifndef glarr_H
#define glarr_H

//Global Arrays
//The following two arrays need to be in sync for proper results
static char *keywords[] = {"class", "const", "var", "read", "write", "if", "then", "else", "endif",
				"{", "}", ",", ";","<", ">", "<=", ">=", "==",
				"=", "-", "+", "/", "*"};
static char *label[] = {"~CLASS", "~CONST", "~VAR", "~READ", "~WRITE", "~IF", "~THEN", "~ELSE",
			"~ENDIF", ">lcb", ">rcb", ">comma", ">semicolon",">jl", "jg", "jle", "jge",
			"je", ">assign", ">minus", ">plus", ">divi", ">mul", "$string", "$int",
			"?UNKOWN"};
enum label_codes { sClass, sConst, sVar, sRead, sWrite, sIf, sThen, sElse, sEndif, sLcb, sRcb,
			sComma, sSemicolon, sJl, sJg, sJle, sJge, sJe, sAssgin, sMinus, sPlus,
			sDivi, sMul, sString, sInt, sUnknown};
static char *segment[] = {"CS", "DS"};

#endif
