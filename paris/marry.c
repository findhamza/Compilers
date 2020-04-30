#include "marry.h"

void InToPost(struct Node** pds, struct Node** quadNode)
{
	struct Node *opStack = NULL;
	struct Node *outStack = NULL;
	struct tokenClass* token = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	struct tokenClass* peek = (struct tokenClass*)calloc(1, sizeof(struct tokenClass));

	int tempCounter = 0;

	normalize(pds);
	printf("marry:\n");
	printLisa(*pds, printToken);
	printf("\n");

	while(is_empty(pds) == false)
	{
		token = (struct tokenClass*)pop(pds, sizeof(struct tokenClass));

		if(token->label == sString || token->label == sInt)
			push(&outStack, token, sizeof(struct tokenClass));

		else if(token->label >= sJl && token->label <= sMul)
		{
			if(is_empty(&opStack) == false)
			{
				getTokenInfo(opStack->data, &peek);
				while(peek->label > token->label)
				{
					peek = (struct tokenClass*)pop(&opStack, sizeof(struct tokenClass));
					genQuad(&tempCounter, peek, &outStack, quadNode);
					getTokenInfo(opStack->data, &peek);
				}
			}
			push(&opStack, token, sizeof(struct tokenClass));
		}

		else if(strcmp(token->lit, "(")==0)
			push(&opStack, token, sizeof(struct tokenClass));

		else if(strcmp(token->lit, ")")==0)
		{
			if(is_empty(&opStack) == false)
			{
				getTokenInfo(opStack->data, &peek);
				while(strcmp(peek->lit,"("))
				{
					peek = (struct tokenClass*)pop(&opStack, sizeof(struct tokenClass));
					genQuad(&tempCounter, peek, &outStack, quadNode);
					getTokenInfo(opStack->data, &peek);
				}
				pop(&opStack, sizeof(struct tokenClass));
			}
		}

	}
	printf("\n");
	printLisa(opStack, printToken);
	printf("\n");

	while(is_empty(&opStack) == false)
	{
		peek = (struct tokenClass*)pop(&opStack, sizeof(struct tokenClass));
		genQuad(&tempCounter, peek, &outStack, quadNode);
	}

}

void genQuad(int* temp, struct tokenClass* op, struct Node** outStack, struct Node** quadNode)
{
        struct Quads *quad = (struct Quads*)calloc(1,sizeof(struct Quads));
        quad->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
        quad->polyOne = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
        quad->polyTwo = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
        quad->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	quad->op = op;

	if(op->label == sAssgin)
	{
		quad->polyOne = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));
		quad->result = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));
	}

	else if(op->label >= sJl && op->label <= sJe)
	{
		quad->polyTwo = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));
		quad->polyOne = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));
	}

	else
	{
		quad->polyTwo = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));
		quad->polyOne = (struct tokenClass*)pop(outStack, sizeof(struct tokenClass));

		sprintf(quad->result->lit, "temp%d", *temp);
		quad->result->label = sVar;

		(*temp)++;
		push(outStack, quad->result, sizeof(struct tokenClass));
	}

	push(quadNode, quad, sizeof(struct Quads));

}


