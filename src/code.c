
#include <code.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *__dest(char *mne){
	if (strcmp(mne,"null")==0 || strcmp(mne,"NULL")==0){
		return "000";
	}else if (strcmp(mne,"M")==0){
		return "001";
	}else if (strcmp(mne,"D")==0){
		return "010";
	}else if (strcmp(mne,"MD")==0){
		return "011";
	}else if (strcmp(mne,"A")==0){
		return "100";
	}else if (strcmp(mne,"AM")==0){
		return "101";
	}else if (strcmp(mne,"AD")==0){
		return "110";
	}else if (strcmp(mne,"AMD")==0){
		return "111";
	}else{
		printf("error : '%s' is no DEST instruction",mne);
	}
	return NULL;
}

char *__comp(char *mne){
	/* 	a = 0		*/
	if (strcmp(mne,"0")==0){
		return "101010";
	}else if (strcmp(mne,"1")==0){
		return "111111";
	}else if (strcmp(mne,"-1")==0){
		return "111010";
	}else if (strcmp(mne,"D")==0){
		return "001100";
	}else if (strcmp(mne,"A")==0){
		return "110000";
	}else if (strcmp(mne,"!D")==0){
		return "001101";
	}else if (strcmp(mne,"!A")==0){
		return "110001";
	}else if (strcmp(mne,"-D")==0){
		return "001111";
	}else if (strcmp(mne,"-A")==0){
		return "110011";
	}else if (strcmp(mne,"D+1")==0){
		return "011111";
	}else if (strcmp(mne,"A+1")==0){
		return "110111";
	}else if (strcmp(mne,"D-1")==0){
		return "001110";
	}else if (strcmp(mne,"A-1")==0){
		return "110010";
	}else if (strcmp(mne,"D+A")==0){
		return "000010";
	}else if (strcmp(mne,"D-A")==0){
		return "010011";
	}else if (strcmp(mne,"A-D")==0){
		return "000111";
	}else if (strcmp(mne,"D&A")==0){
		return "000000";
	}else if (strcmp(mne,"D|A")==0){
		return "010101";
	/* 	a = 1		*/
	}else if (strcmp(mne,"M")==0){
		return "110000";
	}else if (strcmp(mne,"!M")==0){
		return "110001";
	}else if (strcmp(mne,"-M")==0){
		return "110011";
	}else if (strcmp(mne,"M+1")==0){
		return "110111";
	}else if (strcmp(mne,"M-1")==0){
		return "110010";
	}else if (strcmp(mne,"D+M")==0){
		return "000010";
	}else if (strcmp(mne,"D-M")==0){
		return "010011";
	}else if (strcmp(mne,"M-D")==0){
		return "000111";
	}else if (strcmp(mne,"D&M")==0){
		return "000000";
	}else if (strcmp(mne,"D|M")==0){
		return "010101";
	}else{
		printf("error : '%s' is no COMP instruction",mne);
	}
	return NULL;
}

char *__jump(char *mne){
	if (strcmp(mne,"NULL")==0 || strcmp(mne,"null")==0){
		return "000";
	}else if (strcmp(mne,"JGT")==0 || strcmp(mne,"jgt")==0){
		return "001";
	}else if (strcmp(mne,"JEQ")==0 || strcmp(mne,"jeq")==0){
		return "010";
	}else if (strcmp(mne,"JGE")==0 || strcmp(mne,"jge")==0){
		return "011";
	}else if (strcmp(mne,"JLT")==0 || strcmp(mne,"jlt")==0){
		return "100";
	}else if (strcmp(mne,"JNE")==0 || strcmp(mne,"jne")==0){
		return "101";
	}else if (strcmp(mne,"JLE")==0 || strcmp(mne,"jle")==0){
		return "110";
	}else if (strcmp(mne,"JMP")==0 || strcmp(mne,"jmp")==0){
		return "111";
	}else{
		printf("error : '%s' is no JUMP instruction",mne);
	}
	return NULL;
}
