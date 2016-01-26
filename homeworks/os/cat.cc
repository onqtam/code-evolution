//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #1
// FILE NAME: cat.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the main functionality of the UNIX
// program "cat". 
//---------------------------------------------

#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
	if (argc==1) // checks if there are no arguments (argv[0] always contains the name of the program and argc is atleast 1)...
	{
		size_t size=0;
		char *line=NULL;
		while(getline(&line, &size, stdin)!=-1)
			fputs(line, stdout);
		return 0;
	}
	
	for(int i=1; i<argc; i++) //going through all arguments...
	{
		if ( (argv[i][0]=='-') && (argv[i][1]=='\0') )
		{
			size_t size=0;
			char *line=NULL;
			while(getline(&line, &size, stdin)!=-1)
				fputs(line, stdout);
		}
		else
		{
			FILE* tmpFile = fopen( argv[i], "r");
			if (tmpFile!=NULL)
			{
				//printing the file to stdout...
				size_t size=0;
				char *line=NULL;
				while(getline(&line, &size, tmpFile)!=-1)
					fputs(line, stdout);
				fclose(tmpFile);
			}
			else
			{
				//printing the error to stderr
				fputs("cat: ", stderr);
				perror(argv[i]);
			}
		}
	}
	return 0;
}

