#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SEQ(file, cnt, byte)\
	do{	\
		fputc(0xED, file);\
		fputc(cnt, file);\
		fputc(byte, file);\
	}while(0)

int main(int argc, char* argv[]){
	int pre = -1;
	int chr;
	int cnt = 0;

	FILE* infile;
	FILE* outfile;
	char* outfilename;

	if (argc < 2){
		printf("usage: %s filename\n", argv[0]);
		return -1;
	}

	outfilename = malloc(strlen(argv[1])+5);
	strcpy(outfilename, argv[1]);

	char *lastdotptr= strrchr(outfilename,'.');
	*lastdotptr=0;	  
	
	strcat(outfilename, ".ace");
	infile = fopen(argv[1], "rb");
	outfile = fopen(outfilename,"wb");

	if (infile == NULL || outfile == NULL){
		perror("dce: file could not be opened.\n");
		return -1;
	}

	chr = fgetc(infile);
	while(chr != EOF){
		if (chr == pre){
			if (cnt < 240)
				cnt++;
			else{
				SEQ(outfile, cnt, pre);
				cnt = 1;
			}
		}
		else{
			if (pre == 0xED){
				SEQ(outfile, cnt, pre);
			}
			else{
				if (cnt <= 3){
					int i;
					for (i=0; i<cnt; i++){
						fputc(pre, outfile);
					}
				}
				else{
					SEQ(outfile, cnt, pre);
				}
			}
			pre = chr;
			cnt = 1;
		}
		chr = fgetc(infile);
	}
	SEQ(outfile, cnt, pre);

	fclose(infile);
	fclose(outfile);

	return 0;
}	

