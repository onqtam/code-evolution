//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #3
// FILE NAME: ls.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the main functionality of the UNIX
// program "ls". 
//---------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <iomanip>

void prepInfo(struct stat&, char*);
void dirFunc(const char str[], int flag, int multi_flag); //prototype

int main(int argc, char* argv[])
{
	//flag for -l
	int lflag = 0;
	//here we get the options using getopt()...
	int index;
	int c;
	opterr = 0;
	while ((c = getopt (argc, argv, "l")) != -1)
		  switch (c)
		  {
		    case 'l':
		       lflag = 1;
		       break;
		    case '?':
			 fprintf (stderr, "./ls: invalid option -- '%c'\n", optopt);
		       return 1;
		    default:
		       return 1;
		  }
	
	int multi_flag=0;
	//optind stores the index of the next non-option argv[] argument 
	if (argc-optind>1) //this shows wether directory/file names should be printed above the results (if more than 1 dir/file   then yes)
		multi_flag=1;
	if(argc==optind)
		dirFunc("./",lflag,multi_flag); //if no arguments are passed (options do not count)
	else
		for (index = optind; index < argc; index++) 
		{
			if( (argv[index][0]=='/') || (argv[index][0]=='.') ) //if the argument is a directori not starting from the current
				dirFunc(argv[index], lflag, multi_flag);
			else
			{
				char temp[256];
				sprintf(temp, "./%s", argv[index]); //we add the argument after the reference to the current dir (./)
				dirFunc(temp, lflag, multi_flag);
			}		
			fprintf(stdout, "\n");
		}
	return 0;	
}

//--------------------------------------------
// FUNCTION: dirFunc
// This function opens directories and prints their contents
// to the screen. Also can print advanced information about files.
// PARAMETERS:
// char str[]     -   the path (+name) of the directory(file)
// int flag       -   a flag showing wether advanced info mode should be on or not.
// int multi_flag -   a flag showing wether file namesshould be printed if more than 2 things have to be printed
//----------------------------------------------

void dirFunc(const char str[], int flag, int multi_flag)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir(str);
	if (dp != NULL) //if directory does not exist, str is a filename or the dir cant be opened
	{
		if(multi_flag) //to print the name of the dir (or not)
			fprintf(stdout, "%s:\n",str);
		struct stat myStat;
		struct tm* timeinfo;
		if(flag==1) //we count the blocks here... no output is done (except for the total)
		{
			int block_counter=0;
			while (ep = readdir (dp))
			{
				char temp[256];
				sprintf(temp, "%s/%s", str, ep->d_name);
				lstat(temp, &myStat);
				
				if(ep->d_name[0]!='.') //to ignore hidden files
					block_counter+=myStat.st_blocks/2;
				//I divide by 2 because the original ls works with --block-size=1024 and myStat.st_blocks is the number of 512 byte blocks...  meaning twice as much blocks
			}
			(void) closedir (dp);
			dp = opendir (str); //we open the dir as nothing has happened
			fprintf(stdout, "total %d\n", block_counter); //printing total blocks in the dir
		}
		while (ep = readdir (dp))
		{
			if(ep->d_name[0]!='.') //if file is not hidden (hidden file names begin with '.')
				if(flag==0)
				{
					fprintf(stdout, "%s\n",ep->d_name);
				}
				else //if flag for advanced options is set...
				{
					struct stat myStat;
					char temp[256];
					sprintf(temp, "%s/%s", str, ep->d_name);
					lstat(temp,&myStat);
					prepInfo(myStat,ep->d_name);
				}
		}
	     	(void) closedir (dp);
	}
	else
	{
		if(errno==20) //existing file name, not directory name... (shall be printed)
		{
			if(flag==0)
				fprintf(stdout, "%s\n\n", str);
			else //if flag for advanced options is set...
			{
				struct stat myStat;
				lstat(str,&myStat);
				prepInfo(myStat,ep->d_name);
			}
		}
		else
		{
			char errorstr[256];
			sprintf(errorstr, "ls: cannot access %s",str); //if a non-existing folder/file
			perror (errorstr);
		}
	}
}

void prepInfo(struct stat& myStat, char* name)
{
	int Perms[]={S_IREAD, S_IWRITE, S_IEXEC, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	char FinalPermissions[]={'-','r','w','x','r','w','x','r','w','\0'};
	struct tm* timeinfo;
	struct passwd * User= getpwuid(myStat.st_uid);
	struct group* Group=getgrgid(myStat.st_gid);
	//this here is for the first of the permitions
	mode_t IntPerms=myStat.st_mode;
	if S_ISREG(myStat.st_mode)
		FinalPermissions[0]='-';
	else
        	if S_ISDIR(myStat.st_mode)
	                FinalPermissions[0]='d';
	        else
		        if S_ISCHR(myStat.st_mode)
		                FinalPermissions[0]='c';
		        else
			        if S_ISBLK(myStat.st_mode)
			                FinalPermissions[0]='b';
			        else
				        if S_ISFIFO(myStat.st_mode)
				                FinalPermissions[0]='f';
	for(int i=0; i<9; i++) //in this loop we check the bytes with a mask   byte by byte
	{
		if (!(IntPerms&Perms[i]))
			FinalPermissions[i+1]='-'; //[i+1] because [0] is already set
	}
	timeinfo = localtime ( &myStat.st_mtime ); //for convertion from seconds from 1970 to a more readable date.
	fprintf(stdout, "%10s %8s %8s %d %6d %4d-%2d-%2d %2d:%2d %-s\n", FinalPermissions, User->pw_name, Group->gr_name, myStat.st_nlink, (int)myStat.st_size, timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, name);
}

