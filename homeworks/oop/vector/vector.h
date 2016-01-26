//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #2
// FILE NAME: vector.h
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the vector container class.
//---------------------------------------------

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>

#define STEP 2

template<class T> class Vector
{
private:
	unsigned int capacity_;
	unsigned int size_;
	T* buffer_;
	const int step_;
public:
	//--------------------------------------------
	// FUNCTION: Vector
	// constructor for the Vector class
	// PARAMETERS:
	// unsigned int capacity - the capacity of the newly created Vector
	//----------------------------------------------
	
	Vector(unsigned int capacity)
			: size_(capacity), capacity_ (capacity), buffer_(new T[capacity_]), step_(STEP)
	{
	}
	
	//--------------------------------------------
	// FUNCTION: Vector
	// constructor for the Vector class
	// PARAMETERS:
	// const Vector& other - the other Vector to be copied
	//----------------------------------------------
	
	Vector(const Vector& other)
			: size_(other.size_), capacity_ (other.capacity_),buffer_(new T[capacity_]), step_(STEP)
	{
		for(unsigned int i=0;i<size_;i++) 
			buffer_[i]=other.buffer_[i];
	}
	
	//--------------------------------------------
	// FUNCTION: Vector
	// default constructor for the Vector class
	// PARAMETERS:
	//----------------------------------------------
	
	Vector()
			: size_ (0) , capacity_ (10),buffer_(new T[capacity_]), step_(STEP)
	{
	}
	
	//--------------------------------------------
	// FUNCTION: Vector
	// destructor for the Vector class
	// PARAMETERS:
	//----------------------------------------------
	
	~Vector(void)
	{
		delete [] buffer_;
	}
	
	//--------------------------------------------
	// FUNCTION: capacity
	// returns the capacity
	// PARAMETERS:
	//----------------------------------------------
	
	unsigned int capacity() const
	{
		return capacity_;
	}
	
	//--------------------------------------------
	// FUNCTION: size
	// returns the size
	// PARAMETERS:
	//----------------------------------------------
	
	unsigned int size() const
	{
		return size_;
	}
	
	//--------------------------------------------
	// FUNCTION: empty
	// returns true or false wether the vector is empty or not
	// PARAMETERS:
	//----------------------------------------------
	
	bool empty() const
	{
		return size()==0;
	}
	
	//--------------------------------------------
	// FUNCTION: clear
	// clears the vector
	// PARAMETERS:
	//----------------------------------------------
	
	void clear()
	{
		size_=0;
	}
	
	//--------------------------------------------
	// FUNCTION: operator[]
	// returns an element from the vector
	// PARAMETERS:
	// int index - the index of the element
	//----------------------------------------------
	
	T& operator[](int index)
	{
		if(index>=size_)
			throw std::exception();
		return buffer_[index];
	}
	
	//--------------------------------------------
	// FUNCTION: operator[]
	// like the normal one but returns const T&
	// PARAMETERS:
	// int index - the index of the element
	//----------------------------------------------
	
	const T& operator[](int index) const
	{
		if(index>=size_)
			throw std::exception();
		return buffer_[index];
	}
	
	//--------------------------------------------
	// FUNCTION: operator=
	// the overloaded operator=
	// PARAMETERS:
	// const Vector& other - the other vector to be copied
	//----------------------------------------------
	
	Vector& operator=(const Vector& other)
	{
		if(this!=&other) 
		{
			delete [] buffer_;
			size_=other.size_;
			capacity_=other.capacity_;
			buffer_=new T[capacity_];
			for(unsigned int i=0;i<size_;i++)
				buffer_[i]=other.buffer_[i];
		}
		return *this;
	}
	
	//--------------------------------------------
	// FUNCTION: front
	// returns the front element
	// PARAMETERS:
	//----------------------------------------------
	
	T& front()
	{
		return buffer_[0];
	}
	
	//--------------------------------------------
	// FUNCTION: front
	// returns the first element as const
	// PARAMETERS:
	// 
	//----------------------------------------------
	
	const T& front() const
	{
		return buffer_[0];
	}
	
	//--------------------------------------------
	// FUNCTION: back
	// returns the last element
	// PARAMETERS:
	//----------------------------------------------
	
	T& back()
	{
		return buffer_[size()-1];
	}
	
	//--------------------------------------------
	// FUNCTION: back
	// returns tle last element as const
	// PARAMETERS:
	//----------------------------------------------
	
	const T& back() const
	{
		return buffer_[size()-1];
	}
	
	//--------------------------------------------
	// FUNCTION: pop_back
	// erases the last element
	// PARAMETERS:
	//----------------------------------------------
	
	void pop_back()
	{
		if(size()>0)
			size_--;
	}
	
	//--------------------------------------------
	// FUNCTION: push_back
	// inserts an element at the back of the vector
	// PARAMETERS:
	// const T& item - the element to be inserted
	//----------------------------------------------
	
	void push_back(const T& item)
	{
		if(size()<capacity())
		{
			buffer_[size_]=item;
			size_++;
		}
		else
		{
			T* temp=new T[capacity_*STEP];
			unsigned int i;
			for(i=0; i<size(); i++)
				temp[i]=buffer_[i];
			temp[i]=item;
			delete [] buffer_;
			buffer_=temp;
			capacity_*=STEP;
			size_++;
		}
	}
	
	class iterator 
	{
		T* curr_;
		
		//--------------------------------------------
		// FUNCTION: oterator
		// constructor for the iterator class
		// PARAMETERS:
		// T* ptr - where to point
		//----------------------------------------------
	
		iterator(T* ptr)
				: curr_(ptr)
		{
		}

	public:
		friend class Vector;
		
		//--------------------------------------------
		// FUNCTION: operator==
		// the overloaded operator equals
		// PARAMETERS:
		// const iterator& other - the iterator to be compared with
		//----------------------------------------------
		
		bool operator==(const iterator& other) const 
		{
			return curr_==other.curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator!=
		// the overloaded operator not equals
		// PARAMETERS:
		// const iterator& other - the other iterator to be compared with
		//----------------------------------------------
		
		bool operator!=(const iterator& other) const 
		{
			return !operator==(other);
		}

		//--------------------------------------------
		// FUNCTION: operator*
		// returns the element that the iterator is pointing at
		// PARAMETERS:
		//----------------------------------------------
		
		T& operator*() 
		{
			return *curr_;
		}

		//--------------------------------------------
		// FUNCTION: operator++
		// the overloaded operator ++
		// PARAMETERS:
		//----------------------------------------------
		
		iterator& operator++() 
		{
			curr_++;
			return *this;
		}
		
		//--------------------------------------------
		// FUNCTION: operator--
		// the overloaded operator --
		// PARAMETERS:
		//----------------------------------------------
		
		iterator& operator--() 
		{
			curr_--;
			return *this;
		}
		
		//--------------------------------------------
		// FUNCTION: operator--(int)
		// same as operator--
		// PARAMETERS:
		//----------------------------------------------
		
		iterator& operator--(int) 
		{
			curr_--;
			return *this;
		}

		//--------------------------------------------
		// FUNCTION: operator++(int)
		// same as operator++
		// PARAMETERS:
		//----------------------------------------------
		
		iterator operator++(int) 
		{
			iterator res=*this;
			curr_++;
			return res;
		}
	};
	
	//--------------------------------------------
	// FUNCTION: current
	// returns an iterator considering an index
	// PARAMETERS:
	// unsigned int index_
	//----------------------------------------------
	
	iterator current(unsigned int index_)
	{
		return iterator(buffer_+index_);
	}
	
	//--------------------------------------------
	// FUNCTION: begin
	// returns an iterator pointing at the begining
	// PARAMETERS:
	//----------------------------------------------
	
	iterator begin() 
	{
		return iterator(buffer_);
	}
	
	//--------------------------------------------
	// FUNCTION: end
	// returns an iterator pointing at the end
	// PARAMETERS:
	//----------------------------------------------
	
	iterator end() 
	{
		return iterator(buffer_+size_);
	}
	
	//--------------------------------------------
	// FUNCTION: erase
	// erases an element pointed by the iterator pos
	// PARAMETERS:
	// iterator pos - points at the element to be deleted
	//----------------------------------------------
	
	iterator erase(iterator pos)
	{
		T* p=pos.curr_+1;
		for(iterator it=pos; it!=this->end(); it++,p++)
			(*it)=*(p);
		size_--;
		return pos;
	}
	
	//--------------------------------------------
	// FUNCTION: erase
	// erases all elements between the 2 iterators
	// PARAMETERS:
	// iterator first - the first iterator
	// iterator last - the last iterator
	//----------------------------------------------
	
	
	iterator erase(iterator first, iterator last)
	{
		for(iterator it=first;it.curr_!=end().curr_-(last.curr_-first.curr_); it++)
			*it=*(it.curr_+(last.curr_-first.curr_));
		size_-=last.curr_-first.curr_;
		return first;
	}
	
	//--------------------------------------------
	// FUNCTION: insert
	// inserts an element at a given position
	// PARAMETERS:
	// iterator pos - the position
	// const T& x - the element
	//----------------------------------------------
	
	iterator insert(iterator pos, const T& x)
	{
		if(empty())
			buffer_[size_++]=x;
		else
		{
			if(!(size()<capacity())) //if resizing is needed
				capacity_*=STEP;
			int index=0;
			int offset=0;
			T* temp=new T[capacity_]; //reallocation
			for(int i=0; i<=size_; i++) //loop all elements + 1
				if(buffer_+i==pos.curr_) //if pointed by iterator element is reached
				{
					offset=1; //set offset to 1
					temp[i]=x; //insert the element
					index=i; //save an index for later recreation of a valid iterator pos
				}
				else
					temp[i]=buffer_[i-offset];  //offset represents the difference between the indexes of the tho arrays (which is 1 or 0 (it is 1 only when we've inserted the X element))
			delete [] buffer_;
			buffer_=temp;
			size_++;
			pos=current(index);
		}
		return pos;
	}
	
	//same as iterator but const. see iterator for more info.
	class const_iterator 
	{
		T* curr_;

		const_iterator(T* ptr)
				: curr_(ptr)
		{
		}

	public:
		friend class Vector;

		bool operator==(const const_iterator& other) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator!=(const const_iterator& other) const 
		{
			return !operator==(other);
		}

		const T& operator*() 
		{
			return *curr_;
		}

		const const_iterator& operator++() 
		{
			curr_++;
			return *this;
		}

		const_iterator operator++(int) 
		{
			const_iterator res=*this;
			curr_++;
			return res;
		}
	};
	
	//reverse iterator is the same as the normal iterator, but ++ means -- and -- means ++ :D
	class reverse_iterator 
	{
		T* curr_;

		reverse_iterator(T* ptr)
				: curr_(ptr)
		{
		}

	public:
		friend class Vector;

		bool operator==(const reverse_iterator& other) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator!=(const reverse_iterator& other) const 
		{
			return !operator==(other);
		}

		T& operator*() 
		{
			return *(curr_-1);
		}

		reverse_iterator& operator++() 
		{
			curr_--;
			return *this;
		}

		reverse_iterator operator++(int) 
		{
			reverse_iterator res=*this;
			curr_--;
			return res;
		}
	};
	
	//this is like reverse iterator... but const... see reverse iterator for more info.
	class const_reverse_iterator 
	{
		T* curr_;

		const_reverse_iterator(T* ptr)
				: curr_(ptr)
		{
		}

	public:
		friend class Vector;

		bool operator==(const reverse_iterator& other) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator!=(const reverse_iterator& other) const 
		{
			return !operator==(other);
		}

		const T& operator*() 
		{
			return *(curr_-1);
		}

		const reverse_iterator& operator++() 
		{
			curr_--;
			return *this;
		}

		reverse_iterator operator++(int) 
		{
			reverse_iterator res=*this;
			curr_--;
			return res;
		}
	};
	
	//these functions are like begin() and end()... see them for more info.
	reverse_iterator rbegin() 
	{
		return reverse_iterator(buffer_+size_);
	}
	
	reverse_iterator rend() 
	{
		return reverse_iterator(buffer_);
	}	
	
	const_iterator begin() const 
	{
		return const_iterator(buffer_);
	}
	
	const_iterator end() const 
	{
		return const_iterator(buffer_+size_);
	}
	
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(buffer_+size_);
	}
	
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(buffer_);
	}
};

#endif
