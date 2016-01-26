//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #1
// FILE NAME: hw01string.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the string class.
//---------------------------------------------

#include <iostream>
#include <string>

using namespace std;

#include "string2.h"

int main(int argc, char* argv[])
{
	//this program works only if there are atleast 2 arguments passed
	if(argc==1)
	{
		cout << "No arguments passed... exiting..." << endl;
		return 1;
	}
	if(argc==2)
	{
		cout << "Only one  argument passed... exiting..." << endl;
		return 1;
	}
	
	//initialisation
	string2 str;
	string2 str1(argv[1]);
	string2 str2(argv[2]);
	string2::iterator it=str1.begin();
	int number_of_spaces=0;
	
	//output the strings
	cout << "string 1: <" << str1 << ">" << endl;
	cout << "string 2: <" << str2 << ">" << endl;
	
	//output their length
	cout << "string 1 length:" << str1.length() << endl;
	cout << "string 2 length:" << str2.length() << endl;
	
	//output the number of spaces in them
	number_of_spaces=0;
	for(it=str1.begin(); it!=str1.end(); it++)
		if((*it)==' ')
			number_of_spaces++;
	cout << "string 1 spaces:" << number_of_spaces << endl;
	
	number_of_spaces=0;
	for(it=str2.begin(); it!=str2.end(); it++)
		if((*it)==' ')
			number_of_spaces++;
	cout << "string 2 spaces:" << number_of_spaces << endl;
	
	//comparison
	if(str1==str2)
		cout << "<" << str1 << "> is equal to <" << str2 << ">" << endl;
	else
	if(str1>str2)
		cout << "<" << str1 << "> is greater than <" << str2 << ">" << endl;
	else
	if(str1<str2)
		cout << "<" << str1 << "> is smaller than <" << str2 << ">" << endl;
	
	//adding a symbol at the back of the 2 strings
	str1.push_back('!');
	str2.push_back('!');
	cout << "string 1: <" << str1 << ">" << endl;
	cout << "string 2: <" << str2 << ">" << endl;
	
	//concatenating the 2 strings
	str=str1+str2;
	cout << "concatenation: <" << str << ">" << endl;
	
	//output the length of the result
	cout << "concatenation length:" << str.length() << endl;
	
	//output the number of spaces in the result
	number_of_spaces=0;
	for(it=str.begin(); it!=str.end(); it++)
		if((*it)==' ')
			number_of_spaces++;
	cout << "concatenation spaces:" << number_of_spaces << endl;
	
	return 0;
}

