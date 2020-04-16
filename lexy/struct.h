#ifndef STRUCT_H
#define STRUCT_H

struct Node {
        void *data;
        struct Node *next;
};

struct tokenClass {
	char lit[32];
	int label;
};

struct symbol {
	struct tokenClass *token;
        int val;
        int adrs;
        char seg[2];
};

struct Quads {
	struct tokenClass *op;
	struct tokenClass *polyOne;
	struct tokenClass *polyTwo;
	struct tokenClass *result;
};
#endif
