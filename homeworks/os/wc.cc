//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #2
// FILE NAME: wc.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the main functionality of the UNIX
// program "wc". 
//---------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct counted
{
	counted() //this is the default constructor which initializes all parts ot the struct with '0'...
		: chars(0), words(0), lines(0)
	{}
	int chars;
	int words;
	int lines;
};

//--------------------------------------------
// FUNCTION: count
// The purpose of this function is to count chars, words and lines in a file and make a statistic
// (this here is only the prototype (declaration) of the real function)
// PARAMETERS:
// int cflag, int wflag, int lflag, counted& results, FILE* SOURCE
// The three integers are flags and are used to indicate which parts of the statistic should be shown.
// The 4-th parameter is a struct of type 'counted' passed by reference so that we could update
// the final statistics. SOURCE is a file stream from which we read.
//----------------------------------------------

void count(int, int, int, counted&, FILE*);

int main(int argc, char** argv)
{
	int c;
	int cflag=0, wflag=0, lflag=0; //these are the flags for all three available outcomes from the options...
	while (1)
	{
	    static struct option long_options[] =
	       {
		  /* These options don't set a flag.
	   	  We distinguish them by their indices. */
		  {"bytes",           no_argument,                 0, 'c'},
		  {"words",        no_argument,                 0, 'w'},
		  {"lines",        no_argument, 0, 'l'},
		  {0, 0, 0, 0}
	       };
	    /* getopt_long stores the option index here. */
	    int option_index = 0;
	    c = getopt_long (argc, argv, "cwl", long_options, &option_index);
	    /* Detect the end of the options. */
	    if (c == -1)
	       break;
	    switch (c)
	       {
	       case 0:
		  /* If this option set a flag, do nothing else now. */
		  if (long_options[option_index].flag != 0)
		     break;
		        fprintf (stdout,"option %s", long_options[option_index].name);
		        if (optarg)
		           fprintf (stdout," with arg %s", optarg);
		        fprintf (stdout,"\n");
		        break;
		    case 'c':
		    	cflag=1;
		        break;
		    case 'w':
		    	wflag=1;
		        break;
		    case 'l':
		    	lflag=1;
		        break;
		    case '?':
		        /* getopt_long already printed an error message. */
		        fprintf(stderr, "Try `wc --help' for more information.\n");
		        return 1;
		        break;
		    default:
		        return 1;
		}
	}
	    if((wflag==0) && (cflag==0) && (lflag==0)) //if no flag has been set, all are set to 1
	    {
		    wflag=1;
		    cflag=1;
		    lflag=1;
	    }
	    counted total; //the final results of all the counting
	    /* Use any remaining command-line arguments (not options). */
	    
	    //optind stores the index of the next non-option string in argv[]
	    if (optind < argc)
	    {
	    	int loop_counter=0; //to distinguish whether we need to show the total or not...
		   while (optind < argc)
		   {
		     if ( (argv[optind][0]=='-') && (argv[optind][1]=='\0') )
			{
				count(cflag,wflag,lflag,total,stdin);
				fprintf(stdout, " -\n");
				optind++;
				loop_counter++;
			}
		     else
		     {
			FILE* tmpFile = fopen( argv[optind], "r");
			if (tmpFile!=NULL)
			{
				count(cflag,wflag,lflag,total,tmpFile);
				fprintf(stdout, " %s\n",argv[optind]);
				fclose(tmpFile);
			}
			else
			{
				//printing the error to stderr
				fputs("wc: ", stderr);
				perror(argv[optind]);
			}
		     optind++;
		     loop_counter++;
		     }
		   }
		   
		   if(loop_counter!=1) //printing the final results only if there are atleast 2 statistics to be considered...
		   {
		   	if(lflag==1)
		   		fprintf(stdout, "%8d",total.lines);
		   	if(wflag==1)
		   		fprintf(stdout, "%8d",total.words);
		   	if(cflag==1)
		   		fprintf(stdout, "%8d total\n",total.chars);
		   }
	    }
	    else
	    {
	    	count(cflag,wflag,lflag,total,stdin);
	    	fprintf(stdout, "\n");
	    }
	return 0;
}

//--------------------------------------------
// FUNCTION: count
// The purpose of this function is to count chars, words and lines in a file and make a statistic
// PARAMETERS:
// int cflag, int wflag, int lflag, counted& results, FILE* SOURCE
// The three integers are flags and are used to indicate which parts of the statistic should be shown.
// The 4-th parameter is a struct of type 'counted' passed by reference so that we could update
// the final statistics. SOURCE is a file stream from which we read.
//----------------------------------------------

void count(int cflag, int wflag, int lflag, counted& results, FILE* SOURCE)
{
	counted current;
    	ssize_t char_current;
    	size_t size=0;
	char *line=NULL;
	while((char_current=getline(&line, &size, SOURCE))!=-1) //counting loop
	{
		current.chars+=char_current;
		current.lines++;
		bool inword=false;
		for(int i=0; i<char_current; i++)
		{
			if ((line[i]!=' ') && (line[i]!='\t') && (line[i]!='\n'))
			{
				if(inword==false)
				{
					current.words++;
					inword=true;
				}
			}
			else
			inword=false;
		}
	}
	//print the current results
	if(lflag==1)
	   	fprintf(stdout, "%8d",current.lines);
	if(wflag==1)
		fprintf(stdout, "%8d",current.words);
	if(cflag==1)
		fprintf(stdout, "%8d",current.chars);
	
	//update the final sum
	results.chars+=current.chars;
	results.words+=current.words;
	results.lines+=current.lines;
}

