#ifndef LEXY_H
#define LEXY_H
/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/


//Include Sector
//Header Files
#include "syslib.h"
#include "struct.h"
#include "lisa.h"
#include "glarr.h"

//
//Function Init Sector
void LexyDriver(char*);
char *FileReader(char *fileName);
void FileWriter(char*, struct Node*, struct Node*);
void tokenizer(char *jav, struct Node**);
void symbolizer(struct Node*, struct Node**);

void append(char*,char);
int getLabel(char*);
void adrsCounter(struct Node*);
void tempCounter(struct Node*, struct Node**);

//FSM Tokenizer Functions
enum ret_codes assort(char);
int entry_state(char);
int letter_state(char);
int digit_state(char);
int symbol_state(char);
int token_state(char);
int exit_state(char);
//END FSM Tokenizer Functions

//FSM Symbol Functions
int new_sym(struct tokenClass*, struct symbol**, struct Node**);
int key_sym(struct tokenClass*, struct symbol**, struct Node**);
int io_sym(struct tokenClass*, struct symbol**, struct Node**);
int op_sym(struct tokenClass*, struct symbol**, struct Node**);
int alpha_sym(struct tokenClass*, struct symbol**, struct Node**);
int num_sym(struct tokenClass*, struct symbol**, struct Node**);
int error_sym(struct tokenClass*, struct symbol**, struct Node**);
int end_sym(struct tokenClass*, struct symbol**, struct Node**);
//END FSM Symbol Functions

//

	//
	//FSM Symbol Components
	static const int (* symState[])(struct tokenClass*, struct symbol**, struct Node**) = { new_sym, key_sym, io_sym, op_sym, alpha_sym, num_sym, error_sym, end_sym};
	enum sym_codes { newsym, keysym, iosym, opsym, alphasym, numsym, errorsym, endsym};
	static const char* get_symState[] = { "NewSym", "KeySym", "IoSym", "OpSym", "AlphaSym", "NumSym", "ErrorSym", "EndSym"};

	//label_codes enum lineup with global label string array in glarr.h

	struct symTransition {
		enum sym_codes sym_src;
		enum label_codes label_ret;
		enum sym_codes sym_dst;
	};

	static struct symTransition sym_state_transition[] = {

		{newsym, 	sClass,		keysym},
		{newsym, 	sConst, 	keysym},
		{newsym, 	sVar, 		keysym},
		{newsym,	sRead,		iosym},
		{newsym,	sWrite,		iosym},
		{newsym, 	sLcb,	 	opsym},
		{newsym, 	sRcb,	 	opsym},
		{newsym, 	sComma, 	opsym},
		{newsym, 	sSemicolon, 	opsym},
		{newsym, 	sAssgin, 	opsym},
		{newsym, 	sPlus,		opsym},
		{newsym, 	sMinus, 	opsym},
		{newsym, 	sMul, 		opsym},
		{newsym, 	sDivi,	 	opsym},
		{newsym, 	sString,	alphasym},
		{newsym, 	sInt, 		numsym},
		{newsym, 	sUnknown, 	endsym},

		{keysym, 	sString,	alphasym},
		{keysym, 	sComma,		opsym},

		{iosym,		sString,	alphasym},

		{opsym, 	sInt, 		numsym},
		{opsym, 	sString,	alphasym},

		{alphasym, 	sLcb,	 	newsym},
		{alphasym, 	sRcb,	 	newsym},
		{alphasym, 	sComma, 	keysym},
		{alphasym, 	sSemicolon, 	newsym},
		{alphasym, 	sAssgin, 	opsym},
		{alphasym, 	sPlus,		opsym},
		{alphasym, 	sMinus, 	opsym},
		{alphasym, 	sMul, 		opsym},
		{alphasym, 	sDivi,	 	opsym},

		{numsym, 	sInt, 		newsym},
		{numsym, 	sLcb,	 	newsym},
		{numsym, 	sRcb,	 	newsym},
		{numsym, 	sComma, 	keysym},
		{numsym, 	sSemicolon, 	newsym},
		{numsym, 	sAssgin, 	opsym},
		{numsym, 	sPlus,		newsym},
		{numsym, 	sMinus, 	newsym},
		{numsym, 	sMul, 		newsym},
		{numsym, 	sDivi,	 	newsym},
		};

		enum sym_codes lookup_symTransitions(enum sym_codes, enum label_codes);
		//END FSM Components


//
//FSM Tokenizer Components
//The following three arrays need to be in sync for proper results
static int (* state[])(char) = { entry_state, letter_state, digit_state, symbol_state, token_state, exit_state};
enum state_codes { entry, letter, digit, symbol, token, end};
static const char* get_state[] = { "entry", "letter", "digit", "symbol", "token", "end"};

//The following two arrays need to be in sync for proper results
enum ret_codes { alpha, num, lcb, rcb, comma, semicolon, assign, plus, sub, mul, divi, gt, lt, space};
static const char* get_ret[] = { "alpha", "num", "lcb", "rcb", "comma", "semicolon", "assign", "plus", "sub", "mul", "divi", "gt", "lt", "space"};
struct transition {
	enum state_codes src_state;
	enum ret_codes ret_codes;
	enum state_codes dst_state;
};

static struct transition state_transition[] = {

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

	{entry,		lt,		symbol},
	{entry,		gt,		symbol},

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
	{symbol, 	assign,		symbol},
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

	{token,		lt,		symbol},
	{token,		gt,		symbol},

	{token,		space,		entry}};


#define EXIT_STATE end
#define ENTRY_STATE entry

enum state_codes lookup_transitions(enum state_codes, enum ret_codes);
//END FSM Components


//
//Flags
extern bool tokenize;

#endif
