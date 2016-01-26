//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #3
// FILE NAME: hw03list.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the list container class.
//---------------------------------------------

#include <iostream>
#include <stdlib.h>

using namespace std;

#include "list.h"

int main(int argc, char*argv[])
{
	if( ((argc-1)%2!=0) || (argc==1) || (argc==3) )
	{
		cout << "Invalid argument list... atleast 4 arguments of type (int) are required..." << endl;
		return 1;
	}
	
	List<int> l1;
	for(int i=atoi(argv[1]); i<atoi(argv[2]); i++)
		l1.push_back(i);
	List<int> l2;
	for(int i=atoi(argv[3]); i<atoi(argv[4]); i++)
		l2.push_back(i);
	cout << "l1: {";
	for(List<int>::iterator it=l1.begin(); it!=l1.end(); it++)
		cout << *it << ",";
	cout << "}" << endl;
	cout << "l2: {";
	for(List<int>::iterator it=l2.begin(); it!=l2.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	bool equalsFound=false;
	for(List<int>::iterator it1=l1.begin(); it1!=l1.end(); it1++)
		for(List<int>::iterator it2=l2.begin(); it2!=l2.end(); it2++)
			if(*it1==*it2)
			{
				equalsFound=true;
				cout << "equal element in l1 and l2: " << *it1 << endl;
			}
	if(equalsFound==false)
		cout << "no equal elements found in l1 and l2." << endl;
	cout << endl;
	
	l1.push_back(-100);
	l2.push_back(-100);
	cout << "l1: {";
	for(List<int>::iterator it=l1.begin(); it!=l1.end(); it++)
		cout << *it << ",";
	cout << "}" << endl;
	cout << "l2: {";
	for(List<int>::iterator it=l2.begin(); it!=l2.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	List<int> l(l2);
	cout << "l: {";
	for(List<int>::iterator it=l.begin(); it!=l.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	for(List<int>::reverse_iterator it=l1.rbegin(); it!=l1.rend(); it++)
		l.insert(l.begin(),*it);
	cout << "l: {";
	for(List<int>::iterator it=l.begin(); it!=l.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	List<int>::iterator bit=l.begin();
	for(; (*bit!=-100) && (bit!=l.end()) ;bit++);
	l.erase(bit,l.end());
	cout << "v: {";
	for(List<int>::iterator it=l.begin(); it!=l.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	return 0;
}

