#pragma once
#include<iostream>
using namespace std;
using std::cout;
using std::cin;

#define tab "\t"
template<typename T>class ConstBaseIterator;

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev);
		~Element();
		friend class List<T>;
	}*Head, * Tail;
	unsigned int size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {};
		~ConstBaseIterator() {};
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {};
		~Iterator() {};
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {};
		~ReverseIterator() {};
		T& operator*();
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	List();
	List(const std::initializer_list<T>& il) :List();
	~List();

	//     Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);
	//                  Removing elements:
	void pop_front();
	void pop_back();
	void  erase(int Index);


	//                    Methods:
	void print()const;
};
template<typename T>void print(const List<T>& list);
template<typename T>void reverse_print(const List<T>& list);

