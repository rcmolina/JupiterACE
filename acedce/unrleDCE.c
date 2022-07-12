#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
	int realchr = -1;
	int chr;
	int cnt = 0;

	FILE* infile;
	FILE* outfile;
	char* outfilename;

	outfilename = malloc(strlen(argv[1])+5);
	strcpy(outfilename, argv[1]);
	
	char *lastdotptr= strrchr(outfilename,'.');
	*lastdotptr=0;	   
	
	strcat(outfilename, ".dce");
	infile = fopen(argv[1], "rb");
	outfile = fopen(outfilename,"wb");

	if (infile == NULL || outfile == NULL){
		perror("ace: file could not be opened.\n");
		return -1;
	}

	chr = fgetc(infile);
	while(chr != EOF){
		if (chr == 0xED){
			int i;
			//realchr = fgetc(infile);
			cnt = fgetc(infile);
			realchr = fgetc(infile);
						
			for(i=0; i<cnt; i++){
				fputc(realchr, outfile);
			}
		}
		else{
			fputc(chr, outfile);
		}
		chr = fgetc(infile);
	}

	fclose(infile);
	fclose(outfile);

	return 0;
}	

