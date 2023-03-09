#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;      //значение элемента
	Element* pNext; //адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList    //forward - односв€зный, однонаправленный
{
	Element* Head;    //голова списка - содержит указатель на нулевой элемент списка
public:
	ForwardList()
	{
		Head = nullptr; //≈сли список пуст, то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//   Adding elements:
	void push_front(int Data)
	{
		//1) создаем новый элемент
		Element* New = new Element(Data);
		//2) новый элемент должен указывать на начало списка
		New->pNext = Head;
		//3) голову списка переводим на новый элемент
		Head = New;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);  //1)создаем новый элемент
		Element* Temp = Head;
		while (Temp->pNext)                       //2)доходим до конца списка
			Temp = Temp->pNext;
		Temp->pNext = New;                 //3)добавл€ем элемент в конец списка
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
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();*/
}