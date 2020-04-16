/* Author:      Hamza Syed      */
/* COSC4317:    Compilers       */
/* Part-1:      Lexical         */


//Include Sector
//Header Files
#include "../lexy/syslib.h"
#include "../lexy/struct.h"
#include "../lexy/lisa.h"
#include "../lexy/glarr.h"
//#include "missy.h"

//
//Function Init Sector
char *LexReader(char *fileName);
void parser(char *lexCode);

//driver
//int missy();

//FSM Parser Functions
int new_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int key_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int io_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int op_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int alpha_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int num_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int error_prs(char*,int,struct Quads**,struct Node**,struct Node**);
int end_prs(char*,int,struct Quads**,struct Node**,struct Node**);
//END FSM Parser Functions

//
//FSM Parser Components
int (* prsState[])(char*, int, struct Quads**, struct Node**, struct Node**) = { new_prs, key_prs, io_prs, op_prs, alpha_prs, num_prs, error_prs, end_prs};
enum prs_codes { newprs, keyprs, ioprs, opprs, alphaprs, numprs, errorprs, endprs};
const char* get_prsState[] = { "NewPrs", "KeyPrs", "IoPrs", "OpPrs", "AlphaPrs", "NumPrs", "ErrorPrs", "EndPrs"};

	//label_codes enum lineup with global label string array in glarr.h

struct prsTransition {
	enum prs_codes prs_src;
	enum label_codes label_ret;
	enum prs_codes prs_dst;
};

struct prsTransition prs_state_transition[] = {

		{newprs,        sClass,         keyprs},
                {newprs,        sConst,         keyprs},
                {newprs,        sVar,           keyprs},
                {newprs,        sRead,          ioprs},
                {newprs,        sWrite,         ioprs},
                {newprs,        sLcb,           opprs},
                {newprs,        sRcb,           opprs},
                {newprs,        sComma,         opprs},
                {newprs,        sSemicolon,     opprs},
                {newprs,        sAssgin,        opprs},
                {newprs,        sPlus,          opprs},
                {newprs,        sMinus,         opprs},
                {newprs,        sMul,           opprs},
                {newprs,        sDivi,          opprs},
                {newprs,        sString,        alphaprs},
                {newprs,        sInt,           numprs},
                {newprs,        sUnknown,       endprs},

                {keyprs,        sString,        alphaprs},
                {keyprs,        sComma,         opprs},

                {ioprs,         sString,        alphaprs},

                {opprs,         sInt,           numprs},
                {opprs,         sString,        alphaprs},

                {alphaprs,      sLcb,           newprs},
                {alphaprs,      sRcb,           newprs},
                {alphaprs,      sComma,         keyprs},
                {alphaprs,      sSemicolon,     newprs},
                {alphaprs,      sAssgin,        opprs},
                {alphaprs,      sPlus,          opprs},
                {alphaprs,      sMinus,         opprs},
                {alphaprs,      sMul,           opprs},
                {alphaprs,      sDivi,          opprs},

                {numprs,        sInt,           newprs},
                {numprs,        sLcb,           newprs},
                {numprs,        sRcb,           newprs},
                {numprs,        sComma,         keyprs},
                {numprs,        sSemicolon,     newprs},
                {numprs,        sAssgin,        opprs},
                {numprs,        sPlus,          newprs},
                {numprs,        sMinus,         newprs},
                {numprs,        sMul,           newprs},
                {numprs,        sDivi,          newprs},
                };

enum prs_codes lookup_prsTransitions(enum prs_codes, enum label_codes);
//END FSM Components

