#include<iostream>
using namespace std;

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
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
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

	int minValue(Element* Root)
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)
	{
		if (Root == nullptr)return 0;
		else return  Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)
	{
		if (Root == nullptr)return 0;
		else return  Sum(Root->pLeft) + Sum(Root->pRight)+Root->Data;
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int Depth(Element* Root)
	{
		if (Root == nullptr)return 1;
		else 
		{
			int lchild = Depth(Root->pLeft);
			int rchild = Depth(Root->pRight);
			return 1 + (lchild > rchild ? lchild : rchild);
		}
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)delete Root;
		if (Root != nullptr)
		{
			if (Root->pLeft != nullptr) Clear(Root->pLeft);
			if (Root->pRight != nullptr) Clear(Root->pRight);
			delete Root;
		}
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

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree.Count(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.Sum(tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth(tree.getRoot()) << endl;

	tree.Clear(tree.getRoot());

	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}
	
	tree2.print(tree2.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree2.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree2.maxValue(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree2.Count(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree2.Sum(tree2.getRoot()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree2.Avg() << endl;
	cout << "Глубина дерева: " << tree2.Depth(tree2.getRoot()) << endl;
	tree2.Clear(tree2.getRoot());
}