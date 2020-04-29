#include "ophelia.h"

char* getCode(void* f)
{
	struct Quads *quad = (struct Quads*)calloc(1,sizeof(struct Quads));
	quad->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyOne = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyTwo = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	getQuadInfo(f, &quad);

	if(quad->op->label == sRead)
		return readCode(quad->result->lit);

	if(quad->op->label == sWrite)
		return writeCode(quad->result->lit);

	if(quad->op->label == sAssgin)
		return assignCode(quad->polyOne->lit, quad->result->lit);

	if(quad->op->label == sMul)
		return mulCode(quad->polyOne->lit, quad->polyTwo->lit,
				quad->result->lit);

	if(quad->op->label == sDivi)
		return diviCode(quad->polyOne->lit, quad->polyTwo->lit,
				quad->result->lit);

	if(quad->op->label == sPlus)
		return plusCode(quad->polyOne->lit, quad->polyTwo->lit,
				quad->result->lit);

	if(quad->op->label == sMinus)
		return minusCode(quad->polyOne->lit, quad->polyTwo->lit,
				quad->result->lit);

	return "";
}

char* readCode(char* lit)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);
	sprintf(code,
		"\tcall PrintString\n"
		"\tcall GetAnInteger\n"
		"\tmov ax, [ReadInt]\n"
		"\tmov [%s], ax\n",
		lit);

	return code;
}

char* writeCode(char* lit)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);
	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcall ConvertIntegerToString\n"
		"\tmov eax, 4\n"
		"\tmov ebx, 1\n"
		"\tmov ecx, Result\n"
		"\tmov edx, ResultEnd\n"
		"\tint 80h\n",
		lit);

	return code;
}

char* assignCode(char* val, char* lit)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	val = NumToLit(val);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tmov [%s], ax\n",
		val, lit);

	return code;
}

char* mulCode(char* polyOne, char* polyTwo, char* result)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tmul word [%s]\n"
		"\tmov [%s], ax\n",
		polyOne, polyTwo, result);

	return code;
}

char* diviCode(char* polyOne, char* polyTwo, char* result)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov dx, 0\n"
		"\tmov ax, [%s]\n"
		"\tdiv word [%s]\n"
		"\tmov [%s], ax\n",
		polyOne, polyTwo, result);

	return code;
}

char* plusCode(char* polyOne, char* polyTwo, char* result)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tadd ax, [%s]\n"
		"\tmov [%s], ax\n",
		polyOne, polyTwo, result);

	return code;
}

char* minusCode(char* polyOne, char* polyTwo, char* result)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tsub ax, [%s]\n"
		"\tmov [%s], ax\n",
		polyOne, polyTwo, result);

	return code;
}

char* NumToLit(char* val)
{
	printf("HELLO %s\n", val);
	if(!atoi(val))
		return val;

	char *temp = (char*)calloc(32,sizeof(char));
	strcat(temp, "lit");
	strcat(temp, val);

	printf("HELLO %s\n", temp);
	return temp;
}
