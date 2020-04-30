#include "ophelia.h"

char* getCode(void* f, int* labCount)
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

	if(quad->op->label == sElse)
		return elseCode(labCount);

	if(quad->op->label == sEndif)
		return endifCode(labCount);

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

	if(quad->op->label == sJe)
		return jeCode(quad->polyOne->lit, quad->polyTwo->lit, labCount);
	if(quad->op->label == sJge)
		return jgeCode(quad->polyOne->lit, quad->polyTwo->lit, labCount);
	if(quad->op->label == sJle)
		return jleCode(quad->polyOne->lit, quad->polyTwo->lit, labCount);
	if(quad->op->label == sJg)
		return jgCode(quad->polyOne->lit, quad->polyTwo->lit, labCount);
	if(quad->op->label == sJl)
		return jlCode(quad->polyOne->lit, quad->polyTwo->lit, labCount);

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

char* elseCode(int* count)
{
	int buffer = 32;
	char *code = malloc(sizeof(char)*buffer);
	sprintf(code, "\tjmp L%d\nL%d:\tnop",*count+1, *count);
	++(*count++);

	return code;
}

char* endifCode(int* count)
{
	int buffer = 32;
	char *code = malloc(sizeof(char)*buffer);
	sprintf(code, "L%d:\tnop", *count);
	++(*count++);

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

char* jeCode(char* polyOne, char* polyTwo, int* count)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcmp ax, [%s]\n"
		"\tje L%d\n"
		"\tjne L%d\n"
		"\nL%d:\n",
		polyOne, polyTwo, *count, *count+1, *count);

	++*count;

	return code;
}

char* jgeCode(char* polyOne, char* polyTwo, int* count)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcmp ax, [%s]\n"
		"\tjge L%d\n"
		"\tjl L%d\n"
		"\nL%d:\n",
		polyOne, polyTwo, *count, *count+1, *count);

	++*count;

	return code;
}

char* jleCode(char* polyOne, char* polyTwo, int* count)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcmp ax, [%s]\n"
		"\tjle L%d\n"
		"\tjg L%d\n"
		"\nL%d:\n",
		polyOne, polyTwo, *count, *count+1, *count);

	++*count;

	return code;
}

char* jgCode(char* polyOne, char* polyTwo, int* count)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcmp ax, [%s]\n"
		"\tjg L%d\n"
		"\tjle L%d\n"
		"\nL%d:\n",
		polyOne, polyTwo, *count, *count+1, *count);

	++*count;

	return code;
}

char* jlCode(char* polyOne, char* polyTwo, int* count)
{
	int buffer = 512;
	char *code = malloc(sizeof(char)*buffer);

	polyOne = NumToLit(polyOne);
	polyTwo = NumToLit(polyTwo);

	sprintf(code,
		"\tmov ax, [%s]\n"
		"\tcmp ax, [%s]\n"
		"\tjl L%d\n"
		"\tjge L%d\n"
		"\nL%d:\n",
		polyOne, polyTwo, *count, *count+1, *count);

	++*count;

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
