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
	printf("%s\t%d\t%d\t%d\t%s\n", data->token->lit, data->token->label,
		data->val, data->adrs, data->seg);
}

void printToken(void *f)
{
	struct tokenClass* data = (struct tokenClass*)f;
	printf("%s\t%d\n", data->lit, data->label);
}
