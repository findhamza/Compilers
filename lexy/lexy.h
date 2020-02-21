/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/


//Include Sector
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//Function Init Sector
char *FileReader(char *fileName);
char *classify(char *jav);
int entry_state(char);
int letter_state(char);
int digit_state(char);
int symbol_state(char);
int exit_state(char);

void append(char*,char);

//Global Arrays
static char *keywords[] = {"class","const","var"};

//Case Functions
int (* state[])(char) = { entry_state, letter_state, digit_state, symbol_state, exit_state};
enum state_codes { entry, letter, digit, symbol, end};

enum ret_codes { alpha, num, lb, rb, comma, semicolon, assign, plus, sub, mul, divi};
struct transition {
	enum state_codes src_state;
	enum ret_codes ret_codes;
	enum state_codes dst_state;
};

struct transition state_transition[] = {
	{entry, alpha,	letter},
	{entry, num,	digit},
	{entry, lb,	symbol},
	{entry, rb,	symbol},
	{entry, comma,	symbol},
	{entry, semicolon,symbol},
	{entry, assign,	symbol},
	{entry, plus,	symbol},
	{entry, sub,	symbol},
	{entry, mul,	symbol},
	{entry, divi,	symbol},
	{letter, alpha,	letter},
	{digit, num, 	digit},
	{symbol, alpha,	letter},
	{symbol, num,	digit}};

#define EXIT_STATE end
#define ENTRY_STATE entry

enum state_codes lookup_transitions(enum state_codes, enum ret_codes);

//Flags
bool tokenize = false;
