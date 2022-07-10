/*
 * C Program to Convert the Content of File to LowerCase
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h> // warning for malloc
 
//int to_lower_file(FILE *);
int change_file(FILE *, int option);
 
int main(int argc, char * argv[])
{
    int op = -1;
    char ch;
    FILE *fp;
/*
    if (fp = fopen(argv[1], "r+b"))
    {
        printf("FILE has been opened..!!!\n");
        op = to_lower_file(fp);
        printf(" %d \n", op);
        fclose(fp);
    }
    else
    {
        perror("Error Occured");
        printf(" %d\n ", op);
    }
*/
	int i;
	int option;
	//printf("%d", argc);
	if ((argc > 3) || (argc == 1)) {

		printf("%s [-l|-u|-s] finename \n",argv[0]);
		printf("-l : convert to lower case \n");
		printf("-u : convert to upper case \n");
		printf("-s : switch between lowercase and uppercase \n");	 	 	 	 
		return 1;
	
	} else if (argc == 3) {	   
		if (strcmp(argv[1], "-l") == 0) option = 0;
		else if (strcmp(argv[1], "-u") == 0) option = 1;
		else if (strcmp(argv[1], "-s") == 0) option = 2;
		else option = 0;
		
	 	if (fp = fopen(argv[2], "r+b")) {
	        printf("FILE has been opened..!!!\n");
	        op = change_file(fp, option);
	        printf(" %d \n", op);
	        fclose(fp);
	    }
	    else
	    {
	        perror("Error Occured");
	        printf(" %d\n ", op);
	    }
		
	} else if (argc == 2) {
		option = 0;
		//printf("%d", argc);
	 	if (fp = fopen(argv[1], "r+b")) {
	        printf("FILE has been opened..!!!\n");
	        op = change_file(fp, option);
	        printf(" %d \n", op);
	        fclose(fp);
	    }
	    else
	    {
	        perror("Error Occured");
	        printf(" %d\n ", op);
	    }	   	   
		
	}
	
	
}

/* 
int to_lower_file(FILE *f)
{
	long int pos;
    char ch;
	fseek (f,0,SEEK_END);
	long int lastpos = ftell(f);
	fseek (f,0,SEEK_SET);
	
    while (ftell(f) < lastpos) {
		ch = fgetc(f); 
			//fread(&ch,1,1,f);	     
			//printf("%c ",ch);
		if (isupper(ch)) ch = tolower(ch);
				//printf("%c\n",ch);
				//system("pause");
				//if (islower(ch)) ch = toupper(ch);
				//printf("%d\n",ftell(f));
	    fseek(f, -1L, SEEK_CUR);
				//printf("%d\n",ftell(f));
	    fputc(ch, f);
				//fwrite(&ch,1,1,f);
				//printf("before put %d\n",ftell(f));
		fseek(f, 0, SEEK_CUR);
				//printf("after put %d\n",ftell(f));
    }
    return 0;
}
*/

int change_file(FILE *f, int opt)
{
	#define BUFFER_SIZE 1024
	long int pos;
    char ch;
	char* buf = (char*) malloc (sizeof(char)* BUFFER_SIZE); //1024 is buffer size
	fseek (f,0,SEEK_END);
	long int lastpos = ftell(f);
	long int lastBlockSize;
	fseek (f,0,SEEK_SET);
	long int i;
	
    while (ftell(f) < lastpos) {
	
		if ((ftell(f) + BUFFER_SIZE) < lastpos) {
			fread(buf, sizeof(char), BUFFER_SIZE, f);
			//for (i=0;i<BUFFER_SIZE;i++) buf[i]=tolower(buf[i]);
			if (opt == 0) for (i=0;i<BUFFER_SIZE;i++) buf[i]=tolower(buf[i]);
			else if (opt == 1) for (i=0;i<BUFFER_SIZE;i++) buf[i]=toupper(buf[i]);
			else if (opt == 2) 
				for (i=0;i<BUFFER_SIZE;i++) {
					if (islower(buf[i])) buf[i]=toupper(buf[i]);
					else buf[i]=tolower(buf[i]);
				}
			
			fseek(f, -BUFFER_SIZE, SEEK_CUR);
			fwrite(buf, sizeof(char), BUFFER_SIZE, f);
			fseek(f, 0, SEEK_CUR);
		}
		else {
			lastBlockSize = lastpos-ftell(f);
			fread(buf, sizeof(char), lastBlockSize, f);
			//for (i=0;i<lastBlockSize;i++) buf[i]=tolower(buf[i]);
			if (opt == 0) for (i=0;i<lastBlockSize;i++) buf[i]=tolower(buf[i]);
			else if (opt == 1) for (i=0;i<lastBlockSize;i++) buf[i]=toupper(buf[i]);
			else if (opt == 2) 
				for (i=0;i<lastBlockSize;i++) {
					if (islower(buf[i])) buf[i]=toupper(buf[i]);
					else buf[i]=tolower(buf[i]);
				}	   	   	   
			
			
			fseek(f, -lastBlockSize, SEEK_CUR);
			fwrite(buf, sizeof(char), lastBlockSize, f);
			fseek(f, 0, SEEK_CUR);	   	   	   
		}
		
    }
	free(buf);
    return 0;
}

