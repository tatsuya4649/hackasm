#include <parser.h>
#include <glo.h>
#include <stdio.h>
#include <code.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sym.h>

int main(int argc,const char *argv[])
{
	const char *file;
	char bifile[MAX_FILE_NAME];
	/* file pointer to assemly(.asm) and to binary(.hack) */
	FILE *afp,*bfp;
	long update_line(void);
	void addEntry(char *,unsigned);
	if ( !argv[1] || argc<=1 )
		printf("error : not found to .asm file\n");
	/* get file name */
	file = argv[1];
	if ( (afp = fopen(file,"r")) == NULL){
		printf("error: can't open assembly file\n");
		return 1;
	}
	parse_file(afp);
	while(hasMoreCommands()){
		reg_cmd();
		if (current_command!=NULL){
			/* if A or C command,update line number */
			if (current_command->type==A_COMMAND||current_command->type==C_COMMAND)
				current_command->now_row = update_line();
			/* change to binary code */
			printf("===========================================\n");
			printf("current commands's now_row => %ld\n",current_command->now_row);
			printf("current commands's symbol => %s\n",current_command->symbol);
			printf("current commands's dest => %s\n",current_command->dest);
			printf("current commands's comp => %s\n",current_command->comp);
			printf("current commands's jump => %s\n",current_command->jump);
			/* this commands is LABEL */
			if (strlen(current_command->symbol)!=0 && current_command->type==L_COMMAND){
				/* add symbol table (only LABEL)*/
				addEntry(current_command->symbol,current_command->now_row);
			}
		}
	}
	printf("total lines => %ld\n",update_line());
	if (start_seek()<0){
		printf("error: start_seek\n");
		exit(1);
	}
	int i=0,j=0,k=0;
	for (const char *f=file;*f!='\0';f++,i++){
		if (*f=='/')
			j=i;
	}
	j++;
	for (const char *f=(file+j);*f!='.';f++,k++){
		bifile[k] = *f;
	}
	printf("%s\n",file);
	printf("%s\n",bifile);
	strcat(bifile,".hack");
	if ((bfp=fopen(bifile,"w")) == NULL){
		printf("error: can't open hack(binary) file\n");
		return 1;
	}
	printf("open %s!\n",bifile);
	while(hasMoreCommands()){
		reg_cmd();
		if (current_command!=NULL){
			current_command->now_row = update_line();
			printf("current commands's now_row => %ld\n",current_command->now_row);
			switch(current_command->type){
				case A_COMMAND:
					printf("A_COMMAND\n");
					if (strlen(current_command->symbol)==0)
						printf("current_command symbol name's length 0\n");
					/* if digit ex. @134 */ if (isdigit(current_command->symbol[0])){
						char *a_binary;
						a_binary = (char *) malloc(A_COMMAND_BINARY_LEN+1);
						/* A_COMMAND_ */
						a_binary[0] = A_COMMAND_PRE;
						/* TODO: change symbol to binary number */
						__bia(a_binary+1,current_command->symbol,A_COMMAND_BINARY_LEN);
						/* TODO: put binary file */
						a_binary[A_COMMAND_BINARY_LEN+1] = '\n';
						fputs(a_binary,bfp);
					}else{
						/* TODO: if LABEL and VARIABLES */
						if (contains(current_command->symbol)){
							/* TODO: LABEL */
							printf("this is LABEL\n");
							printf("%d\n",getAddress(current_command->symbol));
							char *a_binary;
							a_binary = (char *) malloc(A_COMMAND_BINARY_LEN+1);
							a_binary[0] = A_COMMAND_PRE;
							__bi(a_binary+1,getAddress(current_command->symbol),A_COMMAND_BINARY_LEN);
							a_binary[A_COMMAND_BINARY_LEN+1] = '\n';
							fputs(a_binary,bfp);
						}else{
							/* TODO: VARIABLES */
							printf("this is variables\n");
							printf("%s\n",current_command->symbol);
							addVarEntry(current_command->symbol);
							char *a_binary;
							a_binary = (char *) malloc(A_COMMAND_BINARY_LEN+1);
							/* A_COMMNAD */
							a_binary[0] = A_COMMAND_PRE;
							__bi(a_binary+1,getAddress(current_command->symbol),A_COMMAND_BINARY_LEN);
							a_binary[A_COMMAND_BINARY_LEN+1] = '\n';
							fputs(a_binary,bfp);
						}
					}
					break;
				case C_COMMAND:
					printf("C_COMMAND\n");
					char *c_binary;
					c_binary = (char *) malloc(C_COMMAND_BINARY_LEN+1);
					strcpy(&c_binary[0],C_COMMAND_PRE);
					printf("%s\n",__comp(current_command->comp));
					strcpy(&c_binary[C_COMMAND_COMP_IND],__comp(current_command->comp));
					strcpy(&c_binary[C_COMMAND_DEST_IND],__dest(current_command->dest));
					strcpy(&c_binary[C_COMMAND_JUMP_IND],__jump(current_command->jump));
					c_binary[C_COMMAND_BINARY_LEN+1] = '\n';
					fputs(c_binary,bfp);
					break;
				case L_COMMAND:
					printf("L_COMMAND\n");
					add_t label_address;
					if ((label_address=getAddress(current_command->symbol))<0)
						fprintf(stderr,"error: not found L_COMMAND address\n");
					char *l_binary;
					l_binary = (char *) malloc(L_COMMAND_BINARY_LEN+1);
					l_binary[0] = L_COMMAND_PRE;
					__bi(l_binary+1,label_address,L_COMMAND_BINARY_LEN);
					l_binary[L_COMMAND_BINARY_LEN+1] = '\n';
					fputs("\n",bfp);
					break;
				default:
					printf("else_COMMAND\n");
					break;
			}
		}
	}
	return 0;
}
