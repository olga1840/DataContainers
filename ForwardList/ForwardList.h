#pragma once
#include<iostream>
using namespace std;
using std::cout;

#define tab "\t"

///////////////////////////////////////////////////////////////////////////
///////////////////     class declaration - объ€вление класса     ////////


template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>class Element
{
	T Data;      //значение элемента
	Element<T>* pNext; //адрес следующего элемента
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
	friend class ForwardList<T>;
	friend class Iterator<T>;
};


template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr);
	~Iterator();

	Iterator<T>& operator++();

	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	T& operator*();
};

template<typename T>class ForwardList    //forward - односв€зный, однонаправленный
{
	Element<T>* Head;    //голова списка - содержит указатель на нулевой элемент списка
	int size;
public:
	Iterator<T> begin();
	Iterator<T> end();
	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	~ForwardList();

	//   Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);

	//                            Erasing elements
	void pop_front();
	void pop_back();
	void  erase(int Index);

	//   Methods:
	void print()const;
};

///////////////////     class declaration END -  конец объ€влени€ класса     ////////
////////////////////////////////////////////////////////////////////////////////////
