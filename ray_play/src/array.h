#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <cassert>

template<class T>
class Array
{
private:
	size_t m_Size;
	T* m_Buffer;
public:
	
	Array()
		: m_Size(0)
		, m_Buffer(0)
	{}
	
	Array(size_t Size)
		: m_Size(Size)
		, m_Buffer(0)
	{
		m_Buffer = new T[Size];
	}
	
	Array(size_t Size, const T& Default)
		: m_Size(Size)
		, m_Buffer(0)
	{
		m_Buffer = new T[Size];
		Set(Default);
	}
	
	Array(const Array& other)
		: m_Size(other.m_Size)
		, m_Buffer(new T[other.m_Size])
	{
		for(size_t i = 0; i < m_Size; ++i)
		{
			m_Buffer [i] = other.m_Buffer[i];
		}
	}
	
	~Array()
	{
		delete [] m_Buffer;
	}
	
	void set(const T& Value)
	{
		for(size_t i = 0; i < m_Size; ++i)
		{
			m_Buffer[i] = Value;
		}
	}
	
	void resize(size_t NewSize)
	{
		T* newBuffer = new T[NewSize];
		for(size_t i = 0; i < m_Size && i < NewSize; ++i)
		{
			newBuffer[i] = m_Buffer[i];
		}
		m_Size = NewSize;
		T* temp = m_Buffer;
		m_Buffer = newBuffer;
		delete [] temp;
	}
	
	size_t size() const
	{
		return m_Size;
	}
	
	T& operator [](size_t Index)
	{
		assert(Index < m_Size);
		return m_Buffer[Index];
	}
	
	const T& operator [](size_t Index) const
	{
		assert(Index < m_Size);
		return m_Buffer[Index];
	}
	
	Array& operator =(const Array& Other)
	{
		if(this != &Other) 
		{
			delete [] m_Buffer;
			m_Size = Other.m_Size;
			m_Buffer = new T[m_Size];
			for(size_t i = 0; i < m_Size; ++i)
			{
				m_Buffer[i] = Other.m_Buffer[i];
			}
		}
		return *this;
	}
};

#endif // __ARRAY_H__
