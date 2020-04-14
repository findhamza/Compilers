#include "missyd.h"

int main()
{
	char *equ;
	struct Node *inFix = NULL;
	struct Node *postFix = NULL;

	printf("\nEnter equation: ");
	scanf("%s", equ);

	int i=0;
	while(equ[i] != '\0')
	{
		push(&inFix, &equ[i], sizeof(char));
		i++;
	}

	InToPost(inFix, &postFix);

	while(postFix->next != NULL)
	{
		printf("%s", (char*)(postFix->data));
		postFix = postFix->next;
	}

	return 0;
}
