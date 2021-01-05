/*
 *	this file is a header file that declares the variables
 *	and functions needed to parse the input.
 *	
 *	Parser Mudules API
 *	------------------------
 *	int hasMoreCommands(void)
 *	void advance(void)
 *	command_type commandType(void)
 *	char *symbol(void)
 *	char *dest(void)
 *	char *comp(void)
 *	char *jump(void)
 */

#ifndef _PARSER_H
#define _PARSER_H

#include "glo.h"
#include <stdio.h>

/* command type */
typedef enum c_type{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND
} command_type;

/* command struct */
#define MAX_LENGTH		1000
struct command{
	char symbol[MAX_SYMBOL_LENGTH];
	command_type type;
	char dest[MAX_LENGTH];
	char comp[MAX_LENGTH];
	char jump[MAX_LENGTH];
	long now_row;
};

FILE* fp;
/* pointer to now command */
struct command *current_command;

/*
 *  get file pointer to assemble(.asm)
 */
void parse_file(FILE *fp);
/*
 *  seek file to start
 */
int start_seek(void);

/*
 *  check if the command still exists in the entered file.
 *  return TRUE(1) or FALSE(0).
 */
int hasMoreCommands(void);

/*
 *  read the next command from the input and make it the current command.
 *  if files have not next command, return immediately.
 *  return nothing.
 */
void advance(void);

/*
 *  return current command type.
 */
command_type commandType(void);

/*
 *  return symbol name of current command.
 */
char *symbol(void);

/*
 *  return dest mnemonic of current C instruction.(symbol or decimal)
 */
char *dest(void);

/*
 *  return comp mnemonic of current C instruction.
 */
char *comp(void);

/*
 *  return jump mnemonic of current C instruction.
 */
char *jump(void);

/*
 * helper : analyze command types
 */
void reg_cmd(void);

#endif // _PARSER_H
