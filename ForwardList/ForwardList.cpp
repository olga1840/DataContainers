#include"ForwardList.h"

///////////////////////////////////////////////////////////////////////////////////////
////////////////  class definition - определение класса            ///////////////////

template<typename T>int Element<T>::count = 0; //инициализируем статическую переменную, объявленную в классе  'Element'

template<typename T>Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>Element<T>::~Element()
{
	count--;
	cout << "EDestructor:\t" << this << endl;
}

////////////   Iterator    ////////////////

template<typename T>Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T>Iterator<T>::~Iterator()
{
	cout << "ItDestructor:\t" << this << endl;
}

template<typename T>Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>T& Iterator<T>::operator*()
{
	return Temp->Data;
}

/////////////////////   ForwardList   ////////////////////////

template<typename T>Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr; //Если список пуст, то его голова указывает на 0
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList() //il - initializer list
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//   Adding elements:
template<typename T>void ForwardList<T>::push_front(T Data)
{
	/*//1) создаем новый элемент
	Element* New = new Element(Data);
	//2) новый элемент должен указывать на начало списка
	New->pNext = Head;
	//3) голову списка переводим на новый элемент
	Head = New;*/

	Head = new Element<T>(Data, Head);
	size++;
}

template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);
	//Element<T>* New = new Element(Data);  //1)создаем новый элемент
	Element<T>* Temp = Head;
	while (Temp->pNext)                       //2)доходим до конца списка
		Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data);                 //3)добавляем элемент в конец списка
	size++;
}

template<typename T>void ForwardList<T>::insert(int Index, T Data)
{
	if (Index == 0)return push_front(Data);
	if (Index > size)return;

	//1) создаем новый элемент:
	//Element* New = new Element(Data);

	//2) Доходим до нужного элемента
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

	//3) Вставляем новый элемент в список:
	/*New->pNext = Temp->pNext;
	Temp->pNext = New;*/
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}

//                            Erasing elements
template<typename T>void ForwardList<T>::pop_front()
{
	Element<T>* Erased = Head;  //1)запоминаем адрес удаляемого элемента
	Head = Head->pNext;      //2)исключаем элемент из списка
	delete Erased;           //3)удаляем элемент из памяти
	size--;
}

template<typename T>void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}


template<typename T>void ForwardList<T>::erase(int Index)
{
	if (Index == 0)return pop_front(); //если индекс равен нулю, вызываем pop_front (удаление первого элемента в списке)
	if (Index >= size)return;
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;  //1) Доходим до нужного элемента (предыдущий перед удаляемым
	Element<T>* Erased = Temp->pNext;  //2)запоминаем адрес удаляемого элемента
	Temp->pNext = Erased->pNext;    //3)адрес предыдущего элемента привязываем к следующему за удаляемым элементом, исключаем элемент из списка
	delete Erased;    //4) удаляем элемент с индексом
	size--;                //5)уменьшаем размер списка
}

//   Methods:
template<typename T>void ForwardList<T>::print()const
{
	//Element* Temp = Head;   //Temp - итератор (указатель, при помощи которого 
	////можно получить доступ к элементам структуры данных)
	//while (Temp)
	//{
	//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	//	Temp = Temp->pNext;  //переход на следующий элемент
	//}
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов: " << Element::count << endl;
}

////////////////  class definition END - конец определения класса            ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
