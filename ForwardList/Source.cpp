#include<iostream>
using namespace std;
using std::cout;

#define tab "\t"

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

template<typename T>class ForwardList    //forward - односвязный, однонаправленный
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


//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY

//#define HOME_WORK_1



void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_back();

	int value;
	int index;
	cout << "Введите индлекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();

	/*ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();*/

	/*int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();*/
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	//Range-based for 
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY


	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab; cout << endl;

	ForwardList<double> d_list = { 2.7, 3.14, 1.9, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;



#ifdef HOME_WORK_1
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // HOME_WORK_1

}