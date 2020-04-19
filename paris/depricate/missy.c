#include "missy.h"

void InToPost(struct Node* inFix, struct Node** outFix)
{
	struct Node *temp = NULL;
	char *x = NULL, *token = NULL;
	size_t cSize = sizeof(char*);
	int i, j=0;

	printf("HELLO");

	while(inFix->next != NULL)
	{
		token = inFix->data;

		if(isalnum(token[0]))
			push(outFix, &token[0], sizeof(char*));
		else
			if(token[0]=='(')
				push(&temp, &token[0], sizeof(char*));
		else
			if(token[0]==')')
				while((x=(char*)pop(&temp,cSize))[0]!='(')
					push(outFix, &x[0], sizeof(char*));
				else
				{
					char* t = NULL;
					t = (char **)&(temp->data);
					while(precy(token[0]) <= precy(&t[0]) && !is_empty(&temp))
					{
						x = (pop(&temp,cSize));
						push(&temp, &token[0], sizeof(char*));
						t = temp->data;
					}
				}
	}

	while(!is_empty(&temp))
	{
		push(outFix, pop(&temp,cSize), sizeof(char*));
	}
}

int precy(char a)
{
	if(a=='(')
		return 0;
	else if(a=='-')
		return 1;
	else if(a=='+')
		return 2;
	else if(a=='/')
		return 3;
	else if(a=='*')
		return 4;
	else
		return 5;
}
