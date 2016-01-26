//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #2
// FILE NAME: hw02vector.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the vector container class.
//---------------------------------------------

#include <iostream>
#include <stdlib.h>

#include "vector.h"

using namespace std;

int main(int argc, char* argv[])
{
	if( ((argc-1)%2!=0) || (argc==1) || (argc==3) )
	{
		cout << "Invalid argument list... atleast 4 arguments of type (int) are required..." << endl;
		return 1;
	}
	
	Vector<int> v1;
	for(int i=atoi(argv[1]); i<atoi(argv[2]); i++)
		v1.push_back(i);
	Vector<int> v2;
	for(int i=atoi(argv[3]); i<atoi(argv[4]); i++)
		v2.push_back(i);
	cout << "v1: {";
	for(Vector<int>::iterator it=v1.begin(); it!=v1.end(); it++)
		cout << *it << ",";
	cout << "}" << endl;
	cout << "v2: {";
	for(Vector<int>::iterator it=v2.begin(); it!=v2.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	bool equalsFound=false;
	for(Vector<int>::iterator it1=v1.begin(); it1!=v1.end(); it1++)
		for(Vector<int>::iterator it2=v2.begin(); it2!=v2.end(); it2++)
			if(*it1==*it2)
			{
				equalsFound=true;
				cout << "equal element in v1 and v2: " << *it1 << endl;
			}
	if(equalsFound==false)
		cout << "no equal elements found in v1 and v2." << endl;
	cout << endl;
	
	v1.push_back(-100);
	v2.push_back(-100);
	cout << "v1: {";
	for(Vector<int>::iterator it=v1.begin(); it!=v1.end(); it++)
		cout << *it << ",";
	cout << "}" << endl;
	cout << "v2: {";
	for(Vector<int>::iterator it=v2.begin(); it!=v2.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	Vector<int> v(v2);
	cout << "v: {";
	for(Vector<int>::iterator it=v.begin(); it!=v.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	for(Vector<int>::reverse_iterator it=v1.rbegin(); it!=v1.rend(); it++)
		v.insert(v.begin(),*it);
	cout << "v: {";
	for(Vector<int>::iterator it=v.begin(); it!=v.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	Vector<int>::iterator bit=v.begin();
	for(; (*bit!=-100) && (bit!=v.end()) ;bit++);
	v.erase(bit,v.end());
	cout << "v: {";
	for(Vector<int>::iterator it=v.begin(); it!=v.end(); it++)
		cout << *it << ",";
	cout << "}" << endl << endl;
	
	return 0;
}
