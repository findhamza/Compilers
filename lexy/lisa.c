#include "lisa.h"

void push(struct Node** headRef, void *newData, size_t dataSize)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->data = malloc(dataSize);
	newNode->next = (*headRef);

	memmove(newNode->data, newData, dataSize);
//	size_t pos;
//	for(pos=0; pos<dataSize; pos++)
//		*(char*)(newNode->data + pos) = *(char*)(newData + pos);

	(*headRef) = newNode;
}

void *pop(struct Node** headRef, size_t dataSize)
{
	struct Node* tmp;
	void* data = calloc(1, sizeof(dataSize));

	if(is_empty(headRef))
		return NULL;

	tmp = *headRef;
//	data = (*headRef)->data;
	*headRef = (*headRef)->next;
	free(tmp);
	return data;
}

bool is_empty(struct Node** headRef)
{
	if(*headRef == NULL)
	{
		printf("EMPTY LIST\n");
		return true;
	}
	return false;
}

void pleaseEmpty(struct Node** headRef)
{
	free(*headRef);
	(*headRef) = NULL;
}

void printLisa(struct Node *node, void (*fptr)(void*))
{
	while(node != NULL)
	{
		(*fptr)(node->data);
		node = node->next;
	}
}

void printSymbol(void *f)
{
	struct symbol* data = (struct symbol*)f;

//	struct tokenClass tokenData = data->token;
	printf("lit: %12s\tlab: %d\tval: %d\tadrs: %d\t%s\n", data->token->lit, data->token->label,
		data->val, data->adrs, data->seg);
}

void printToken(void *f)
{
	struct tokenClass* data = (struct tokenClass*)f;
	printf("%s\t%d\n", data->lit, data->label);
}

void printQuad(void *f)
{
	struct Quads* quad = (struct Quads*)f;

	printf("%s\t%s\t%s\t%s\n", quad->op->lit, quad->polyOne->lit, quad->polyTwo->lit, quad->result->lit);
}

void getSymbolInfo(void*f, struct symbol** sym)
{
	struct symbol* data = (struct symbol*)f;
	(*sym) = data;
}

void getTokenInfo(void *f, struct tokenClass** tok)
{
//	struct tokenClass* data = (struct tokenClass*)malloc(sizeof(struct tokenClass));
	struct tokenClass* data = (struct tokenClass*)f;
	(*tok) = data;
}

void normalize(struct Node** headRef)
{
	struct Node* prev = NULL;
	struct Node* cur = *headRef;
	struct Node* next = NULL;

	while(cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	*headRef = prev;
}
