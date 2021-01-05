/* code.h interface of code module
 * convert the received mnemonic to a bit string and return it.
 */
#ifndef _CODE_H
#define _CODE_H

#include <glo.h>
#include <sym.h>

/* C_COMMAND API */
char *__dest(char *);
char *__comp(char *);
char *__jump(char *);

/* A_COMMAND API */
void __bia(char *,char *,int);
void __bi(char *,add_t,int);

#endif // _CODE_H
