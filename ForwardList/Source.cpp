#include"ForwardList.cpp"


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