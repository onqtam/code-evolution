//--------------------------------------------
// NAME: Viktor Kirilov
// CLASS: Xib
// NUMBER: 4
// PROBLEM: #3
// FILE NAME: list.h
// FILE PURPOSE:
// The file's purpose is to contain my homework(program)
// which simulates the list container class.
//---------------------------------------------

#ifndef LIST_HPP
#define LIST_HPP

template <class T> class List 
{
private:
	struct Elem 
	{
		T data_ ;
		Elem * next_ ;
		Elem * prev_ ;
		
		//--------------------------------------------
		// FUNCTION: Elem
		// constructor for the Elem class
		// PARAMETERS:
		// T Val - the type of element
		//----------------------------------------------
		Elem ( T val )
				: data_ ( val ) , next_ (0) , prev_ (0)
		{
		}
	};
	
	unsigned int size_;
	Elem * head_ ;
	Elem * tail_ ;
public :
	
	//--------------------------------------------
	// FUNCTION: List
	// constructor for the List class
	// PARAMETERS:
	//----------------------------------------------
		
	List ()
			: size_ (0), head_ (0) ,tail_ (0)
	{
	}
	
	//--------------------------------------------
	// FUNCTION: List
	// constructor for the List class
	// PARAMETERS:
	// const List& other - the other list to be copied from
	//----------------------------------------------
	
	List(const List& other)
			: size_ (0), head_ (0) ,tail_ (0)
	{
		for(const_iterator it=other.begin(); it!=other.end(); ++it)
			push_back(*it);
	}
	
	//--------------------------------------------
	// FUNCTION: ~List
	// destructor for the List class
	// PARAMETERS:
	//----------------------------------------------
	
   	~List()
   	{
		clear();
	}
	
	//--------------------------------------------
	// FUNCTION: push_back
	// pushes back in the lsit a value
	// PARAMETERS:
	// T Val - the element to be pushed
	//----------------------------------------------
	
	void push_back(T val)
	{
		Elem* newElem = new Elem(val);
		size_++;
		if(head_==0)
		{
			head_=newElem;
			tail_=newElem;
		} 
		else 
		{
			//some intelligent stuff...
			tail_->next_=newElem;
			newElem->prev_=tail_;
			tail_=newElem;
		}
	}
	
	//--------------------------------------------
	// FUNCTION: pop_back
	// deletes the last element
	// PARAMETERS:
	//----------------------------------------------
	
	void pop_back()
	{
		if(head_!=0)
			if (head_==tail_)
			{
				size_--;
				delete tail_;
				head_=tail_=0;
			} 
			else 
			{
				//some intelligent stuff...
				size_--;
				Elem* t=tail_;
				tail_=t->prev_;
				tail_->next_=0;
				delete t;
			}	
	}
	
	//--------------------------------------------
	// FUNCTION: back
	// returns the last element
	// PARAMETERS:
	//----------------------------------------------
	
	T& back()
	{
		return tail_->data_;
	}
	
	//--------------------------------------------
	// FUNCTION: back
	// returns the last element as const
	// PARAMETERS:
	//----------------------------------------------
	
	const T& back() const
	{
		return tail_->data_;
	}
	
	//--------------------------------------------
	// FUNCTION: push_front
	// pushes an element in the front of the lsit
	// PARAMETERS:
	// T Val - the element to be pushed
	//----------------------------------------------
	
	void push_front(T val)
	{
		Elem* newElem = new Elem(val);
		size_++;
		if(head_==0)
		{
			head_=newElem;
			tail_=newElem;
		} 
		else 
		{
			//some intelligent stuff...
			newElem->next_=head_;
			head_->prev_=newElem;
			newElem->prev_=0;
			head_=newElem;
		}
	}
	
	//--------------------------------------------
	// FUNCTION: pop_front
	// deletes the first element
	// PARAMETERS:
	//----------------------------------------------
	
	void pop_front()
	{
		if(head_!=0)
			if (head_==tail_)
			{
				size_--;
				delete head_;
				head_=tail_=0;
			}
			else 
			{
				//some intelligent stuff...
				size_--;
				Elem* t=head_;
				head_=t->next_;
				head_->prev_=0;
				delete t;
			}
	}
	
	//--------------------------------------------
	// FUNCTION: front
	// returns the first element
	// PARAMETERS:
	//----------------------------------------------
	
	T& front()
	{
		return head_->data_;
	}
	
	//--------------------------------------------
	// FUNCTION: front
	// returns the first element as const
	// PARAMETERS:
	//----------------------------------------------
	
	const T& front() const
	{
		return head_->data_;
	}
	
	//--------------------------------------------
	// FUNCTION: empty
	// returns true/false if the list is empty
	// PARAMETERS:
	//----------------------------------------------
	
	bool empty()
	{
		return head_==0;
	}
	
	//--------------------------------------------
	// FUNCTION: swap
	// swaps 2 lists
	// PARAMETERS:
	// List& other - the other list to be swapped with
	//----------------------------------------------
	
	void swap(List& other)
	{
		//some intelligent stuff...
		unsigned int temp_size_=size_;
		Elem* temp_head_=head_;
		Elem* temp_tail_=tail_;
		head_=other.head_;
		tail_=other.tail_;
		size_=other.size_;
		other.head_=temp_head_;
		other.tail_=temp_tail_;
		other.size_=temp_size_;
	}	
	
	//--------------------------------------------
	// FUNCTION: clear
	// clears the list
	// PARAMETERS:
	//----------------------------------------------
	
	void clear()
	{
		while(!empty())
			pop_back();
		size_=0;
	}
	
	//--------------------------------------------
	// FUNCTION: size
	// returns the size of the list
	// PARAMETERS:
	//----------------------------------------------
	
	int size() const
	{
		return size_;
	}
	
	//--------------------------------------------
	// FUNCTION: operator=
	// assigns the other list to the current
	// PARAMETERS:
	// const List& other - the other list to be assigned
	//----------------------------------------------
	
	List& operator=(const List& other)
	{
		if(this!=&other) 
		{
			clear();
			for(const_iterator it=other.begin(); it!=other.end(); ++it)
				push_back(*it);
		}
		return *this;
	}
	
	class iterator
	{
	private:
		Elem* curr_;
		
		//--------------------------------------------
		// FUNCTION: iterator
		// default constructor for the iterator class
		// PARAMETERS:
		// Elem* ptr - the element to point at
		//----------------------------------------------
	
		iterator(Elem* ptr)
				: curr_(ptr)
		{
		}
	public:
		friend class List;
		
		//--------------------------------------------
		// FUNCTION: operator++
		// increments the iterator
		// PARAMETERS:
		//----------------------------------------------
		
		iterator operator ++()
		{
			curr_=curr_->next_;
			return curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator++
		// increments the iterator
		// PARAMETERS:
		//----------------------------------------------
		
		iterator operator ++( int)
		{
			curr_=curr_->next_;
			return curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator==
		// returns true/false debending on whether the 2 lists compared are equal or not
		// PARAMETERS:
		//----------------------------------------------
		
		bool operator ==( const iterator & other ) const 
		{
			return curr_==other.curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator!=
		// returns true/false debending on whether the 2 lists compared are equal or not
		// PARAMETERS:
		//----------------------------------------------
		
		bool operator !=( const iterator & other ) const 
		{
			return curr_!=other.curr_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator*
		// returns the data of the element pointed by the iterator
		// PARAMETERS:
		//----------------------------------------------
		
		T& operator *()
		{
			return curr_->data_;
		}
		
		//--------------------------------------------
		// FUNCTION: operator->
		// returns the data of the element pointed by the iterator
		// PARAMETERS:
		//----------------------------------------------
		
		T* operator ->()
		{
			return curr_.data_;
		}
	};
	
	//--------------------------------------------
	// FUNCTION: begin
	// returns an iterator pointing at the first element
	// PARAMETERS:
	//----------------------------------------------
	
	iterator begin()
	{
		if(size_>0)
		{
			iterator it(head_);
			return it;
		}
		else
		{
			iterator it(head_->prev_);
			return it;
		}
	}
	
	//--------------------------------------------
	// FUNCTION: end
	// returns an iterator pointing at one after the last element
	// PARAMETERS:
	//----------------------------------------------
	
	iterator end()
	{
		iterator it(tail_->next_);
		return it;
	}
	
	//--------------------------------------------
	// FUNCTION: insert
	// inserts an element at a given position
	// PARAMETERS:
	// iterator pos - the iterator pointing at the location
	// const T& x - the element to be inserted
	//----------------------------------------------
	
	iterator insert(iterator pos, const T& x)
	{
		if(!empty())
		{
			Elem* newElem = new Elem(x);
			if(pos!=end()) // to see whether we want to push_back the element
			{
				//some intelligent stuff...
				newElem->next_=pos.curr_;
				newElem->prev_=pos.curr_->prev_;
				if(pos.curr_->prev_!=0)
					pos.curr_->prev_->next_=newElem;
				else
					head_=newElem;
				pos.curr_->prev_=newElem;
			}
			else
				push_back(x);
		}
		else
			push_back(x);
		return pos.curr_->prev_;
	}
	
	//--------------------------------------------
	// FUNCTION: erase
	// erases an element pointed by an iterator
	// PARAMETERS:
	// iterator pos - the iterator pointing at the element to be deleted
	//----------------------------------------------
	
	iterator erase(iterator pos)
	{
		if(!empty())
		{
			// if the element pointed by the iterator is not in the begining/end of the list
			if(pos!=begin() && pos!=end() && pos.curr_!=tail_) 
			{
				//some intelligent stuff...
				pos.curr_->prev_->next_=pos.curr_->next_;
				pos.curr_->next_->prev_=pos.curr_->prev_;
				T* temp=&pos.curr_->data_;
				size_--;
				delete temp;
			}
			else //if it is begin/end we use one of the ready methods
				if(pos==begin())
					pop_front();
				else
					pop_back();
		}
		return pos;
	}
	
	//--------------------------------------------
	// FUNCTION: erase
	// erases all elements between 2 iterators
	// PARAMETERS:
	// iterator first - the first iterator
	// iterator last - the last iterator
	//----------------------------------------------
	
	iterator erase(iterator first, iterator last)
	{
		for(iterator it=first; (it!=last) && ((int)head_!=0); it++)
			erase(it);
		return last;
	}
	
	//for the following 3 classes see the iterator class for more info about them
	
	class reverse_iterator 
	{
	private:
		Elem* curr_;
		
		reverse_iterator(Elem* ptr)
				: curr_(ptr)
		{
		}
	public:
		friend class List;
		
		reverse_iterator operator ++()
		{
			curr_=curr_->prev_;
			return curr_;
		}
		
		reverse_iterator operator ++( int)
		{
			curr_=curr_->prev_;
			return curr_;
		}
		
		bool operator ==( const reverse_iterator & other ) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator !=( const reverse_iterator & other ) const 
		{
			return curr_!=other.curr_;
		}
		
		T& operator *()
		{
			return curr_->data_;
		}
		
		T* operator ->()
		{
			return curr_.data_;
		}
	};
	
	class const_iterator 
	{
	private:
		Elem* curr_;
		
		const_iterator(Elem* ptr)
				: curr_(ptr)
		{
		}
	public:
		friend class List;
		
		const_iterator operator ++()
		{
			curr_=curr_->next_;
			return curr_;
		}
		
		const_iterator operator ++( int)
		{
			curr_=curr_->next_;
			return curr_;
		}
		
		bool operator ==( const const_iterator & other ) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator !=( const const_iterator & other ) const 
		{
			return curr_!=other.curr_;
		}
		
		const T& operator *() const
		{
			return curr_->data_;
		}
		
		const T* operator ->() const
		{
			return curr_.data_;
		}
	};
	
	class const_reverse_iterator 
	{
	private:
		Elem* curr_;
		
		const_reverse_iterator(Elem* ptr)
				: curr_(ptr)
		{
		}
	public:
		friend class List;
		
		const_reverse_iterator operator ++()
		{
			curr_=curr_->prev_;
			return curr_;
		}
		
		const_reverse_iterator operator ++( int)
		{
			curr_=curr_->prev_;
			return curr_;
		}
		
		bool operator ==( const const_reverse_iterator & other ) const 
		{
			return curr_==other.curr_;
		}
		
		bool operator !=( const const_reverse_iterator & other ) const 
		{
			return curr_!=other.curr_;
		}
		
		T& operator *()
		{
			return curr_->data_;
		}
		
		T* operator ->()
		{
			return curr_.data_;
		}
	};
	
	//for the following 6 methods see the begin and end which return an iterator for more information
	
	const_iterator end() const
	{
		const_iterator it(tail_->next_);
		return it;
	}
	
	const_iterator begin() const
	{
		if(size_>0)
		{
			const_iterator it(head_);
			return it;
		}
		else
		{
			const_iterator it(head_->prev_);
			return it;
		}
	}
	
	reverse_iterator rend()
	{
		reverse_iterator it(head_->prev_);
		return it;
	}
	
	reverse_iterator rbegin()
	{
		reverse_iterator it(tail_);
		return it;
	}
	
	const_reverse_iterator rend() const
	{
		if(size_>0)
		{
			const_reverse_iterator it(head_->prev_);
			return it;
		}
		else
		{
			const_reverse_iterator it(head_->prev_);
			return it;
		}
	}
	
	const_reverse_iterator rbegin() const
	{
		const_reverse_iterator it(tail_);
		return it;
	}
};

#endif
