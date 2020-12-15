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

#include "glo.h"

/*
 *  check if the command still exists in the entered file.
 *  return TRUE(1) or FALSE(0).
 */
int hasMoreCommands(void);

/*
 *  read the next command from the input and make it the current command.
 *  return nothing.
 */
void advance(void);

/*
 *  return current command type.
 */
/* command type */
typedef enum c_type{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND
} command_type;

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
