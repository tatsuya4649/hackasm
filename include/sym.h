

#ifndef _SYM_H
#define _SYM_H

#include "glo.h"
typedef int add_t;
/* the struct of symbol table */
typedef struct symbol_table{
	char 	name[MAX_SYMBOL_LENGTH];
	add_t	address;
	struct symbol_table *next;
}s_table;

#define NULL_SYMBOL_TABLE	((struct symbol_table *) 0)
#define FIRST_ADDRESS		((add_t) 0x0010)
extern add_t var_address;

struct symbol_table KBD,SCREEN;
struct symbol_table SP,LCL,ARG,THIS,THAT;
struct symbol_table R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15;

extern struct symbol_table *s_s_table;
struct symbol_table *now_s_table;

/* symbol module API */
/* add symbol entry (add only LABEL) */
void addEntry(char *symbol_name,unsigned address);
/* whether have symbol_name? */
int contains(char *symbol_name);
/* get symbol address (if no symbol_name, return -1) */
add_t getAddress(char *symbol_name);


/* variables API */
void addVarEntry(char *symbol_name);

#endif // _SYM_H
