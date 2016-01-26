//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #1
// FILE NAME: string2.cc
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the string class.
//-----------------------------------------------

#include <string.h>
#include <exception>
#include <iostream>

using namespace std;

#include "string2.h"

//--------------------------------------------
// FUNCTION: string2
// default constructor
// PARAMETERS:
// no parameters...
//----------------------------------------------

string2::string2(void)
		: capacity_ (0) , size_ (0) , buffer_ (new char [0]), step_ (STEP)
{
}

//--------------------------------------------
// FUNCTION: string2
// copy constructor
// PARAMETERS:
// const string2& other - the string2 that should be copied
//----------------------------------------------

string2::string2 (const string2& other)
		: size_(other.size_), buffer_(new char[other.capacity_+1]), capacity_ (other.capacity_), step_ (STEP)
{
	for(unsigned int i=0;i<size_;i++) 
		buffer_[i]=other.buffer_[i];
	buffer_[size_]='\0'; //always put \0 at the end of the strings
}

//--------------------------------------------
// FUNCTION: string2
// constructor with parameter capacity
// PARAMETERS:
// int capacity - this is the capacity of the newly created object
//----------------------------------------------

string2::string2 (int capacity )
		: capacity_ ( capacity ) , size_ (0) , buffer_ (new char [ capacity +1]), step_ (STEP)
{
}

//--------------------------------------------
// FUNCTION: string2
// constructor with a string as an arugment
// PARAMETERS:
// const char* str - the string that should be contained into the newly created instance
//----------------------------------------------

string2::string2 (const char * str )
		: capacity_ (0) , size_ (0) , buffer_ (0), step_ (STEP)
{
	size_ = strlen ( str );
	capacity_ = size_ ;
	buffer_ =new char [ capacity_ +1];
	strcpy ( buffer_ , str );
	buffer_[capacity_+1]='\0'; //always put \0 at the end of the string
}

//--------------------------------------------
// FUNCTION: ~string2
// destructor (frees alocated memory)
// PARAMETERS:
// no parameters...
//----------------------------------------------

string2::~string2 () 
{
	delete [] buffer_ ;
}

//--------------------------------------------
// FUNCTION: size
// returns the size of the string contained in the instance
// PARAMETERS:
// no parameters
//----------------------------------------------

int string2::size() const
{
	return size_;
}

//--------------------------------------------
// FUNCTION: length
// returns the length of the string contained in the instance
// PARAMETERS:
// no parameters
//----------------------------------------------

int string2::length() const
{
	return size_; //we return size since size represents length...
}

//--------------------------------------------
// FUNCTION: capacity
// returns the capacity of the instance (max length without need of reallocation)
// PARAMETERS:
// no parameters
//----------------------------------------------

int string2::capacity() const
{
	return capacity_; //the amount of chars that the string could contain before reallocation
}

//--------------------------------------------
// FUNCTION: empty
// checks if the string contained in the instance is empty
// PARAMETERS:
// no parameters
//----------------------------------------------

bool string2::empty() const
{
	return size_==0;
}

//--------------------------------------------
// FUNCTION: clear
// clears the string inside the isntance
// PARAMETERS:
// no parameters
//----------------------------------------------

void string2::clear()
{
	size_=0;
}

//--------------------------------------------
// FUNCTION: operator[]
// returns a char from the string contained in the instance
// PARAMETERS:
// int index - the index of the element to be returned
//----------------------------------------------

char& string2::operator[](int index)
{
	return buffer_[index];
}

//--------------------------------------------
// FUNCTION: at
// returns a char from the string contained in the isntance if the index is in bounds
// PARAMETERS:
// int index - the index of the element to be returned
//----------------------------------------------

char& string2::at(int index)
{
	if((index<size_) && (index>=0))
		return buffer_[index];
	else
		throw std::exception();
}

//--------------------------------------------
// FUNCTION: operator<<
// the overloaded operator '<<'... for being able to pt the string of the instance in a stream
// PARAMETERS:
// ostream& out - the stream in which the string should be put
// const string2& str - the string that should be put into a stream
//----------------------------------------------

ostream& operator<<(ostream& out, const string2& str)
{
	out << str.buffer_;
	return out;
}

//--------------------------------------------
// FUNCTION: operator=
// the overloaded operator '='... for being able to assign one instance to another
// PARAMETERS:
// const string2& other - the other object that should be assigned to the one we are in
//----------------------------------------------

string2& string2::operator=(const string2& other)
{
	if(this!=&other) //if we are not trying to assign an instance to itself
	{
		delete [] buffer_;
		size_=other.size_;
		capacity_=other.capacity_;
		buffer_=new char[capacity_+1];
		for(unsigned int i=0;i<size_;i++) //going through all chars
		{
			buffer_[i]=other.buffer_[i];
		}
	}
	return *this;
}

//--------------------------------------------
// FUNCTION: append
// appends the string in the current instance
// PARAMETERS:
// const string2& other - the other object whose string should be copied
//----------------------------------------------

string2& string2::append(const string2& other)
{
	if((size_+other.size_)<=capacity_) //if we dont have to reallocate
	{
		unsigned int i;
		for(i=0; i<other.size_; i++)
		{
			buffer_[i+size_]=other.buffer_[i];
		}
		buffer_[i]='\0';
		size_+=other.size_;
	}
	else //if we have to reallocate
	{
		char *temp=new char[(capacity_+other.capacity_) + 1];
		unsigned int i;
		for(i=0; i<size_; i++) //copy all from the first object in the temp
			temp[i]=buffer_[i];
		delete [] buffer_; //free
		for(; i<(size_+other.size_); i++) //copy all from the second object in temp
			temp[i]=other.buffer_[i-size_];
		temp[i]='\0';
		buffer_=temp; //assign buffer temp
		
		//incrementing the 2 fields
		capacity_+=other.capacity_;
		size_+=other.size_;
	}
	return *this;
}

//--------------------------------------------
// FUNCTION: operator+=
// the overloaded operator '+='... for being able to append with this operator
// PARAMETERS:
// const string2& other - the other object whose string should be copied
//----------------------------------------------

string2& string2::operator+=(const string2& other)
{
	if((size_+other.size_)<=capacity_) //if we dont have to reallocate
	{
		unsigned int i;
		for(i=0; i<other.size_; i++)
		{
			buffer_[i+size_]=other.buffer_[i];
		}
		buffer_[i]='\0';
		size_+=other.size_;
	}
	else //if we have to reallocate
	{
		char *temp=new char[(capacity_+other.capacity_) + 1];
		unsigned int i;
		for(i=0; i<size_; i++) //copy all from the first object in the temp
			temp[i]=buffer_[i];
		delete [] buffer_;
		for(; i<(size_+other.size_); i++) //copy all from the second object in temp
			temp[i]=other.buffer_[i-size_];
		temp[i]='\0';
		buffer_=temp;//assign buffer temp
		
		//incrementing the 2 fields
		capacity_+=other.capacity_;
		size_+=other.size_;
	}
	return *this;
}

//--------------------------------------------
// FUNCTION: push_back
// puts a char at the end of the string of the current isntance
// PARAMETERS:
// char ch - the char that should be put
//----------------------------------------------

void string2::push_back(char ch)
{
	if(size_<capacity_) //if we dont have to reallocate
	{
		buffer_[size_++]=ch;
		buffer_[size_]='\0'; //always put \0 at the end
	}
	else //if we ahve to reallocate
	{
		//determining the size of the allocated piece of memory
		int allocationSize=0;
		if(capacity_!=0)
			allocationSize=(capacity_*step_) + 1;
		else
			allocationSize=2;
		char *temp=new char[allocationSize];
		unsigned int i;
		for(i=0; i<size_; i++) //copying all in the temp
			temp[i]=buffer_[i];
		delete [] buffer_;
		temp[i]=ch; //adding the char
		temp[i+1]='\0'; //adding the special symbol
		buffer_=temp;
		
		//incrementation of fields
		if(capacity_!=0)
			capacity_*=step_;
		else
			capacity_++;
		size_++;
	}
}

//--------------------------------------------
// FUNCTION: operator+
// the overloaded operator '+'... for being able to concatenate strings
// PARAMETERS:
// const string2& other - the other string that should be concatenated to the current
//----------------------------------------------

string2 string2::operator+(const string2& other)
{
	string2 out(*this);
	out.append(other);
	return out;
}

//--------------------------------------------
// FUNCTION: operator==
// the overloaded operator '=='... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator ==( const string2 & other )
{
	int result=strcmp(this->buffer_, other.buffer_);
	if (result==0)
		return true;
	else
		return false;
}

//--------------------------------------------
// FUNCTION: operator!=
// the overloaded operator '!='... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator !=( const string2 & other )
{
	if (strcmp(this->buffer_, other.buffer_)==0)
		return false;
	else
		return true;
}

//--------------------------------------------
// FUNCTION: operator<
// the overloaded operator '<'... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator <( const string2 & other )
{
	if (strcmp(this->buffer_, other.buffer_)<0)
		return true;
	else
		return false;
}

//--------------------------------------------
// FUNCTION: operator>
// the overloaded operator '>'... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator >( const string2 & other )
{
	if (strcmp(this->buffer_, other.buffer_)>0)
		return true;
	else
		return false;
}

//--------------------------------------------
// FUNCTION: operator<=
// the overloaded operator '<='... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator <=( const string2 & other )
{
	int result=strcmp(this->buffer_, other.buffer_); //here we need a variable to save the result in
	if ((result<0) || (result==0))
		return true;
	else
		return false;
}

//--------------------------------------------
// FUNCTION: operator>=
// the overloaded operator '>='... for being able to compare the 2 strings of the 2 objects
// PARAMETERS:
// const string2& other - the second instance which's string should be compared
//----------------------------------------------

bool string2::operator >=( const string2 & other )
{
	int result=strcmp(this->buffer_, other.buffer_); //here we need a variable to save the result in
	if ((result>0) || (result==0))
		return true;
	else
		return false;
}

