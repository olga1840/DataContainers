#include<iostream>
using namespace std;

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
};

int Element::count = 0; //инициализируем статическую переменную, объявленную в классе  'Element'

class ForwardList    //forward - односвязный, однонаправленный
{
	Element* Head;    //голова списка - содержит указатель на нулевой элемент списка
	int size;
public:
	ForwardList()
	{
		Head = nullptr; //Если список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
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
		Element* New = new Element(Data);

		//2) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3) Вставляем новый элемент в список:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
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
	    Element* Temp = Head; 
		for (int i = 0; i < Index -1; i++) Temp = Temp->pNext;  //1) Доходим до элемента с нужным индексом
		Element* Erased = Temp->pNext;  //2)исключаем элемент с указанным индексом из списка
		Temp->pNext = Erased->pNext;
		delete Erased;    //3) удаляем элемент с индексом
		size--;                //4)уменьшаем размер списка
	}

	//   Methods:
	void print()const
	{
		Element* Temp = Head;   //Temp - итератор (указатель, при помощи которого 
		//можно получить доступ к элементам структуры данных)
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;  //переход на следующий элемент
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
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

	/*int value;
	int index;
	cout << "Введите индлекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);*/
	list.print();
	
	/*ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();*/

	int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}