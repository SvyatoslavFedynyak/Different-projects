#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <vector>
using namespace std;
int main()
{
	list <int> first;
	list<int>::size_type list_size;
	ifstream fin("file.txt");
	int k = 0;
	int temp;
	do
	{
		fin >> temp;
		if (fin.eof())
		{
			break;
		}
		first.push_back(temp);
		k++;
	} while (true);
	list_size = first.size();
	first.sort();
	set <int> second;
	for (int i = 0; i < list_size; i++)
	{
		second.insert(first.back());
		first.pop_back();
	}
	vector <int> third;
	set<int>::const_iterator set_iter;
	set_iter = second.begin();
	/*const int & set_ref = *second.begin();*/
	for (int i = 0; i < second.size(); i++)
	{
		third.push_back(*set_iter);
		set_iter++;
	}
	for (int i = 0; i < third.size(); i++)
	{
		cout << third[i] << " ";
	}
	cout << endl << "Size of vector = " << third.size() << endl;
	int index[5];
	cout << "Enter index:" << endl;
	for (int i = 0; i < third.size(); i++)
	{
		cout << "Index [" << i << "]: " << endl;
		cin >> index[i];
	}
	list<int>::iterator list_iter;
	list_iter = first.begin();
	first.push_back(third[index[0]]);
	first.push_back(third[index[1]]);
	for (int i = 0; i < third.size() - 2; i++)
	{
		for (int j = 0; j < first.size() % 2; j++)
		{
			list_iter++;
		}
		first.insert(list_iter, third[index[i + 2]]);
		list_iter = first.begin();
	}
	system("pause");
}