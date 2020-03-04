/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/


//Include Sector
//Header Files
#include "syslib.h"
#include "struct.h"
#include "lisa.h"

//
//Function Init Sector
char *FileReader(char *fileName);
char *classify(char *jav);

void append(char*,char);
int getLabel(char*);

//FSM Functions
enum ret_codes assort(char);
int entry_state(char);
int letter_state(char);
int digit_state(char);
int symbol_state(char);
int token_state(char);
int exit_state(char);
//END FSM Functions


//
//Global Arrays
//The following two arrays need to be in sync for proper results
static char *keywords[] = {"class", "const", "var", "{", "}", ",", ";", "=", "+", "-", "*", "/"};
static char *label[] = {"~CLASS", "~CONST", "~VAR", ">lcb", ">rcb", ">comma", ">semicolon",
			">assign", ">plus", ">minus", ">mul", ">divi", "$string", "$int", "?UNKOWN"};
static char *segment[] = {"CS", "DS"};


	//
	//FSM Symbol Components
	int (* symState[])(int) = { new_sym, key_sym, op_sym, alpha_sym, num_sym, error_sym, end_sym}
	enum sym_codes { newsym


//
//FSM Tokenizer Components
//The following three arrays need to be in sync for proper results
int (* state[])(char) = { entry_state, letter_state, digit_state, symbol_state, token_state, exit_state};
enum state_codes { entry, letter, digit, symbol, token, end};
const char* get_state[] = { "entry", "letter", "digit", "symbol", "token", "end"};

//The following two arrays need to be in sync for proper results
enum ret_codes { alpha, num, lcb, rcb, comma, semicolon, assign, plus, sub, mul, divi, space};
const char* get_ret[] = { "alpha", "num", "lcb", "rcb", "comma", "semicolon", "assign", "plus", "sub", "mul", "divi", "space"};
struct transition {
	enum state_codes src_state;
	enum ret_codes ret_codes;
	enum state_codes dst_state;
};

struct transition state_transition[] = {

	//entry states
	{entry,		alpha,		letter},
	{entry, 	num,		digit},
	{entry, 	lcb,		symbol},
	{entry, 	rcb,		symbol},
	{entry, 	comma,		symbol},
	{entry, 	semicolon,	symbol},
	{entry, 	assign,		symbol},
	{entry, 	plus,		symbol},
	{entry, 	sub,		symbol},
	{entry, 	mul,		symbol},
	{entry, 	divi,		symbol},
	{entry,		space,		symbol},

	//letter states
	{letter,	alpha,		letter},
	{letter,	num,		letter},
	{letter, 	lcb,		token},
	{letter, 	rcb,		token},
	{letter, 	comma,		token},
	{letter, 	semicolon,	token},
	{letter, 	assign,		token},
	{letter, 	plus,		token},
	{letter, 	sub,		token},
	{letter, 	mul,		token},
	{letter, 	divi,		token},
	{letter,	space,		token},

	//digit states
	{digit, 	num, 		digit},
	{digit, 	lcb,		token},
	{digit, 	rcb,		token},
	{digit, 	comma,		token},
	{digit, 	semicolon,	token},
	{digit, 	assign,		token},
	{digit, 	plus,		token},
	{digit, 	sub,		token},
	{digit, 	mul,		token},
	{digit, 	divi,		token},
	{digit,		space,		token},

	//symbol states
	{symbol,	alpha,		letter},
	{symbol,	num,		digit},
	{symbol, 	lcb,		token},
	{symbol, 	rcb,		token},
	{symbol, 	comma,		token},
	{symbol, 	semicolon,	token},
	{symbol, 	assign,		token},
	{symbol, 	plus,		token},
	{symbol, 	sub,		token},
	{symbol, 	mul,		token},
	{symbol, 	divi,		token},
	{symbol,	space,		token},

	//token states
	{token,		alpha,		letter},
	{token,		num,		digit},
	{token, 	lcb,		entry},
	{token, 	rcb,		symbol},
	{token, 	comma,		symbol},
	{token, 	semicolon,	symbol},
	{token, 	assign,		symbol},
	{token, 	plus,		symbol},
	{token, 	sub,		symbol},
	{token, 	mul,		symbol},
	{token, 	divi,		symbol},
	{token,		space,		entry}};


#define EXIT_STATE end
#define ENTRY_STATE entry

enum state_codes lookup_transitions(enum state_codes, enum ret_codes);
//END FSM Components


//
//Flags
bool tokenize = false;
