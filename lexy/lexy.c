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
	enum state_codes old_state = cur_state;
	enum ret_codes rc;
	int (* state_fun)(char);
	//End FSM Component

	//Token Componenet
	int atom_pt = 0;
	char atom = jav[0];
	char token[32] = "";
	//End Component

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
//debug		printf("\nAtom: %c ; O'State; %s ; Ret: %s ; State: %s",atom,get_state[old_state],get_ret[rc],get_state[cur_state]);

//legacy	if(strcmp(get_state[cur_state],"token")!=0)
			atom_pt++;

		if((tokenize==true || strcmp(get_state[cur_state],"token")==0) && strcmp(token,"")!=0)
		{
			int label_pos = getLabel(token);

			printf("\nToken: %s\t%s\n", token, label[label_pos]);
			token[0] = '\0';
			tokenize = false;
		}
		if(tokenize==true)
			tokenize=false;

		if(!isspace(atom) && !iscntrl(atom))
			append(token,atom);

	}

	return jav;
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
