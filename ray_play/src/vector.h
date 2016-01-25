#ifndef __VECTOR_H__
#define __VECTOR_H__

#define STEP 2
#define MIN_CAPACITY 10

template<class T> class Vector
{
private:
	size_t m_Capacity;
	size_t m_Size;
	T* m_Buffer;
public:
	Vector(size_t Capacity)
		: m_Size(Capacity)
		, m_Capacity(Capacity)
		, m_Buffer(new T[m_Capacity])
	{}
	
	Vector(const Vector& other)
		: m_Size(other.m_Size)
		, m_Capacity(other.m_Capacity)
		, m_Buffer(new T[m_Capacity])
	{
		for(size_t i = 0; i < m_Size; ++i)
		{
			m_Buffer[i] = other.m_Buffer[i];
		}
	}
	
	Vector()
		: m_Size(0)
		, m_Capacity(MIN_CAPACITY)
		, m_Buffer(new T[m_Capacity])
	{}
	
	~Vector(void)
	{
		delete [] m_Buffer;
	}
	
	size_t capacity() const
	{
		return m_Capacity;
	}
	
	size_t size() const
	{
		return m_Size;
	}
	
	bool empty() const
	{
		return m_Size == 0;
	}
	
	void clear()
	{
		//wouldn't we ideally want the destructors of the objects to be called?
		//I think real vectors are not implemented like this,
		//but with placement new and probably use malloc/free...
		m_Size = 0;
	}
	
	T& front()
	{
		return m_Buffer[0];
	}
	
	const T& front() const
	{
		return m_Buffer[0];
	}
	
	T& back()
	{
		return m_Buffer[m_Size - 1];
	}
	
	const T& back() const
	{
		return m_Buffer[m_Size - 1];
	}
	
	void pop_back()
	{
		//wouldn't we ideally want the destructor of the object to be called?
		//I think real vectors are not implemented like this,
		//but with placement new and probably use malloc/free...
		if(m_Size > 0)
		{
			--m_Size;
		}
	}
	
	void push_back(const T& item)
	{
		if(size() < m_Capacity)
		{
			m_Buffer[m_Size] = item;
			++m_Size;
		}
		else
		{
			m_Capacity *= STEP;
			T* temp = new T[m_Capacity];
			for(size_t i = 0; i < m_Size; ++i)
			{
				temp[i] = m_Buffer[i];
			}
			temp[m_Size] = item;
			delete [] m_Buffer;
			m_Buffer = temp;
			++m_Size;
		}
	}
	
	void resize(size_t NewSize)
	{
		m_Capacity = NewSize < MIN_CAPACITY ? MIN_CAPACITY : NewSize;
		T* newBuffer = new T[m_Capacity];
		for(size_t i = 0; i < m_Size && i < NewSize; ++i)
		{
			newBuffer[i] = m_Buffer[i];
		}
		m_Size = NewSize;
		T* temp = m_Buffer;
		m_Buffer = newBuffer;
		delete [] temp;
	}
	
	T& operator [](int Index)
	{
		assert(Index < m_Size);
		return m_Buffer[Index];
	}
	
	const T& operator [](int Index) const
	{
		assert(Index < m_Size);
		return m_Buffer[Index];
	}
	
	Vector& operator =(const Vector& other)
	{
		if(this != &other) 
		{
			delete [] m_Buffer;
			m_Size = other.m_Size;
			m_Capacity = other.m_Capacity;
			m_Buffer = new T[m_Capacity];
			for(size_t i = 0; i < m_Size; ++i)
			{
				m_Buffer[i] = other.m_Buffer[i];
			}
		}
		return *this;
	}
	
	class iterator 
	{
		friend class Vector;
		
		T* m_Curr;
		
		iterator(T* ptr)
			: m_Curr(ptr)
		{}
		
	public:
		
		bool operator ==(const iterator& other) const
		{
			return m_Curr == other.m_Curr;
		}
		
		bool operator !=(const iterator& other) const 
		{
			return !operator ==(other);
		}
		
		T& operator *()
		{
			return *m_Curr;
		}
		
		iterator& operator ++()
		{
			++m_Curr;
			return *this;
		}
		
		iterator operator ++(int)
		{
			iterator res = *this;
			++m_Curr;
			return res;
		}
		
		iterator& operator --()
		{
			--m_Curr;
			return *this;
		}
		
		iterator& operator --(int)
		{
			iterator res = *this;
			--m_Curr;
			return res;
		}
	};
	
	iterator current(size_t Index)
	{
		return iterator(m_Buffer + Index);
	}
	
	iterator begin() 
	{
		return iterator(m_Buffer);
	}
	
	iterator end() 
	{
		return iterator(m_Buffer + m_Size);
	}
	
	iterator erase(iterator pos)
	{
		T* p = pos.m_Curr + 1;
		for(iterator it = pos; it != this->end(); ++it, ++p)
		{
			(*it)=*(p);
		}
		--m_Size;
		return pos;
	}
	
	iterator erase(iterator first, iterator last)
	{
		for(iterator it = first; it.m_Curr != end().m_Curr - (last.m_Curr - first.m_Curr); ++it)
		{
			*it = *(it.m_Curr + (last.m_Curr - first.m_Curr));
		}
		m_Size -= last.m_Curr - first.m_Curr;
		return first;
	}
	
	/*
	//@TODO reimplement this
	iterator insert(iterator pos, const T& x)
	{
		if(empty())
		{
			m_Buffer[m_Size++] = x;
		}
		else
		{
			if(!(size()<capacity())) //if resizing is needed
				m_Capacity*=STEP;
			int Index=0;
			int offset=0;
			T* temp=new T[m_Capacity]; //reallocation
			for(int i=0; i<=m_Size; ++i) //loop all elements + 1
				if(m_Buffer+i==pos.m_Curr) //if pointed by iterator element is reached
				{
					offset=1; //set offset to 1
					temp[i]=x; //insert the element
					Index=i; //save an Index for later recreation of a valid iterator pos
				}
				else
					temp[i]=m_Buffer[i-offset];  //offset represents the difference between the Indexes of the tho arrays(which is 1 or 0(it is 1 only when we've inserted the X element))
			delete [] m_Buffer;
			m_Buffer=temp;
			m_Size++;
			pos=current(Index);
		}
		return pos;
	}
	*/
};

#endif // __VECTOR_H__
