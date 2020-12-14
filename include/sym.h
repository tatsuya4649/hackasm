
/* the struct of symbol table */
typedef struct symbol_table{
	char 	*name;
	int	address;
	struct symbol_table *next;
}s_table;

#define NULL_SYMBLE_TABLE	((struct symbol_table *) 0)

struct symbol_table KBD,SCREEN;
struct symbol_table SP,LCL,ARG,THIS,THAT;
struct symbol_table R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15;

struct symbol_table SP		=	{"SP"		,0x0000,&LCL};
struct symbol_table LCL		=	{"LCL"		,0x0001,&ARG};
struct symbol_table ARG		=	{"ARG"		,0x0002,&THIS};
struct symbol_table THIS	=	{"THIS"		,0x0003,&THAT};
struct symbol_table THAT	=	{"THAT"		,0x0004,&R0};

struct symbol_table R0		=	{"R0"		,0x0000,&R1};
struct symbol_table R1		=	{"R1"		,0x0001,&R2};
struct symbol_table R2		=	{"R2"		,0x0002,&R3};
struct symbol_table R3		=	{"R3"		,0x0003,&R4};
struct symbol_table R4		=	{"R4"		,0x0004,&R5};
struct symbol_table R5		=	{"R5"		,0x0005,&R6};
struct symbol_table R6		=	{"R6"		,0x0006,&R7};
struct symbol_table R7		=	{"R7"		,0x0007,&R8};
struct symbol_table R8		=	{"R8"		,0x0008,&R9};
struct symbol_table R9		=	{"R9"		,0x0009,&R10};
struct symbol_table R10		=	{"R10"		,0x000a,&R11};
struct symbol_table R11		=	{"R11"		,0x000b,&R12};
struct symbol_table R12		=	{"R12"		,0x000c,&R13};
struct symbol_table R13		=	{"R13"		,0x000d,&R14};
struct symbol_table R14		=	{"R14"		,0x000e,&R15};
struct symbol_table R15		=	{"R15"		,0x000f,&SCREEN};

struct symbol_table SCREEN	=	{"SCREEN"	,0x4000,&KBD};
struct symbol_table KBD		=	{"KBD"		,0x6000,NULL_SYMBLE_TABLE};

struct symbol_table *s_s_table = &SP;
