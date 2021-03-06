
/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/
#include "lexy.h"

bool tokenize = false;

/*
int main()
{
	char javaZero[] = "pgm1.javaz";
//	char javaZero[] = "pe1.javaz";
	struct Node *tokNode = NULL;
	struct Node *symNode = NULL;

	char *javCode = FileReader(javaZero);
	printf("\n\n");
	tokenizer(javCode, &tokNode);
	printf("\n\n");
	symbolizer(tokNode, &symNode);
//	char *javClass = tokenizer(javCode);

	printLisa(tokNode, printToken);
	printLisa(symNode, printSymbol);
	printf("%s",javCode);

	FileWriter(javaZero, tokNode, symNode);

	return 0;
}
*/

void LexyDriver(char *javaZero)
{
	struct Node *tokNode = NULL;
	struct Node *symNode = NULL;

	char *javCode = FileReader(javaZero);
	tokenizer(javCode, &tokNode);
	symbolizer(tokNode, &symNode);

	printLisa(tokNode, printToken);
	printLisa(symNode, printSymbol);
	printf("%s", javCode);

	FileWriter(javaZero, tokNode, symNode);
}

char *FileReader(char *fileName)
{
        char ext[] = ".javaz";
        char *verify = strstr(fileName, ext);
        if(!verify)
        {
                printf("INVALID JAVA ZERO FILE\nexit code(L0)\n");
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

void FileWriter(char *inFile, struct Node* tok, struct Node* sym)
{
	char ext[] = ".javaz";
	char *outFile = strstr(inFile, ext);

	const char *var = "<token>";
	const char *symbol = "<symbol>";
	const char *end = "<end>";

	struct tokenClass* tokDat = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	struct symbol* symDat = (struct symbol*)calloc(1,sizeof(struct symbol));

	if(outFile)
	{
		strcpy(outFile, ".lic");
//debug		printf("\n1%s\n", inFile);
	}
	else
	{
		strcat(inFile, ".lic");
//debug		printf("\n2%s\n", inFile);
	}
	outFile = (char*)calloc(1,sizeof(inFile));
	strncpy(outFile, inFile, sizeof(inFile));

	FILE *file = fopen(outFile, "w");
	if(file == NULL)
		printf("FILE WRITER CRASHED IN LEXY");

//debug	printf("\nHELLO\n");
	fprintf(file, "%s\n", var);
	while(tok != NULL)
	{
		getTokenInfo(tok->data, &tokDat);
//debug		printf("%s\t%d\n", tokDat->lit, tokDat->label);
		fprintf(file, "%s\t%d\n", tokDat->lit, tokDat->label);
		free(tok->data);
		tok = tok->next;
	}
	fprintf(file, "%s\n", end);
	fprintf(file, "%s\n", symbol);
	while(sym != NULL)
	{
		getSymbolInfo(sym->data, &symDat);
		fprintf(file, "%s\t%d\t%d\t%d\t%s\n", symDat->token->lit, symDat->token->label,
			symDat->val, symDat->adrs, symDat->seg);
		free(sym->data);
		sym = sym->next;
	}

	fprintf(file, "%s\n", end);
	fclose(file);
	free(outFile);
	free(tokDat); free(symDat);
}

void tokenizer(char *jav, struct Node** tokenChain)
{
	//FSM Component
	enum state_codes cur_state = ENTRY_STATE;
	enum state_codes old_state = cur_state;
	enum ret_codes rc;
	int (* state_fun)(char);
	//End FSM Component

	//Token Componenet
	int atom_pt = 0;
	char atom = jav[0];
	char token[32] = "";

		//Token Storage Component
		unsigned tokSize = sizeof(struct tokenClass);
		struct Node *tokenNode = NULL;
		struct tokenClass *tok = (struct tokenClass*)malloc(sizeof(struct tokenClass));
	//End Token Component


		//Flags

	//End Symbol Component

	for(;;){
		atom = jav[atom_pt];
		if(atom=='\0')
			break;

		//FSM Component
		state_fun = state[cur_state];
		rc = state_fun(atom);
		if(EXIT_STATE == cur_state)
			break;
		old_state = cur_state;
		cur_state = lookup_transitions(cur_state, rc);
		//End FSM Component

//debug		sleep(1);
		printf("\nAtom: %c ; O'State; %s ; Ret: %s ; State: %s",atom,get_state[old_state],get_ret[rc],get_state[cur_state]);

//legacy	if(strcmp(get_state[cur_state],"token")!=0)
			atom_pt++;

		if((tokenize==true || strcmp(get_state[cur_state],"token")==0) && strcmp(token,"")!=0)
		{
			int label_pos = getLabel(token);

			//Token Storage
			strncpy(tok->lit, token, sizeof(tok->lit));
			(*tok).label = label_pos;
			push(&tokenNode, tok, tokSize);
			//End Token Storage

			printf("\nToken: %s\t%s\n", tok->lit, label[tok->label]);
			token[0] = '\0';
			tokenize = false;
		}
		if(tokenize==true)
			tokenize=false;

		if(!isspace(atom) && !iscntrl(atom))
			append(token,atom);

	}

	normalize(&tokenNode);
//	printLisa(tokenNode, printToken);

	(*tokenChain) = tokenNode;
}

enum ret_codes assort(char a)
{
	if(isalpha(a))
		return alpha;
	else if(isdigit(a))
		return num;
	else if(a=='{')
		return lcb;
	else if(a=='}')
		return rcb;
	else if(a==',')
		return comma;
	else if(a==';')
		return semicolon;
	else if(a=='=')
		return assign;
	else if(a=='+')
		return plus;
	else if(a=='-')
		return sub;
	else if(a=='*')
		return mul;
	else if(a=='/')
		return divi;
	else if(a=='>')
		return gt;
	else if(a=='<')
		return lt;
	else if(isspace(a))
		return space;

	return end;
}

int entry_state(char a)
{
	return assort(a);
}
int letter_state(char a)
{
	return assort(a);
}
int digit_state(char a)
{
	return assort(a);
}
int symbol_state(char a)
{
	return assort(a);
}
int token_state(char a)
{
	tokenize = true;
	return assort(a);
}
int exit_state(char a)
{
	printf("bye: %c\n", a);
}

enum state_codes lookup_transitions(enum state_codes cur_state, enum ret_codes rc)
{
	int table_size = sizeof state_transition / sizeof state_transition[0];
	for(int i=0; i<table_size; i++)
		if(state_transition[i].src_state==cur_state && state_transition[i].ret_codes==rc)
			return state_transition[i].dst_state;
	return end;
}

void append(char* s, char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}


int getLabel(char* token)
{
	int arr_size = sizeof keywords / sizeof *(keywords + 0);
	size_t i;

	for(i=0; i<arr_size; i++)
	{
		if(strcasecmp(*(keywords +i),token)==0)
			return i;
	}

	if(isalpha(token[0]))
		return arr_size;
	else if(isdigit(token[0]))
		return arr_size+1;

	return arr_size+2;
}

//Symbol Functions
void symbolizer(struct Node* token, struct Node** symbolChain)
{
	//FSM Component
	enum sym_codes cur_state = newsym;
	enum sym_codes old_state = cur_state;
	enum label_codes lc;
	int (* sym_fun)(struct tokenClass*, struct symbol**, struct Node**);
	//End FSM Component

//		struct tokenClass* tokenInfo = (struct tokenClass*)malloc(sizeof(struct tokenClass));
		struct tokenClass* tokenInfo = NULL;

//	tokenhead
		struct Node* tokHead = token;

	//Symbol Table Component
	unsigned symSize = sizeof(struct symbol);
	struct Node *symbolNode = NULL;
	struct symbol *sym = (struct symbol*)malloc(sizeof(struct symbol));
	sym->token = (struct tokenClass*)malloc(sizeof(struct tokenClass));
	strncpy(sym->token->lit, "", sizeof(sym->token->lit));
	sym->token->label = -1;
	sym->val = 0;
	sym->adrs = 0;
	strncpy(sym->seg, "", sizeof(sym->seg));

	for(;;){
		getTokenInfo(token->data, &tokenInfo);
//Debug		printToken(tokenInfo);

		//FSM Component
		sym_fun = symState[cur_state];
		lc = sym_fun(tokenInfo, &sym, &symbolNode);
		if(endsym == cur_state)
			break;
		old_state = cur_state;
		cur_state = lookup_symTransitions(cur_state, lc);
		//End FSM Component
//Debug		printf("STATE::\tsrc:%s\tret:%s\tdst:%s\n\n", get_symState[old_state], label[lc], get_symState[cur_state]);

		if(token->next != NULL)
			(token) = token->next;
		else
			break;
	}

	printf("\n\n");
	tempCounter(tokHead, &symbolNode);
	normalize(&symbolNode);
	adrsCounter(symbolNode);
//	printLisa(symbolNode, printSymbol);

	(*symbolChain) = symbolNode;
}

void adrsCounter(struct Node* sym)
{
	int cs = 0;
	int ds = 0;

	struct symbol* symDat = NULL;

	while(sym != NULL)
	{
		getSymbolInfo(sym->data, &symDat);

		if(strcmp(symDat->seg, "CS")==0)
		{
			symDat->adrs = cs;
			cs++;
		}
		else
		{
			symDat->adrs = ds;
			ds++;
		}

		sym = sym->next;
	}
}

void tempCounter(struct Node* tok, struct Node** sym)
{
	int max = 0;
	int counter = 0;

	struct tokenClass* tokDat = NULL;

//	normalize(&tok);

	while(tok != NULL)
	{
		getTokenInfo(tok->data, &tokDat);
//Debug		printf("TOKEN: %d\n", tokDat->label);
		switch(tokDat->label)
		{
			case sMinus: counter++;
				break;
			case sPlus: counter++;
				break;
			case sDivi: counter++;
				break;
			case sMul: counter++;
				break;
			case sAssgin: counter++;
				break;
			case sSemicolon:
				if(max<counter)
					max = counter;
				counter = 0;
				break;
		}

		tok = tok->next;
	}

//Debug	printf("\n\n%d-%d\n\n",max,counter);
	for(int i=0; i<max; i++)
	{
		struct symbol *temp = (struct symbol*)calloc(1,sizeof(struct symbol));
		temp->token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
		sprintf(temp->token->lit, "temp%d", i);
		temp->token->label = sVar;
		temp->val = 0;
		sprintf(temp->seg, "DS");

		push(sym, temp, sizeof(struct symbol));
	}

}

enum sym_codes lookup_symTransitions(enum sym_codes cur_state, enum label_codes lc)
{
	int table_size = sizeof sym_state_transition / sizeof sym_state_transition[0];
	for(int i=0; i<table_size; i++)
		if(sym_state_transition[i].sym_src==cur_state && sym_state_transition[i].label_ret==lc)
			return sym_state_transition[i].sym_dst;
	return endsym;
}

int new_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	if(strcmp((*sym)->token->lit, "\0")!=0)
	{
		unsigned symSize = sizeof(struct symbol);
		push(symNode, *sym, symSize);
		printSymbol(*sym);
//		printf("\nLIST:\n");
//		printLisa(*symNode, printSymbol);
//		printf(":END LIST:\n\n");
	}

//	free((*sym)->token);
//	free(*sym);
//	(*sym) = NULL;
	(*sym) = (struct symbol*)calloc(1,sizeof(struct symbol));
	(*sym)->token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	if(label[token->label][0] == '~')
	{
		(*sym)->token->label = token->label;
//Debug		printf("\n%s\n",label[token->label]);
	}
	if(strcasecmp(token->lit, keywords[0])==0)
		strncpy((*sym)->seg ,segment[0] , sizeof((*sym)->seg));
	else
		strncpy((*sym)->seg ,segment[1] , sizeof((*sym)->seg));


	return token->label;
}

int key_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	if(strcmp((*sym)->token->lit, "\0")!=0)
	{
		push(symNode, *sym, sizeof(struct symbol));
		printSymbol(*sym);
//		printf("\nLIST:\n");
//		printLisa(*symNode, printSymbol);
//		printf(":END LIST:\n\n");
	}

//	free((*sym)->token);
	(*sym)->token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	if(label[token->label][0] == '$')
		strncpy((*sym)->token->lit, token->lit, sizeof(token->lit));

	return token->label;
}

int io_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	return token->label;
}

int op_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	if(token->label == sInt)// || (isdigit(token->lit[0]) && !isalpha(token->lit[0])))
		(*sym)->val = atoi(token->lit);

	if(strcmp((*sym)->token->lit, "\0")==0 && isdigit(token->lit[0]))
	{
		strncpy((*sym)->token->lit, "lit", sizeof((*sym)->token->lit));
		strcat((*sym)->token->lit, token->lit);
		(*sym)->token->label = sConst;
	}

	return token->label;
}

int alpha_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	(*sym)->val = 0;

	if(token->label == sAssgin)
		(*sym)->token->label = sConst;
	else if(token->label == sComma || token->label == sSemicolon)
		(*sym)->token->label = sVar;

	return token->label;
}

int num_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	return token->label;
}

int error_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	return token->label;
}

int end_sym(struct tokenClass* token, struct symbol** sym, struct Node** symNode)
{
	return token->label;
}
