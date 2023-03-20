#include<iostream>
using namespace std;
using std::cout;

#define tab "\t"

class Element
{
	int Data;      //значение элемента
	Element* pNext; //адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0; //инициализируем статическую переменную, объявленную в классе  'Element'

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList    //forward - односвязный, однонаправленный
{
	Element* Head;    //голова списка - содержит указатель на нулевой элемент списка
	int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr; //Если список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList() //il - initializer list
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//   Adding elements:
	void push_front(int Data)
	{
		/*//1) создаем новый элемент
		Element* New = new Element(Data);
		//2) новый элемент должен указывать на начало списка
		New->pNext = Head;
		//3) голову списка переводим на новый элемент
		Head = New;*/
		
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);  //1)создаем новый элемент
		Element* Temp = Head;
		while (Temp->pNext)                       //2)доходим до конца списка
			Temp = Temp->pNext;
		Temp->pNext = New;                 //3)добавляем элемент в конец списка
		size++;
	}

	void insert(int Index, int Data)
	{
		if(Index == 0)return push_front(Data);
		if (Index > size)return;

		//1) создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) Вставляем новый элемент в список:
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//                            Erasing elements
	void pop_front()
	{
		Element* Erased = Head;  //1)запоминаем адрес удаляемого элемента
		Head = Head->pNext;      //2)исключаем элемент из списка
		delete Erased;           //3)удаляем элемент из памяти
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	
	void  erase(int Index)
	{
		if (Index == 0)return pop_front(); //если индекс равен нулю, вызываем pop_front (удаление первого элемента в списке)
		if (Index >= size)return;
		Element* Temp = Head; 
		for (int i = 0; i < Index -1; i++) Temp = Temp->pNext;  //1) Доходим до нужного элемента (предыдущий перед удаляемым
		Element* Erased = Temp->pNext;  //2)запоминаем адрес удаляемого элемента
		Temp->pNext = Erased->pNext;    //3)адрес предыдущего элемента привязываем к следующему за удаляемым элементом, исключаем элемент из списка
		delete Erased;    //4) удаляем элемент с индексом
		size--;                //5)уменьшаем размер списка
	}

	//   Methods:
	void print()const
	{
		//Element* Temp = Head;   //Temp - итератор (указатель, при помощи которого 
		////можно получить доступ к элементам структуры данных)
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;  //переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY

//#define HOME_WORK_1
#define RANG_-BASED_FOR_LIST

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

#ifdef RANGE_BASED_FOR_LIST

	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab; cout << endl;
#endif // RANGE_BASED_FOR_LIST



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