/* Author:      Hamza Syed      */
/* COSC4317:    Compilers       */
/* Part-1:      Lexical         */

#include "paris.h"

int main()
{
	char lexFile[] = "pe1.lic";
	char *lexCode = LexReader(lexFile);

	parser(lexCode);
}

char *LexReader(char *fileName)
{
	char ext[] = ".lic";
	char *verify = strstr(fileName, ext);
	if(!verify)
	{
		printf("INVALID INTERMIDATE LEX FILE\nexit code(P0)\n");
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

void parser(char *lexCode)
{
	//FSM COMPONENT
	enum prs_codes cur_state = newprs;
	enum prs_codes old_state = cur_state;
	enum label_codes lc;
	int (* prs_fun)(char* tok, int lab, struct Quads** quad,
			struct Node** pds, struct Node** quadNode);
	//END FSM COMPONENT

	//TOKEN COMPONENT
	char delimit[] = " \t\r\n\v\f";
	char *lexTok = strtok(lexCode, delimit);
	char tok[32] = "";
	int lab = 0;

	if(strcmp(lexTok,"<token>")!=0)
	{
		printf("INVALID INTERMIDATE LEX FILE\nexit code(P0)\n");
		exit(0);
	}

	printf("HELLO\n");
	lexTok = strtok(NULL,delimit);
	//END TOKEN COMPONENT

	//PDA STACK COMPONENTS
	struct Node *pds = NULL;
	struct Node *quadNode = NULL;
	struct Quads *quad = (struct Quads*)calloc(1,sizeof(struct Quads));
	quad->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyOne = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyTwo = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	//END PDA STACK COMPONENTS

	while(strcmp(lexTok,"<symbol>"))
	{
		strcpy(tok, lexTok);
		lab = atoi(strtok(NULL, delimit));
//		printf("%s\t%d\n", tok, lab);

		//FSM COMPONENT
		prs_fun = prsState[cur_state];
		lc = prs_fun(tok, lab, &quad, &pds, &quadNode);
		if(endprs == cur_state)
			break;
		old_state = cur_state;
		cur_state = lookup_prsTransitions(cur_state, lc);
		//END FSM COMPONENT

		lexTok = strtok(NULL, delimit);
	}

	printLisa(quadNode, printQuad);
}

enum prs_codes lookup_prsTransitions(enum prs_codes cur_state, enum label_codes lc)
{
	int table_size = sizeof prs_state_transition / sizeof prs_state_transition[0];
	for(int i=0; i<table_size; i++)
		if(prs_state_transition[i].prs_src==cur_state && prs_state_transition[i].label_ret==lc)
			return prs_state_transition[i].prs_dst;
	return endprs;
}

int new_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("NEW:\t%s\t%d\n", tok, lab);

	(*quad)->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	if(lab == sRead || lab == sWrite)
	{
		strncpy((*quad)->op->lit, tok, sizeof(tok));
		(*quad)->op->label = lab;
	}
/**
	if(lab = sString)
	{
		struct tokenClass *token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		sprintf(token->lit, "%s", tok);
		token->label = lab;
		push(pds, token, sizeof(struct tokenClass));
	}
**/
	return lab;
}

int key_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("KEY:\t%s\t%d\n", tok, lab);
	return lab;
}

int io_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("IO:\t%s\t%d\n", tok, lab);

	(*quad)->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	if((*quad)->op->label == sRead || (*quad)->op->label == sWrite)
	{
		strncpy((*quad)->result->lit, tok, sizeof(tok));
		(*quad)->result->label = lab;
		push(quadNode, *quad, sizeof(struct Quads));
	}

	return lab;
}

int op_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("OP:\t%s\t%d\n", tok, lab);
	return lab;
}

int alpha_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("ALP:\t%s\t%d\n", tok, lab);
	return lab;
}
int num_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("NUM:\t%s\t%d\n", tok, lab);
/**
	if(lab >= sMinus && lab <= sAssgin && !is_empty(pds))
	{
		struct tokenClass *token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		sprintf(token->lit, "%s", tok);
		token->label = lab;
		push(pds, token, sizeof(struct tokenClass));
	}
**/
	return lab;
}

int error_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("ERR:\t%s\t%d\n", tok, lab);
	return lab;
}

int end_prs(char *tok, int lab, struct Quads** quad, struct Node** pds, struct Node** quadNode)
{
		printf("END:\t%s\t%d\n", tok, lab);
	return lab;
}
