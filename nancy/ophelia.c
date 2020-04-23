#include "ophelia.h"

char* getCode(void* f)
{
	struct Quads *quad = (struct Quads*)calloc(1,sizeof(struct Quads));
	quad->op = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyOne = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->polyTwo = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));
	quad->result = (struct tokenClass*)calloc(1,sizeof(struct tokenClass));

	getQuadInfo(f, &quad);

	if(quad->op->lable == sRead)
		return readCode(quad->result->lit);

	if(quad->op->lable == sWrite)
		return writeCode(quad->result->lit);

	if(quad->op->lable == sAssgin)
		return assignCode(quad->result->lit);

	if(quad->op->lable == sMul)
		return mulCode(quad->result->lit);

	if(quad->op->lable == sDivi)
		return diviCode(quad->result->lit);

	if(quad->op->lable == sPlus)
		return plusCode(quad->result->lit);

	if(quad->op->lable == sMinus)
		return minusCode(quad->result->lit);

	return "";
}
