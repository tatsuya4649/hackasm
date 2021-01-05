#include <parser.h>
#include <stdlib.h>
#include <string.h>
#include "parser_impl.h"

/* command max length */
#define MAX_COMMD_LEN	1000
/* command string */
char commands[MAX_COMMD_LEN];
/* command length */
int n;

/* if find commands, return 1
 * if not find commands or error, return -1
 */
int find_line(void);
void parse_file(FILE *afp){
	fp = afp;
}
extern long new_line;
int start_seek(void){
	if (fp==NULL) return -1;
	if (fseek(fp,0,SEEK_SET) != 0) return -1;
	printf("seek .asm file to start!\n");
	new_line=0;
	return 0;
}

int find_line(void){
	n = 0; 
	while ((fp != NULL) && (*(commands+n) = fgetc(fp)) != '\n'){
		/* find out file end */
		if (*(commands+n) == EOF) return -1;
		if (*(commands+n) != '\t' && *(commands+n) != ' '){
			n++;
		}
	}
//	if (n!=0)
//		printf("\n");
	*(commands+n) = '\0';
	return 1;
}

/*
 * parse eatch row and add to the symbol table
 */
enum symbol{
	NO = '\0',
	COMMENT = '/',
	AINS = '@',
	LABEL = '('
};
/* register current command for A instruction */
void acommand(void);
/* register current command for C instruction */
void ccommand(void);
/* register current command for Label instruction */
void lcommand(void);
void reg_cmd(void){
	switch(*commands){
		case NO:
			break;
		case COMMENT:
			if (*(commands+1) != '/'){
				printf("error : if you want to comment, must be '//'.\n");
				exit(1);
			}
			return;
		case AINS:
			acommand();
			return;
		case LABEL:
			lcommand();
			return;
		default:
			ccommand();
			return;
	}
	/* free memory of pre current_command */
	if (current_command!=NULL){
		free(current_command);
		current_command = NULL;
	}
}

/* alloc struct command memory */
void alloc_command(void){
	free(current_command);
	current_command = (struct command *)malloc(sizeof(struct command));
	if (current_command == NULL){
		printf("memory cannot alloc\n");
		exit(1);
	}
}

void asymbol(char *);
void acommand(void){
	alloc_command();
	asymbol(current_command->symbol);
	current_command->type = A_COMMAND;
}
void asymbol(char *sym){
	int i,j;
	/* remove @ of symbol */
	for (i=0;*(commands+i)!='@';i++)
		;
	i++;
	for (j=0;*(commands+i)!='\n';j++,i++)
		*(sym+j) = *(commands+i);
	j++;
	*(sym+j) = '\0';
}

/* get destination of C command from mnimonic */
void destination(char *);
/* get jump of C command from mnimonic */
void _jump(char *);
/* get comp of C command from mnimonic */
void _comp(char *);
void ccommand(void){
	alloc_command();
	current_command->symbol[0] = '\0';
	current_command->type = C_COMMAND;
	destination(current_command->dest);
	_jump(current_command->jump);
	_comp(current_command->comp);
}

void destination(char *dest){
	int i;
	for (i=0;*(commands+i)!='=';i++){
		*(dest+i) = *(commands+i);
		if (*(commands+i)==';' || *(commands+i)=='\n'){
			strcpy(dest,"null");
			return;
		}
	}
	*(dest+i) = '\0';
}
#define JUMP_NUMBER	3
void _jump(char *jmp){
	int i=0;
	for (i=0;*(commands+i)!=';';i++){
		if (*(commands+i)=='\0' || *(commands+i)=='\n'){
			strcpy(jmp,"null");
			return;
		}
	}
	i++;
	int k=0;
	for (int j=i;*(commands+j)!='\n' || j<(i+3);j++){
		if (*(commands+j) != ' ' || *(commands+j) != '\t'){
			*(jmp+k) = *(commands+j);
			k++;
		}
	}
	*(jmp+k+1) = '\0';
	return;
}
void _comp(char *cmp){
	int i;
	int end=1;
	i=0;
	while (end){
		switch(*(commands+i)){
			case '=':
				i++;
				end=0;
				break;
			case ';':
				i=0;
				end=0;
				break;
			case '\n':
				i=0;
				end=0;
				break;
			case ' ':
				i++;
			default:
				i++;
		}
	}
	int k;
	for (k=0;*(commands+i)!='\n' && *(commands+i)!=' ' && *(commands+i)!='\0' && *(commands+i)!=';';k++,i++){
		*(cmp+k) = *(commands+i);
	}
	//k++;
	*(cmp+k) = '\0';
}

void lsymbol(char *);
void lcommand(void){
	alloc_command();
	current_command->symbol[0] = '\0';
	lsymbol(current_command->symbol);
	current_command->type = L_COMMAND;
}
void lsymbol(char *sym){
	int i,j;
	for (i=0;*(commands+i)!='(';i++)
		;
	i++;
	for (j=0;*(commands+i)!=')';j++,i++){
		if (*(commands+i) == '\n')
			printf("error : no label end ')'");
		if (j > MAX_SYMBOL_LENGTH){
			printf("error : too symbol long\n");
			exit(1);
		}
		*(sym+j) = *(commands+i);
	}
	j++;
	*(sym+j) = '\0';
}

int hasMoreCommands(void){
	return find_line() > 0;
}

void advance(void){
	if (!hasMoreCommands())
		return;
}

command_type commandType(void){
	return current_command->type;
}

char *symbol(void){
	if (current_command->type == A_COMMAND || current_command->type == L_COMMAND)
		return current_command->symbol;
	else{
		printf("error : symbol must have A_COMMAND or L_COMMAND\n");
		return NULL;
	}
}

char *dest(void){
	if (current_command->type == C_COMMAND)
		return current_command->dest;
	else{
		printf("error : dest must have C_COMMAND\n");
		return NULL;
	}
}

char *comp(void){
	if (current_command->type == C_COMMAND)
		return current_command->comp;
	else{
		printf("error : comp must have C_COMMAND\n");
		return NULL;
	}
}

char *jump(void){
	if (current_command->type == C_COMMAND)
		return current_command->jump;
	else{
		printf("error : jump must have C_COMMAND\n");
		return NULL;
	}
}

/* helper */
long new_line = 0;
long update_line(){
	return ++new_line;
}
