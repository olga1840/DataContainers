#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

class Tree
{protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft=nullptr, Element* pRight=nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int i : il)insert(i);
	}
	Tree(const Tree& other) :Tree()
	{
		Copy(other.Root);
	}
	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth()const
	{
		return Depth(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void Clear()
	{
		return Clear(Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return  Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return  Sum(Root->pLeft) + Sum(Root->pRight)+Root->Data;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		int l_depth = Depth(Root->pLeft) +1;
		int r_depth = Depth(Root->pRight)+1;
		return l_depth < r_depth ? r_depth : l_depth;
		/*if (Root == nullptr)return 0;
			else
			{
				int lchild = Depth(Root->pLeft);
				int rchild = Depth(Root->pRight);
				return 1 + (lchild > rchild ? lchild : rchild);
			}*/
		/*if (Root == nullptr)return 0;
		if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)return Depth(Root->pLeft) + 1;
		else return Depth(Root->pRight) + 1;*/
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
		/*if (Root == nullptr)delete Root;
		if (Root != nullptr)
		{
			if (Root->pLeft != nullptr) Clear(Root->pLeft);
			if (Root->pRight != nullptr) Clear(Root->pRight);
			delete Root;
		}*/
	}
	void Copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		Copy(Root->pLeft);
		Copy(Root->pRight);
	}
	void Erase(Element* Root, int Data)
	{
		if (Root == nullptr) return;
		if (Data < Root->Data) return Erase(Root->pLeft, Data);
		else if (Data > Root->Data) return Erase(Root->pRight, Data);
		else
		{

		}
	}
};
 

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if(Data>Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

//#define BASE_CHECK
#define DEPTH_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	//tree.Clear();

	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}

	tree2.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree2.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree2.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree2.Count() << endl;
	cout << "Сумма элементов дерева: " << tree2.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree2.Avg() << endl;
	cout << "Глубина дерева: " << tree2.Depth() << endl;
	//tree2.Clear();
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 48, 49, 85, 91};
	tree.print();
	cout << "Глубина дерева: " << tree.Depth() << endl;

	Tree tree2 = tree;
	tree2.print();

#endif // DEPTH_CHECK

}