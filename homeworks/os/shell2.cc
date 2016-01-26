//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #5
// FILE NAME: shell2.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates a command interpreter with piping.
//---------------------------------------------

struct Job 
{
    char * command ;
    char ** argv ;
    int stdin ;
    int stdout ;
};

#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

using namespace std;

//--------------------------------------------
// FUNCTION: parse_cmdline
// предназначение на функцията
// PARAMETERS:
// const string& cmdline - this is the string from the 
// standart input which should be transformed into
// a valid array of strings (parameters)
//----------------------------------------------

char** parse_cmdline(const string& cmdline)
{
		istringstream in(cmdline);
		vector<string> argv;		
		while(in) 
		{
			string arg;
			in >> arg; //we use streams so that we dont have to worry about separating the words
			if(!in)
				break;
			argv.push_back(arg);
		}
		char** c_argv= new char*[argv.size()+1]; //make the array of strings bigger so that we add 0 to the last entry.
		for(int i=0; i<argv.size(); i++) //copying.
		{
			c_argv[i]=strdup(argv[i].c_str());
		}
		c_argv[argv.size()]=0; //the last argument is always 0.
	return c_argv;
}

int main(int argc, char** argv) 
{
	while(cin!= NULL) //the loop shall continue as long as getline doesn't crash (meaning until EOF is reached).
	{
		cout << "Shell: ";
		string cmdline;
		getline(cin,cmdline);
		if(cin==NULL) //if cin has crashed we want to quit the program so that we don't try to parse the string read from cin and get an error.
			return 1;
		
		//variables (names speak for themselves)
		int i2=0;
		string temp;
		int counter=0;
		bool havePipe=false;
		Job jobs[2];
		string cmdlines[2]; //the 2 command lines for the 2 programs (if they are 2, or only the first is used)
		char** c_argvs[2]; //the 2 arrays of arguments for the 2 programs(both are used only when we have a pipe)
		string inputFilenames[2];
		string outputFilenames[2];
		//end
		
		//TO SEE IF THERE IS A PIPE
		size_t pipeSymbolPos = cmdline.find_first_of('|');
		if(pipeSymbolPos!=string::npos) //if the symbol '|' has been found
		{
			havePipe=true;
			//here we make the string of arguments for the first program
			cmdlines[0].append(cmdline, 0, pipeSymbolPos); 
			//here we make the string of arguments for the second program
			cmdlines[1].append(cmdline, pipeSymbolPos+1, cmdline.size() - pipeSymbolPos+1);
		}
		else
		{
			//here we make the string of arguments for the only program
			cmdlines[0].append(cmdline, 0, cmdline.length());
			havePipe=false;
		}
		
		//HERE WE SEE WHAT FILENAMES ARE ASOCIATED WITH THE INPUT AND OUTPUT OF THE 2 PROGRAMS
		for(i2=0; i2<2; i2++) //we loop only twice since we can have max 1 pipe...
		{
			if(i2==1 && havePipe==false)
				break;
			//FOR INPUT REDIRECTION OF PROGRAM 1/2   (DOESN'T MATTER SINCE WE ARE IN A LOOP)
			size_t inputSymbolPos = cmdlines[i2].find_first_of('<');
			if(inputSymbolPos!=string::npos) //if a match has been found
			{
				//get filename after '<' for input source
				temp.assign(cmdlines[i2], inputSymbolPos+1, cmdlines[i2].length()-inputSymbolPos-1);
				for(int i=0; i<temp.length(); i++)
				{
					//counter represents the number of all symbols that should be representing the input filename
					counter++; 
					if(!isspace(temp[i]))
						inputFilenames[i2]+=temp[i];
					else
						if(inputFilenames[i2].length()>0) //break if we have finished a word
							break;
				}
				cmdlines[i2].erase(inputSymbolPos, counter+1);//delete the whole section('<filename')
				counter=0;
				//end
			
				//set default input from a file(word) after '<'
				jobs[i2].stdin = open (inputFilenames[i2].c_str(),O_RDONLY | O_CREAT,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
				//end
			}
			else
			{
				//set default input from STDIN
				jobs[i2].stdin=0;
				//end
			}
		
			//FOR OUTPUT REDIRECTION OF PROGRAM 1/2   (DOESN'T MATTER SINCE WE ARE IN A LOOP)
			size_t outputSymbolPos = cmdlines[i2].find_first_of('>');
			if(outputSymbolPos!=string::npos) //if a match has been found
			{
				//get filename after '>' for output destination
				temp.assign(cmdlines[i2], outputSymbolPos+1, cmdlines[i2].length()-outputSymbolPos-1);
				for(int i=0; i<temp.length(); i++)
				{
					//counter represents the number of all symbols that should be representing the output filename
					counter++;
					if(!isspace(temp[i]))
						outputFilenames[i2]+=temp[i];
					else
						if(outputFilenames[i2].length()>0) //break if we have finished a word
							break;
				}
				cmdlines[i2].erase(outputSymbolPos,counter+1);//delete the whole section('>filename')
				counter=0;
				//end
			
				//set default output to a file(word) after '<'
				jobs[i2].stdout = open (outputFilenames[i2].c_str(),O_WRONLY | O_CREAT | O_TRUNC,
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
				
				//end
			}
			else
			{
				//set default output to STDOUT
				jobs[i2].stdout=1;
				//end
			}
		}
		
		if(havePipe==false) //only one job is initialised if there are no pipes
		{
			//making of list of arguments
			c_argvs[0]=parse_cmdline(cmdlines[0]);
			//end
			
			//job initialisation
			jobs[0].command=c_argvs[0][0];
			jobs[0].argv=c_argvs[0];
			//end
		}
		else
		{
			//make the 2 lists of arguments
			c_argvs[0]=parse_cmdline(cmdlines[0]);
			c_argvs[1]=parse_cmdline(cmdlines[1]);
			//end
		
			//make the 2 jobs (here we make the stdin and stdout fields again because pipes have higher priority to ordinary input/output redirection (I made it this way... thought it's more logical...))
			
			jobs[0].command=c_argvs[0][0];
			jobs[0].argv=c_argvs[0];
			
			jobs[1].command=c_argvs[1][0];
			jobs[1].argv=c_argvs[1];
			//end of initialization of jobs
		}
		pid_t pid = fork();
		if (pid==-1) 
		{
			//if fork was unsuccessful (usually when there are too much running processes).
			perror( "Can't fork");
			exit(1);
		} 
		else 
			if (pid==0) //if fork was successful and we are inside the child process
			{
				if ((havePipe==true) && (jobs[1].command[0]!='0')) // if second program has a name
				{
					struct stat myStat;
					if(stat(jobs[0].command, &myStat)!=-1)
					{
						if (S_ISDIR (myStat.st_mode)) //if the name of the first program to be executed is actually a directory.
						{
							fprintf(stdout, "%s is a directory.\n",jobs[0].command);
						}
						else
						{
							int pd[2];
							if(pipe(pd)<0)
							{
								perror("cant create pipe");
								exit(10);
							}	
					
							pid_t pid1=fork();
							if(pid1<0)
							{
								perror("cant fork 1");
								exit(1);
							}
							else
								if(pid1==0)
								{
									// exec first program
							
									dup2(jobs[0].stdin,0);
									close(pd[0]);
									dup2(pd[1],STDOUT_FILENO);
									close(pd[1]);
									if (execv(jobs[0].command, jobs[0].argv)<0)
									{
										perror("cant exec 1");
										exit(4);
									}
								}
							pid_t pid2=fork();
							if (pid1<0)
							{
								perror("cant fork 2");
								exit(2);
							}
							else
								if(pid2==0)
								{
									//exec second program
			
									close(pd[1]);
									dup2(pd[0],STDIN_FILENO);
									dup2(jobs[1].stdout,1);
									close(pd[0]);
									if (execv(jobs[1].command, jobs[1].argv)<0)
									{
										perror("cant exec 1");
										exit(4);
									}
								}
							close(pd[0]);
							close(pd[1]);
	
							int status;
							waitpid(pid1, &status, 0);
							waitpid(pid2, &status, 0);
						}
					}
					else
					{
						fprintf(stdout, "%s: no such file or directory.\n", jobs[0].command);
					}
					exit(0); //end the child process in which the piping had taken place...
				}
				else
				{
					struct stat myStat;
					if(stat(jobs[0].command, &myStat)!=-1)
					{
						if (S_ISDIR (myStat.st_mode)) //if the name of the program to be executed is actually a directory.
						{
							fprintf(stdout, "%s is a directory.\n",jobs[0].command);
						}
						else
						{
							if((dup2(jobs[0].stdout,1))<0)
								cout << "problem1";
							if((dup2(jobs[0].stdin,0))<0)
								cout << "problem0";
						
							if(execv(jobs[0].command,jobs[0].argv)==-1) //here we exec the program c_argv[0] inside the child process.
								perror(jobs[0].command); //to print the error if exec crashes.
							}	
					}
					else
					{
						fprintf(stdout, "%s: no such file or directory.\n", jobs[0].command);
					}
					exit(3);
				}		
			} 
			else 
			{
				//waiting for the child process to finish its job.
				int status=0;	
				if (waitpid(pid,&status,0)==-1)
				{
					perror("can't wait...");
					exit(2);
				}
			}
	}
	return 0;
}
