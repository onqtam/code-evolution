//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #1
// FILE NAME: string2.h
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the string class.
//---------------------------------------------

#ifndef STRING2_HPP
#define STRING2_HPP

#define STEP 2

class string2
{
private:
	const unsigned int step_;
	int capacity_ ;
	int size_;
	char * buffer_ ;
public :
	// the comments explaining what these methods do are located in the source file
	
	string2 (void);
	string2 (const string2& other);
	string2 (int capacity );
	string2 (const char * str );
	~string2 ();
	
	int size() const;
	int length() const;
	int capacity() const;
	bool empty() const;
	void clear();
	char& operator[](int index);
	char& at(int index);
	
	friend ostream& operator<<(ostream& out, const string2& str);
	
	string2& operator=(const string2& other);
	
	string2& append(const string2& other);
	string2& operator+=(const string2& other);
	void push_back(char ch);
	string2 operator+(const string2& other);
	
	bool operator ==( const string2 & other );
	bool operator !=( const string2 & other );
	bool operator <( const string2 & other );
	bool operator >( const string2 & other );
	bool operator <=( const string2 & other );
	bool operator >=( const string2 & other );
	
	class iterator 
	{
		char* curr_;
		
		//--------------------------------------------
		// FUNCTION: iterator
		// constructor for the iterator class
		// PARAMETERS:
		// char* ptr - a char to be pointing at
		//----------------------------------------------
		
		iterator(char* ptr)
		: curr_(ptr)
		{}
		
	public:
		friend class string2;
		
		//--------------------------------------------
		// FUNCTION: operator==
		// the overloaded operator '++'... for being able to compare 2 instances
		// PARAMETERS:
		// const iterator& other - the other instance to be compared with
		//----------------------------------------------
		
		bool operator==(const iterator& other) const 
		{
			return curr_==other.curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator!=
		// the overloaded operator '*'... for being able to compare 2 instances
		// PARAMETERS:
		// const iterator& other - the other instance to be compared with
		//----------------------------------------------
		
		bool operator!=(const iterator& other) const 
		{
			return !operator==(other);
		}
		
		//--------------------------------------------
		// FUNCTION: operator*
		// the overloaded operator '*'... for being able to get the char which the iterator is pointing at
		// PARAMETERS:
		// no parameters
		//----------------------------------------------
		
		char& operator*() 
		{
			return *curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator++
		// the overloaded operator '++'... for being able to increment the iterator's position
		// PARAMETERS:
		// no parameters
		//----------------------------------------------
		
		iterator& operator++() 
		{
			curr_++;
			return *this;
		}

		//--------------------------------------------
		// FUNCTION: operator++
		// the overloaded operator '++'... for being able to increment the iterator's position
		// PARAMETERS:
		// int - don't know how to explain... but this is for ++i
		//----------------------------------------------
		
		iterator operator++(int) 
		{
			iterator res=*this;
			curr_++;
			return res;
		}
	};
	
	//--------------------------------------------
	// FUNCTION: begin
	// returns an iterator pointing at the begining of the object's string
	// PARAMETERS:
	// no parameters
	//----------------------------------------------

	iterator begin() 
	{
		return iterator(buffer_);
	}
	
	//--------------------------------------------
	// FUNCTION: end
	// returns an iterator pointing at the end of the object's string
	// PARAMETERS:
	// no parameters
	//----------------------------------------------
	
	iterator end() 
	{
		return iterator(buffer_+size_);
	}
};

//--------------------------------------------
// FUNCTION: operator<<
// the overloaded operator '<<'... for being able to pt the string of the instance in a stream
// PARAMETERS:
// ostream& out - the stream in which the string should be put
// const string2& str - the string that should be put into a stream
//----------------------------------------------

ostream& operator<<(ostream& out, const string2& str);

#endif
