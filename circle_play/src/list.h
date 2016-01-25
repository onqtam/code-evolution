#ifndef __LIST_H__
#define __LIST_H__

template <class T>
class List
{
private:
	struct Elem
	{
		T m_Data;
		Elem* m_Next;
		Elem* m_Prev;
		
		Elem(const T& val)
			: m_Data(val)
			, m_Next(0)
			, m_Prev(0)
		{}
	};
	
	size_t m_Size;
	Elem* m_Head;
	Elem* m_Tail;
public :
	
	List ()
		: m_Size(0)
		, m_Head(0)
		, m_Tail(0)
	{}
	
	List(const List& other)
		: m_Size(0)
		, m_Head(0)
		, m_Tail(0)
	{
		for(const_iterator it = other.begin(); it != other.end(); ++it)
		{
			push_back(*it);
		}
	}
	
	~List()
	{
		clear();
	}
	
	void push_back(const T& val)
	{
		Elem* newElem = new Elem(val);
		++m_Size;
		if(m_Head == 0)
		{
			m_Head = newElem;
			m_Tail = newElem;
		} 
		else 
		{
			m_Tail->m_Next = newElem;
			newElem->m_Prev = m_Tail;
			m_Tail = newElem;
		}
	}
	
	void pop_back()
	{
		if(m_Head != 0)
		{
			--m_Size;
			if(m_Head == m_Tail)
			{
				delete m_Tail;
				m_Head = m_Tail = 0;
			}
			else
			{
				Elem* t = m_Tail;
				m_Tail = t->m_Prev;
				m_Tail->m_Next = 0;
				delete t;
			}
		}
	}
	
	T& back()
	{
		return m_Tail->m_Data;
	}
	
	const T& back() const
	{
		return m_Tail->m_Data;
	}
	
	void push_front(const T& val)
	{
		Elem* newElem = new Elem(val);
		++m_Size;
		if(m_Head==0)
		{
			m_Head=newElem;
			m_Tail=newElem;
		} 
		else 
		{
			newElem->m_Next = m_Head;
			m_Head->m_Prev = newElem;
			newElem->m_Prev = 0;
			m_Head = newElem;
		}
	}
	
	void pop_front()
	{
		if(m_Head != 0)
		{
			--m_Size;
			if(m_Head == m_Tail)
			{
				delete m_Head;
				m_Head = m_Tail = 0;
			}
			else 
			{
				Elem* t = m_Head;
				m_Head = t->m_Next;
				m_Head->m_Prev = 0;
				delete t;
			}
		}
	}
	
	T& front()
	{
		return m_Head->m_Data;
	}
	
	const T& front() const
	{
		return m_Head->m_Data;
	}
	
	bool empty()
	{
		return m_Head == 0;
	}
	
	void swap(const List& other)
	{
		size_t temp_m_Size = m_Size;
		Elem* temp_m_Head = m_Head;
		Elem* temp_m_Tail = m_Tail;
		m_Head = other.m_Head;
		m_Tail = other.m_Tail;
		m_Size = other.m_Size;
		other.m_Head = temp_m_Head;
		other.m_Tail = temp_m_Tail;
		other.m_Size = temp_m_Size;
	}	
	
	void clear()
	{
		while(!empty())
		{
			pop_back();
		}
		m_Size = 0;
	}
	
	int size() const
	{
		return m_Size;
	}
	
	List& operator=(const List& other)
	{
		if(this != &other) 
		{
			clear();
			for(const_iterator it = other.begin(); it != other.end(); ++it)
			{
				push_back(*it);
			}
		}
		return *this;
	}
	
	class iterator
	{
		friend class List;
	private:
		Elem* m_Curr;
		
		iterator(Elem* ptr)
			: m_Curr(ptr)
		{}
		
	public:
		
		iterator operator ++()
		{
			m_Curr = m_Curr->m_Next;
			return m_Curr;
		}
		
		iterator operator ++(int)
		{
			m_Curr = m_Curr->m_Next;
			return m_Curr;
		}
		
		bool operator ==(const iterator& other) const
		{
			return m_Curr == other.m_Curr;
		}
		
		bool operator !=(const iterator & other) const
		{
			return m_Curr != other.m_Curr;
		}
		
		T& operator *()
		{
			return m_Curr->m_Data;
		}
		
		T* operator ->()
		{
			return &m_Curr->m_Data;
		}
	};
	
	iterator begin()
	{
		if(m_Size > 0)
		{
			return iterator(m_Head);
		}
		else
		{
			return iterator(0);
		}
	}
	
	iterator end()
	{
		return iterator(0);
	}
	
	iterator insert(const iterator& pos, const T& x)
	{
		if(!empty())
		{
			Elem* newElem = new Elem(x);
			if(pos != end())
			{
				newElem->m_Next = pos.m_Curr;
				newElem->m_Prev = pos.m_Curr->m_Prev;
				if(pos.m_Curr->m_Prev != 0)
				{
					pos.m_Curr->m_Prev->m_Next = newElem;
				}
				else
				{
					m_Head = newElem;
				}
				pos.m_Curr->m_Prev = newElem;
			}
			else
			{
				push_back(x);
			}
		}
		else
		{
			push_back(x);
		}
		
		return pos.m_Curr->m_Prev;
	}
	
	iterator erase(iterator pos)
	{
		if(!empty())
		{
			if(pos != begin() && pos != end() && pos.m_Curr != m_Tail)
			{
				pos.m_Curr->m_Prev->m_Next = pos.m_Curr->m_Next;
				pos.m_Curr->m_Next->m_Prev = pos.m_Curr->m_Prev;
				T* temp = &pos.m_Curr->m_Data;
				--m_Size;
				delete temp;
			}
			else
			{
				if(pos == begin())
				{
					pop_front();
				}
				else
				{
					pop_back();
				}
			}
		}
		return pos;
	}
	
	iterator erase(iterator first, iterator last)
	{
		for(iterator it = first; (it != last) && ((int)m_Head != 0); ++it)
		{
			erase(it);
		}
		return last;
	}
	
	class const_iterator 
	{
		friend class List;
	private:
		Elem* m_Curr;
		
		const_iterator(Elem* ptr)
			: m_Curr(ptr)
		{}
	public:
		
		const_iterator operator ++()
		{
			m_Curr = m_Curr->m_Next;
			return m_Curr;
		}
		
		const_iterator operator ++(int)
		{
			m_Curr = m_Curr->m_Next;
			return m_Curr;
		}
		
		bool operator ==(const const_iterator& other) const
		{
			return m_Curr == other.m_Curr;
		}
		
		bool operator !=(const const_iterator& other) const
		{
			return m_Curr != other.m_Curr;
		}
		
		const T& operator *() const
		{
			return m_Curr->m_Data;
		}
		
		const T* operator ->() const
		{
			return m_Curr.m_Data;
		}
	};
	
	const_iterator end() const
	{
		return const_iterator(0);
	}
	
	const_iterator begin() const
	{
		if(m_Size > 0)
		{
			return const_iterator(m_Head);
		}
		else
		{
			return const_iterator(0);
		}
	}
};

#endif // __LIST_H__
