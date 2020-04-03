#include "lisa.h"

void push(struct Node** headRef, void *newData, size_t dataSize)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->data = malloc(dataSize);
	newNode->next = (*headRef);

	size_t pos;
	for(pos=0; pos<dataSize; pos++)
		*(char*)(newNode->data + pos) = *(char*)(newData + pos);

	(*headRef) = newNode;
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
	printf("lit: %s\t\tlab: %d\tval: %d\tadrs: %d\t%s\n", data->token->lit, data->token->label,
		data->val, data->adrs, data->seg);
}

void printToken(void *f)
{
	struct tokenClass* data = (struct tokenClass*)f;
	printf("%s\t%d\n", data->lit, data->label);
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
