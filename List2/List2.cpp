#include"List2.h"

template<typename T>Element<T>::Element(T Data, Element* pNext, Element* pPrev):Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
template<typename T>Element<T>::~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		
	unsigned int size;

	template<typename T>ConstBaseIterator<T>::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
	template<typename T>ConstBaseIterator<T>::~ConstBaseIterator() {}
	template<typename T>ConstBaseIterator<T>::bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
	template<typename T>ConstBaseIterator<T>::bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
	template<typename T>ConstBaseIterator<T>::const T& operator*()const
		{
			return Temp->Data;
		}

	template<typename T>ConstIterator<T>::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
	template<typename T>ConstIterator<T>::~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}
	template<typename T>ConstIterator<T>::ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
	template<typename T>ConstIterator<T>::ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	template<typename T>ConstIterator<T>::ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
	template<typename T>ConstIterator<T>::ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
	template<typename T>ConstReverseIterator<T>::~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
		}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator operator++(T)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator operator--(T)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	
	template<typename T>Iterator<T>::Iterator(Element* Temp) :ConstIterator(Temp) {}
	template<typename T>Iterator<T>::~Iterator() {}
	template<typename T>Iterator<T>::T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	
	template<typename T>ReverseIterator<T>::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
	template<typename T>ReverseIterator<T>::~ReverseIterator() {}
	template<typename T>ReverseIterator<T>::T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	
	template<typename T>ConstIterator<T>::ConstIterator cbegin()const
	{
		return Head;
	}
	template<typename T>ConstIterator<T>::ConstIterator cend()const
	{
		return nullptr;
	}
	template<typename T>ConstIterator<T>::ConstIterator begin()const
	{
		return Head;
	}
	template<typename T>ConstIterator<T>::ConstIterator end()const
	{
		return nullptr;
	}
	template<typename T>Iterator<T>::Iterator begin()
	{
		return Head;
	}
	template<typename T>Iterator<T>::Iterator end()
	{
		return nullptr;
	}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	template<typename T>ConstReverseIterator<T>::ConstReverseIterator crend()const
	{
		return nullptr;
	}
	template<typename T>ReverseIterator<T>::ReverseIterator rbegin()
	{
		return Tail;
	}
	template<typename T>ReverseIterator<T>::ReverseIterator rend()
	{
		return nullptr;
	}
	template<typename T>List<T>::List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	template<typename T>List<T>::~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//     Adding elements:
	template<typename T>List<T>::void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	template<typename T>List<T>::void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	template<typename T>List<T>::void insert(int Index, T Data)
	{
		//if (Index == 0)return push_front(Data);
		if (Index > size)return;

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	//                  Removing elements:
	template<typename T>List<T>::void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail;
			Head = Tail = nullptr;
			return;
		}
		//1) Исключаем элемент из списка
		Head = Head->pNext;
		//2) удаляем элемент из памяти
		delete Head->pPrev;
		//3) обнуляем адрес удаленного элемента
		Head->pPrev = nullptr;
		size--;
	}
	template<typename T>List<T>::void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	template<typename T>List<T>::void  erase(int Index)
	{
		if (Index == 0)return pop_front();
		if (Index == size - 1)return pop_back();
		if (Index == size)
		{
			cout << "Ошибка! Индекс удаляемого элемента превышает размер списка!\t" << endl;
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Element* Erased = Temp;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Erased;
		size--;
	}



	//                    Methods:
	template<typename T>List<T>::void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};
template<typename T>void print(const List<T>& list)
{
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}
template<typename T>void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{
		//*rit *= 10;
		cout << *rit << tab;
	}
	cout << endl;
}