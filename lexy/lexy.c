/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/
#include "lexy.h"

int main()
{
	char javaZero[] = "pgm1.javaz";
	char *javCode = FileReader(javaZero);
	char *javClass = classify(javCode);
	printf("%s",javClass);

	return 0;
}

char *FileReader(char *fileName)
{
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

char *classify(char *jav)
{
	//FSM Component
	enum state_codes cur_state = ENTRY_STATE;
	enum ret_codes rc;
	int (* state_fun)(char);
	//End FSM Component

	int atom_pt = 0;
	char atom = jav[0];
	char token[32] = "";

	for(;;){
		atom = jav[atom_pt];

		//FSM Component
		state_fun = state[cur_state];
		rc = state_fun(atom);
		if(EXIT_STATE == cur_state)
			break;
		cur_state = lookup_transitions(cur_state, rc);
		//End FSM Component

		atom_pt++;
		while(isspace(jav[atom_pt]))
			atom_pt++;
		append(token,atom);
		if(tokenize==true)
		{
			printf("\n\nToken: %s\n\n", token);
			token[0] = '\0';
			tokenize = false;
		}
	}

	return jav;
}

int entry_state(char a)
{
	printf("entered: %c\n", a);
	if(isalpha(a))
		return alpha;
	if(isdigit(a))
		return num;
	else if(a=='{')
	{
		tokenize=true;
		return lb;
	}
	return end;
}
int letter_state(char a)
{
	if(isalpha(a)){
		printf("letter: %c\n", a);
		return alpha;
	}
	return entry;
}
int digit_state(char a)
{
	if(isdigit(a)){
		printf("digit: %c\n", a);
		return num;
	}
	printf("num not caught\n");
	return entry;
}
int symbol_state(char a)
{
	if(isalpha(a))
		return alpha;
	else if(isdigit(a))
		return num;
	return entry;
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
