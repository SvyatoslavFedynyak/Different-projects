#include <iostream>
#include <utility>
#include <list>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;
template <typename T>
class Bakalavr
{
private:
	string name;
	int num_of_zal;
	list<pair<string, T>> subj;
public:
	Bakalavr() {};
	Bakalavr(string n, int num, list<pair<string, T>> s) :name(n), num_of_zal(num), subj(s) {};
	void Print()
	{
		cout << name << num_of_zal;
		list<pair<string, T>>::iterator list_iter = subj.begin();
		for (int i = 0;i < subj.size();i++)
		{
			cout << list_iter->first << " " << list_iter->second;
		}
	}
	void AddSubj(string s, T mark)
	{
		subj.push_back(make_pair(s, mark));
	}
	int returnZal() { return num_of_zal; }
	string returnNmae() { return name; }
	T retunr_mark_of_name(string n)
	{
		list<pair<string, T>>::iterator list_iter = subj.begin();
		for (int i = 0;i < subj.size();i++)
		{
			if (list_iter->first == n)return ist_iter->second;
		}
	}
	int some_mark(T mark)
	{
		list<pair<string, T>>::iterator list_iter = subj.begin();
		int res = 0;
		for (int i = 0;i < subj.size();i++)
		{
			if (list_iter->second == mark)res++;
		}
		return res;
	}
	bool only_A()
	{
		bool res = true;
		list<pair<string, T>>::iterator list_iter = subj.begin();
		for (int i = 0;i < subj.size();i++)
		{
			if (!(list_iter->second == 'A')) { res = false; break; }
		}
		return res;
	}
	list<pair<string, char>> ReturnCharSubj() { return subj; }
	list<pair<string, double>> ReturnDoubleSubj() { return subj; }
	double MediumMark() 
	{
		double sum=0;
		list<pair<string, T>>::iterator list_iter = subj.begin();
		for (int i = 0;i < subj.size();i++)
		{
			sum += list_iter->second;
		}
		return sum / subj.size();
	}
};
bool has_e_or_d(list<pair<string, char>> subj_list)
{
	list<pair<string, char>>::iterator list_iter = subj_list.begin();
	for (int i = 0;i < subj_list.size();i++)
	{
		if (list_iter->second == 'E' || list_iter->second == 'D')return true;
	}
	return false;
}
bool no_prog(Bakalavr<char> b)
{
	list<pair<string, char>>::iterator list_iter = b.ReturnCharSubj().begin();
	for (int i = 0;i < b.ReturnCharSubj().size();i++)
	{
		if (list_iter->first == "prog")return false;
	}
	return true;
}
bool compare(Bakalavr<char> first, Bakalavr<char> second)
{
	if (first.MediumMark() > second.MediumMark())return true;
}
bool medium_mark_more_4(Bakalavr<double> b)
{
	if (b.MediumMark() >= 4)return true;
}
bool les_than_5_subj(Bakalavr<double> b)
{
	if (b.ReturnDoubleSubj().size() < 5)return true;
}
void print(Bakalavr<double> b)
{
	b.Print();
}
int main()
{
	int num_of_b;
	cin >> num_of_b;
	string name;int zal, num_of_subj;
	list<Bakalavr<char>> bak_list;
	for (int i = 0;i < num_of_b;i++)
	{
		cin >> name >> zal>>num_of_subj;
		list<pair<string, char>> subj_list;
		string subj; char mark;
		for (int j = 0;j < num_of_subj;j++)
		{
			cin >> subj >> mark;
			subj_list.push_back(make_pair(subj, mark));
		}
		bak_list.push_back(Bakalavr<char>(name, zal, subj_list));
	}
	list<Bakalavr<char>>::iterator list_iter = bak_list.begin();
	int num_of_best=0;
	for (int i = 0;i < bak_list.size();i++)
	{
		if (list_iter->only_A())num_of_best++;
	}
	cout << num_of_best;
	list_iter = bak_list.begin();
	for (int i = 0; i < bak_list.size();i++)
	{
		if (has_e_or_d(list_iter->ReturnCharSubj()))cout << list_iter->returnNmae();
	}
	list_iter = bak_list.begin();
	for (int i = 0; i < bak_list.size();i++)
	{
		if (no_prog(*list_iter)) { cout << "Yes" << endl; break; }
	}
	list<Bakalavr<double>> bak_list1;
	bak_list1.resize(10);
	ifstream fin("file.txt");
	//copy(istream_iterator<Bakalavr<double>>(fin), istream_iterator<Bakalavr<double>>(), bak_list1.begin());
	do
	{
		string name;int zal, num_of_subj;
		for (int i = 0;i < num_of_b;i++)
		{
			fin >> name >> zal >> num_of_subj;
			list<pair<string, double>> subj_list;
			string subj; double mark;
			for (int j = 0;j < num_of_subj;j++)
			{
				fin >> subj >> mark;
				subj_list.push_back(make_pair(subj, mark));
			}
			bak_list1.push_back(Bakalavr<double>(name, zal, subj_list));
			if (fin.eof())break;
		}
	} while (true);
	list<Bakalavr<double>>::iterator iter = bak_list1.begin();
	for_each(bak_list1.begin(), bak_list1.end(), print);
	//sort(bak_list1.begin(), bak_list1.end(), compare);
	cout<<count_if(bak_list1.begin(), bak_list1.end(), medium_mark_more_4)<<endl;
	if (count_if(bak_list1.begin(), bak_list1.end(), les_than_5_subj) >= 1)cout << "Yes";
	system("pause");
}