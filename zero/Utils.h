#ifndef __UTILS_H__
#define __UTILS_H__

//#include "Header.h"
#include "list"
#include "map"
#include "CDevice.h"
using namespace std;

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#   define ListIterator(type) list<type>::iterator
#else
#   define ListIterator(type) _List_iterator<type>
#endif

namespace GameTutor
{
	template<typename element_type>
	class CList
	{
	public:
		CList();
		virtual ~CList();
		void AddItem(element_type ele);
		void RemoveItem(element_type ele);
		element_type GetElement(int index);
		element_type operator[](int index);
		int GetCount();
		void DeallocateElementPointer();
		void Clear();

		void BeginTravel();
		element_type Travel();
		bool IsEndOfTravel();
		int GetTravelStepCounter() { return m_iTravelStepCounter; }
	protected:
		list<element_type>* m_List;
		typename list<element_type>::iterator m_CurrentIter;
	private:
		int m_iTravelStepCounter;
	};

	template<typename element_type>
	class CLut
	{
		struct ltstr
		{
			bool operator()(const char* s1, const char* s2) const
			{
				return strcmp(s1, s2) < 0;
			}
		};
	public:
		CLut();
		virtual ~CLut();
		void AddItem(const char * name, element_type ele);
		element_type RemoveItem(const char * name);
		bool GetElement(const char * name, element_type& out);
		int GetCount();
		void DeallocateElementPointer();
		void Clear();
	protected:
		map<const char *, element_type, ltstr> m_List;
	};


	// Additive congruential
	// a[0] = seed
	// a[i] = (b*a[i]) % m , i < c
	// a[j] = (a[j-b] + a[j-c]) % m, j >= c
#define RND_MAX_VAL_SHIFT	30
#define RND_MAX_VAL_MASK	0x3fffffffl
#define RND_HALF_MAX_VAL_SHIFT	15
#define RND_HALF_MAX_VAL_MASK	0x7fffl
#define RND_C				55
#define RND_B				31
	class CRandom
	{
	public:
		CRandom()
		{
			SetSeed(CDevice::GetInstance()->GetTimer());
		}

		CRandom(__UINT64 seed)
		{
			SetSeed(seed);
		}

		void SetSeed(__UINT64 seed)
		{
			m_Val[0] = seed;
			for (m_iRandomIndex = 1; m_iRandomIndex < RND_C; m_iRandomIndex++)
			{
				m_Val[m_iRandomIndex] = (Mult(RND_B, m_Val[m_iRandomIndex - 1])) & RND_MAX_VAL_MASK;
			}
		}

		__UINT32 NextInt(__UINT32 max)
		{
			m_iRandomIndex = (m_iRandomIndex + 1) % RND_C;
			int shift1 = (m_iRandomIndex + (RND_C - 1) - RND_B) % RND_C;
			int shift2 = (m_iRandomIndex + (RND_C - 1)) % RND_C;

			m_Val[m_iRandomIndex] = (m_Val[shift1] + m_Val[shift2]) & RND_MAX_VAL_MASK;
			__UINT64 rint = ((m_Val[m_iRandomIndex] >> RND_HALF_MAX_VAL_SHIFT)*max) >> RND_HALF_MAX_VAL_SHIFT;
			return __UINT32(rint);
		}

		__UINT32 NextTrueFalse()
		{
			return  NextInt(100) > 50 ? 1 : 0;
		}

		__UINT32 NextTrue(__UINT32 percent)
		{
			return NextInt(100) < percent ? 1 : 0;
		}

	private:
		__UINT64 m_Val[RND_C];
		__UINT32 m_iRandomIndex;
	private:
		__UINT64 Mult(__UINT64 a, __UINT64 b) // mul 2 number without overflow. Assume a, b are 30bits integers.
		{
			__UINT64 a1 = a >> RND_HALF_MAX_VAL_SHIFT;
			__UINT64 a0 = a&RND_HALF_MAX_VAL_MASK;
			__UINT64 b1 = b >> RND_HALF_MAX_VAL_SHIFT;
			__UINT64 b0 = b&RND_HALF_MAX_VAL_MASK;

			__UINT64 mul = (((((a0*b1) + (a1*b0)) & RND_HALF_MAX_VAL_MASK) << RND_HALF_MAX_VAL_SHIFT) + a0*b0) & RND_MAX_VAL_MASK;

			return mul;
		}
	};


	template<class T>
	inline T Math_Abs(T a)
	{
		return (a<0 ? -a : a);
	}

	template<class T>
	void Math_GetLog2(T input, __UINT32 &val, __UINT32 &mod)
	{
		__UINT32 num = __UINT32(input);
		val = 0;
		mod = 0;
		if (num == 0)
		{
			return;
		}
		else if (num == 1)
		{
			val = 0;
			mod = 1;
			return;
		}
		else
		{
			__UINT32 tmp = num;
			while (tmp > 1)
			{
				val++;
				tmp >>= 1;
			}
			mod = num - (1 << val);
		}
	}

	template<class T>
	inline T Math_Min(T a, T b)
	{
		return (a<b ? a : b);
	}

	template<class T>
	inline T Math_Max(T a, T b)
	{
		return (a>b ? a : b);
	}

	template<class T>
	inline bool Math_IsPO2(T a)
	{
		if (a < 0) return false;
		__INT32 num = __UINT32(a);
		return ((num&(-num)) == num);
	}

	inline
		void Str_ToUpper(char *input, __INT32 size)
	{
		if (input)
		{
			for (int i = 0; i < size; i++)
			{
				if (input[i] >= 'a' && input[i] <= 'z')
				{
					input[i] += 'A' - 'a';
				}
			}
		}
	}

	inline
		void Str_ToLower(char *input, __INT32 size)
	{
		if (input)
		{
			for (int i = 0; i < size; i++)
			{
				if (input[i] >= 'A' && input[i] <= 'Z')
				{
					input[i] += 'a' - 'A';
				}
			}
		}
	}
}


template<typename element_type> GameTutor::CList<element_type>::CList()
{
	m_List = new list<element_type>();
}

template<typename element_type> GameTutor::CList<element_type>::~CList()
{
	m_List->clear();
	SAFE_DELETE(m_List);
}


template<typename element_type> void GameTutor::CList<element_type>::AddItem(element_type ele)
{
	m_List->push_back(ele);
}

template<typename element_type> void GameTutor::CList<element_type>::RemoveItem(element_type ele)
{
	m_List->remove(ele);
}

template<typename element_type> element_type GameTutor::CList<element_type>::GetElement(int index)
{
	ListIterator(element_type) i = m_List->begin();
	int _i = 0;
	if ((unsigned)index < m_List->size())
	{
		for (i = m_List->begin(); _i < index; i++, _i++){}
		return (*i);
	}
	return (*i);
}

template<typename element_type> element_type GameTutor::CList<element_type>::operator[] (int index)
{
	return GetElement(index);
}

template<typename element_type> int GameTutor::CList<element_type>::GetCount()
{
	if (!m_List) return 0;
	return m_List->size();
}

template<typename element_type> void GameTutor::CList<element_type>::DeallocateElementPointer()
{
	if (GetCount() > 0)
	{
		ListIterator(element_type) i;
		ListIterator(element_type) cur;
		for (i = m_List->begin(); i != m_List->end();)
		{
			cur = i;
			i++;
			if (*cur)
			{
				delete[] * cur;
			}
		}
	}
}

template<typename element_type> void GameTutor::CList<element_type>::Clear()
{
	if (GetCount() > 0)
	{
		m_List->clear();
	}
}



template<typename element_type> void GameTutor::CList<element_type>::BeginTravel()
{
	m_CurrentIter = m_List->begin();
	m_iTravelStepCounter = -1;
}
template<typename element_type> element_type GameTutor::CList<element_type>::Travel()
{
	element_type re = (*m_CurrentIter);
	if (m_CurrentIter != m_List->end())
	{
		m_CurrentIter++;
		m_iTravelStepCounter++;
	}
	return re;
}
template<typename element_type> bool GameTutor::CList<element_type>::IsEndOfTravel()
{
	return ((GetCount() == 0) || (m_CurrentIter == m_List->end()));
}

///////////////////////////////
// Clut
///////////////////////////////
template<typename element_type> GameTutor::CLut<element_type>::CLut()
{
}

template<typename element_type> GameTutor::CLut<element_type>::~CLut()
{
	m_List.clear();
}


//element_type RemoveItem(const char * name);
//element_type GetElement(const char * name);
//int GetCount();			
//void DeallocateElementPointer();
//void Clear();

template<typename element_type> void GameTutor::CLut<element_type>::AddItem(const char *name, element_type ele)
{
	char *namex = new char[strlen(name) + 1];
	memcpy(namex, name, strlen(name) + 1);
	m_List[namex] = ele;
}

template<typename element_type> element_type GameTutor::CLut<element_type>::RemoveItem(const char *name)
{
	element_type re;
	if (GetElement(name, re))
	{
		map<const char*, element_type, ltstr>::iterator cur = m_List.find(name);
		char *key = (char*)((*cur).first);
		m_List.erase(name);
		delete key;
		return re;
	}
	else
	{
		return 0;
	}
}

template<typename element_type> bool GameTutor::CLut<element_type>::GetElement(const char *name, element_type & out)
{
	map<const char*, element_type, ltstr>::iterator cur = m_List.find(name);
	if (cur != m_List.end())
	{
		out = (*cur).second;
		return true;
	}
	else
	{
		return false;
	}
}


template<typename element_type> int GameTutor::CLut<element_type>::GetCount()
{
	return m_List.size();
}

template<typename element_type> void GameTutor::CLut<element_type>::DeallocateElementPointer()
{
	if (m_List.size() > 0)
	{
		map<const char*, element_type, ltstr>::iterator cur = m_List.begin();
		for (cur = m_List.begin(); cur != m_List.end(); cur++)
		{
			/*char *key = (char*)((*cur).first);
			SAFE_DEL(key);*/
			SAFE_DEL((*cur).second);
		}
	}
}

template<typename element_type> void GameTutor::CLut<element_type>::Clear()
{
	if (m_List.size() > 0)
	{
		map<const char*, element_type, ltstr>::iterator cur = m_List.begin();
		for (cur = m_List.begin(); cur != m_List.end(); cur++)
		{
			char *key = (char*)((*cur).first);
			SAFE_DEL(key);
		}
	}
	m_List.clear();
}

#include <sstream>

//Chuyen so thanh chuoi 
//
//Usage: NumberToString(Number);
//
template <typename T>
string NumberToString(T Number)
{
	stringstream ss(stringstream::in | stringstream::out);
	ss << Number;
	return ss.str();
}

//Chuyen chuoi thanh so
//
// Usage: StringToNumber<Type>(String);
//
template <typename T>
T StringToNumber(const string &Text)//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

#endif