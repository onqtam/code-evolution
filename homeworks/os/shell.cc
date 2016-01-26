//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #4
// FILE NAME: shell.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates a command interpreter.
//---------------------------------------------

#include <sys/wait.h>
#include <sys/stat.h>
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
	while(cin!= NULL) //the loop shall continue as long as getline doesn't crash.
	{
		string cmdline;
		getline(cin,cmdline);
		if(cin==NULL) //if cin has crashed we want to quit the program so that we don't try to parse the string read from cin and get an error.
			return 1;
		char** c_argv=parse_cmdline(cmdline); //converting the string into an array of strings.
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
				struct stat myStat;
				if(stat(c_argv[0], &myStat)!=-1)
					if (S_ISDIR (myStat.st_mode)) //if the name of the program to be executed is actually a directory name.
					{
						fprintf(stdout, "%s is a directory.\n",c_argv[0]);
					}
					else //if the name of the program to be executed is an existing file.
					{
						if(execv(c_argv[0],c_argv)==-1) //here we exec the program c_argv[0] inside the child process.
							perror(c_argv[0]); //to print the error if exec crashes.
					}
				else
				{
					cout << "Not a valid file/dir name..." << endl;
				}
				exit(3);		
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
