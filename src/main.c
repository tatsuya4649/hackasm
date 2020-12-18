#include <sym.h>
#include <parser.h>
#include <stdio.h>
#include <code.h>

int main(int argc,const char *argv[])
{
	const char *file;
	/* file pointer to assemly(.asm) */
	FILE *afp;
	if ( !argv[1] || argc<=1 )
		printf("error : not found to .asm file\n");
	/* get file name */
	file = argv[1];
	if ( (afp = fopen(file,"r")) == NULL){
		printf("can't open assembly file");
		return 1;
	}
	parse_file(afp);
	while(hasMoreCommands()){
		reg_cmd();
	}
}
