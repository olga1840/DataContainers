#include<iostream>
using namespace std;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//     Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/

		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext= New;
		Tail = New;*/
				
		Tail = Tail->pNext = new Element(Data,nullptr,Tail);
		size++;
	}
	void insert(int Index, int Data)
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
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
				
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	//                  Removing elements:
	void pop_front()
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
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void  erase(int Index)
	{
		if (Index == 0)return pop_front(); 
		if (Index >= size)return;
		Element* Temp;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;  //1) Доходим до нужного элемента (предыдущий перед удаляемым
		Element* Erased = Temp->pNext;  //2)запоминаем адрес удаляемого элемента
		Temp->pNext = Erased->pNext;    //3)адрес предыдущего элемента привязываем к следующему за удаляемым элементом, исключаем элемент из списка
		delete Erased;    //4) удаляем элемент с индексом
		size--;                //5)уменьшаем размер списка
	}

	

	//                    Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp=Temp->pNext)
		{
			cout << Temp->pPrev<< tab << Temp << tab << Temp->Data << tab << Temp-> pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for(Element* Temp = Tail; Temp; Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	/*for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();*/

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();

	/*int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();*/
#endif // BASE_CHECK

}