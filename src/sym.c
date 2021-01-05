#include <sym.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

add_t var_address = FIRST_ADDRESS;

struct symbol_table SP          =       {"SP"           ,0x0000,&LCL};
struct symbol_table LCL         =       {"LCL"          ,0x0001,&ARG};
struct symbol_table ARG         =       {"ARG"          ,0x0002,&THIS};
struct symbol_table THIS        =       {"THIS"         ,0x0003,&THAT};
struct symbol_table THAT        =       {"THAT"         ,0x0004,&R0};

struct symbol_table R0          =       {"R0"           ,0x0000,&R1};
struct symbol_table R1          =       {"R1"           ,0x0001,&R2};
struct symbol_table R2          =       {"R2"           ,0x0002,&R3};
struct symbol_table R3          =       {"R3"           ,0x0003,&R4};
struct symbol_table R4          =       {"R4"           ,0x0004,&R5};
struct symbol_table R5          =       {"R5"           ,0x0005,&R6};
struct symbol_table R6          =       {"R6"           ,0x0006,&R7};
struct symbol_table R7          =       {"R7"           ,0x0007,&R8};
struct symbol_table R8          =       {"R8"           ,0x0008,&R9};
struct symbol_table R9          =       {"R9"           ,0x0009,&R10};
struct symbol_table R10         =       {"R10"          ,0x000a,&R11};
struct symbol_table R11         =       {"R11"          ,0x000b,&R12};
struct symbol_table R12         =       {"R12"          ,0x000c,&R13};
struct symbol_table R13         =       {"R13"          ,0x000d,&R14};
struct symbol_table R14         =       {"R14"          ,0x000e,&R15};
struct symbol_table R15         =       {"R15"          ,0x000f,&SCREEN};

struct symbol_table SCREEN      =       {"SCREEN"       ,0x4000,&KBD};
struct symbol_table KBD         =       {"KBD"          ,0x6000,NULL_SYMBOL_TABLE};

struct symbol_table *s_s_table = &SP;

void addEntry(char *symbol_name,unsigned address){
	for (now_s_table=s_s_table;
		now_s_table->next!=NULL_SYMBOL_TABLE;
		now_s_table=now_s_table->next)
		;
	struct symbol_table *new = (struct symbol_table *) malloc(sizeof(struct symbol_table));
	strcpy(new->name,symbol_name);
	new->address = address;
	new->next = NULL_SYMBOL_TABLE;
	now_s_table->next = new;
	printf("now_s_table=>%s\n",now_s_table->name);
}

void addVarEntry(char *symbol_name){
	for (now_s_table=s_s_table;
		now_s_table->next!=NULL_SYMBOL_TABLE;
		now_s_table=now_s_table->next)
		;
	struct symbol_table *var = (struct symbol_table *) malloc(sizeof(struct symbol_table));
	strcpy(var->name,symbol_name);
	var->address = var_address;
	var->next = NULL_SYMBOL_TABLE;
	now_s_table->next = var;
	var_address++;
}
int contains(char *symbol_name){
	struct symbol_table *check;
	for (check=s_s_table;
		check!=NULL_SYMBOL_TABLE;
		check=check->next){
		if (strcmp(check->name,symbol_name)==0)
			return TRUE;
	}
	return FALSE;
}

add_t getAddress(char *symbol_name){
	struct symbol_table *check;
	for (check=s_s_table;
		check!=NULL_SYMBOL_TABLE;
		check=check->next){
		if (strcmp(check->name,symbol_name)==0)
			return check->address;
	}
	return -1;
}
