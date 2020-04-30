/* Author:      Hamza Syed      */
/* COSC4317:    Compilers       */
/* Part-1:      Lexical         */

#include "nancy.h"
/*
int main()
{
	NancyDriver();

	return 0;
}
*/
void NancyDriver(char* prsFile)
{
//	char *prsFile = "pe1.licp";
//	char *prsFile = "pgm1.lic";

	char *prsCode = PrsReader(prsFile);
	struct Node *tokNode = NULL;
	struct Node *symNode = NULL;
	struct Node *quadNode = NULL;

	getNodes(prsCode, &tokNode, &symNode, &quadNode);

	normalize(&tokNode);
	normalize(&symNode);
	normalize(&quadNode);

	writeAsm(prsFile, symNode, quadNode);

//debug	printLisa(tokNode, printToken);
//debug	printLisa(symNode, printSymbol);
//debug	printLisa(quadNode, printQuad);
}

char *PrsReader(char *fileName)
{
	char ext[] = ".licp";
	char *verify = strstr(fileName, ext);
	if(!verify)
	{
		printf("INVALID OR MISSING INTERMIDATE PARSE FILE\nexit code(N0)\n");
		exit(0);
	}

        char *buffer=NULL;
        int strSize,readSize;
        FILE *file = fopen(fileName,"r");

        if(file)
        {
                fseek(file,0,SEEK_END);
                strSize = ftell(file);
                rewind(file);

                buffer = (char*)malloc(sizeof(char)*(strSize+1));
                readSize = fread(buffer,sizeof(char),strSize,file);
                buffer[strSize]='\0';

                if(strSize != readSize)
                {
                        free(buffer);
                        buffer=NULL;
                }

                fclose(file);
        }

        return buffer;
}

void getNodes(char *prsCode, struct Node** tokenChain,
		struct Node** symbolChain, struct Node** quadChain)
{
	//TOKENIZER COMPONENT
	char delimit[] = " \t\r\n\v\f";
	char *word = strtok(prsCode, delimit);
		//TOKEN COMPONENT
		char lit[32] = "";
		int label = 0;
		//SYMBOL COMPONENT
		int val = 0;
		int adrs = 0;
		char seg[2] = "";

	//FLAGS
	bool tokens = true;
	bool symbols = false;
	bool quads = false;

	while(tokens && word)
	{
		struct tokenClass *tok =
			(struct tokenClass*)calloc(1,sizeof(struct tokenClass));

		word = strtok(NULL, delimit);
		if(word && strcmp(word,"<end>")==0)
		{
			tokens = false;
			word = strtok(NULL, delimit);
			symbols = true;
			break;
		}

		strcpy((*tok).lit,word);
		(*tok).label = atoi(strtok(NULL, delimit));

		push(tokenChain, tok, sizeof(struct tokenClass));
	}

	while(symbols && word)
	{
		struct symbol *sym = (struct symbol*)calloc(1,sizeof(struct symbol));
		sym->token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

		word = strtok(NULL, delimit);
		if(word && strcmp(word,"<end>")==0)
		{
			symbols = false;
			word = strtok(NULL, delimit);
/*			while(strcmp(word,"<end>")!=0)
			{
				printf("%s\n", word);
				word = strtok(NULL,delimit);
			}
*/
			quads = true;
			break;
		}

		strcpy((*sym).token->lit, word);
		(*sym).token->label = atoi(strtok(NULL, delimit));
		(*sym).val = atoi(strtok(NULL, delimit));
		(*sym).adrs = atoi(strtok(NULL, delimit));
		strcpy((*sym).seg, strtok(NULL, delimit));

		push(symbolChain, sym, sizeof(struct symbol));
	}

	while(quads && word)
	{
		struct Quads *quadTok = (struct Quads*)calloc(1,sizeof(struct Quads));
		quadTok->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		quadTok->polyOne = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		quadTok->polyTwo = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		quadTok->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

		word = strtok(NULL, delimit);
		if(word && strcmp(word,"<end>")==0)
		{
			quads = false;
			break;
		}

		strcpy((*quadTok).op->lit, word);
		(*quadTok).op->label = getLabel_nancy((*quadTok).op->lit);

		label = (*quadTok).op->label;
		printf("%s", keywords[label]);

		if(label != sRead && label != sWrite && !(label >= sIf && label <= sEndif))
		{
			strcpy((*quadTok).polyOne->lit, strtok(NULL, delimit));
			(*quadTok).polyOne->label = sString;

			if(label != sAssgin)
			{
				strcpy((*quadTok).polyTwo->lit, strtok(NULL, delimit));
				(*quadTok).polyTwo->label = sString;
			}
		}

//Backup	strcpy((*quadTok).result->lit, strtok(NULL, delimit));
		if(!(label >= sJl && label <= sJe))
		{
			sprintf((*quadTok).result->lit, "%s", strtok(NULL, delimit));
			(*quadTok).result->label = sString;
		}

		push(quadChain, quadTok, sizeof(struct Quads));
	}

}

int getLabel_nancy(char* lit)
{
	if(strcmp(lit, "=")==0)
		return sAssgin;
	if(strcmp(lit, "*")==0)
		return sMul;
	if(strcmp(lit, "/")==0)
		return sDivi;
	if(strcmp(lit, "+")==0)
		return sPlus;
	if(strcmp(lit, "-")==0)
		return sMinus;
	if(strcmp(lit, "==")==0)
		return sJe;
	if(strcmp(lit, ">=")==0)
		return sJge;
	if(strcmp(lit, "<=")==0)
		return sJle;
	if(strcmp(lit, ">")==0)
		return sJg;
	if(strcmp(lit, "<")==0)
		return sJle;
	if(strcmp(lit, "Read")==0)
		return sRead;
	if(strcmp(lit, "Write")==0)
		return sWrite;
	if(strcmp(lit, "If")==0)
		return sIf;
	if(strcmp(lit, "Then")==0)
		return sThen;
	if(strcmp(lit, "Else")==0)
		return sElse;
	if(strcmp(lit, "Endif")==0)
		return sEndif;

	return sUnknown;
}

void writeAsm(char* file, struct Node* symbolChain, struct Node* quadChain)
{
	const int buffer = 999;

	char asmFile[32] = "";
	char filing[32] = "";
	sprintf(filing, "%s", file);
	sprintf(asmFile, "%s", strtok(filing, "."));
	strcat(asmFile, ".asm");

	initAsm(asmFile);

	char asmData[buffer], asmBss[buffer], dataTemp[64];
	sprintf(asmData, "section .data\n");
	sprintf(asmBss, "section .bss\n");

	struct symbol *sym = (struct symbol*)calloc(1,sizeof(struct symbol));
	sym->token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	while(symbolChain)
	{
		getSymbolInfo(symbolChain->data, &sym);
		printSymbol(symbolChain->data);

		if(strcmp(sym->seg, "DS")==0)
		{
			if(sym->token->label == sConst)
			{
				sprintf(dataTemp, "\t%s\tDW\t%d\n", sym->token->lit, sym->val);
				strcat(asmData, dataTemp);
			}
			else if(sym->token->label == sVar)
			{
				sprintf(dataTemp, "\t%s\tRESW\t1\n", sym->token->lit);
				strcat(asmBss, dataTemp);
			}
		}

		symbolChain = symbolChain->next;
	}

	appendAsm(asmFile, asmData);
	appendAsm(asmFile, asmBss);
	appendAsm(asmFile, "section .txt");

	char codeData[buffer];
	sprintf(codeData, "_start:");
	appendAsm(asmFile, codeData);

	while(quadChain)
	{
		sprintf(codeData, "%s", getCode(quadChain->data));
		appendAsm(asmFile, codeData);
		quadChain = quadChain->next;
	}

	endAsm(asmFile);
}

void initAsm(char* asmFile)
{
	FILE *file = fopen(asmFile, "w");
	if(file == NULL)
		printf("FILE WRITER CRASHED IN NANCY\n exit(N1)\n");

	fprintf(file, "%%include \"IOSR.asm\"\nglobal _start\n\n\n");
	fclose(file);
}

void appendAsm(char* asmFile, char *data)
{
	FILE *file = fopen(asmFile, "a");
	if(file == NULL)
		printf("FILE WRITER CRASHED IN NANCY\n exit(N2)\n");

	fprintf(file, "%s\n\n", data);
	fclose(file);
}

void endAsm(char* asmFile)
{
	FILE *file = fopen(asmFile, "a");
	if(file == NULL)
		printf("FILE WRITER CRASHED IN NANCY\n exit(N3)\n");

	fprintf(file, "\tcall fini\n");
	fclose(file);

	char fileName[32] = "";
	char pgmName[32] = "";
	sprintf(fileName, "%s", asmFile);
	sprintf(pgmName, "%s", strtok(asmFile, "."));

	char cmd1[64] = "";
	char cmd2[64] = "";
	char cmd3[64] = "";
	char cmd4[64] = "";

	sprintf(cmd1, "nasm -felf64 -o IOSR.o IOSR.asm");
	sprintf(cmd2, "nasm -felf64 -o %s.o %s", pgmName, fileName);
	sprintf(cmd3, "ld -o %s %s.o IOSR.o", pgmName, pgmName);
	sprintf(cmd4, "rm *.o");

	system(cmd1);
	system(cmd2);
	system(cmd3);
	system(cmd4);
}
