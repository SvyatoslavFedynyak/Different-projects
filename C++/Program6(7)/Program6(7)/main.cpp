#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
class transport_line
{
private:
	string first_stop, last_stop;
	int num_of_stop;
	double length;
public:
	transport_line() {};
	transport_line(string fs, string ls, int nos, double l) : first_stop(fs), last_stop(ls), num_of_stop(nos), length(l) {};
	double ReturnLength() { return length; }
	int ReturnNum() { return num_of_stop; }
	string ReturnFirstStop() { return first_stop; }
	void Show()
	{
		cout << "First stop is: " << first_stop << endl;
		cout << "Last stop is: " << last_stop << endl;
		cout << "Num of stop is " << num_of_stop << endl;
		cout << "Length is " << length << endl;
	}
};
bool length_bool(transport_line first, transport_line second)
{
	if (first.ReturnLength() < second.ReturnLength())return true;
	else return false;
}
class medium_value_bool
{
private:
	double X;
public:
	medium_value_bool(double _x) :X(_x) {};
	bool operator()(transport_line& tl)
	{
		if ((tl.ReturnLength() / tl.ReturnNum()) < X)return true;
		else return false;
	}
};
class if_fs_x
{
private:
	string x;
public:
	if_fs_x(string _x) :x(_x) {};
	bool operator()(transport_line& tl)
	{
		if (tl.ReturnFirstStop() == x)return false;
		else return true;
	}
};
bool less_num(transport_line first, transport_line second)
{
	if (first.ReturnNum() < second.ReturnNum())return true;
	else return false;
}
class cout_if_max
{
private:
	vector <transport_line> vect;
public:
	cout_if_max(vector <transport_line> _vect) :vect(_vect) {};
	void operator()(transport_line& el)
	{
		if (el.ReturnNum() == max_element(vect.begin(), vect.end(), less_num)->ReturnNum())
			el.Show();
	}
};
int main()
{
	ifstream fin("file.txt");
	list <transport_line> trans_list;
	string first_st, last_st;
	int n_o_s;
	double len;
	do
	{
		if (fin.eof())break;
		fin >> first_st >> last_st >> n_o_s >> len;
		trans_list.push_back(transport_line(first_st, last_st, n_o_s, len));
	} while (!fin.eof());
	vector <transport_line> trans_vector;
	trans_vector.resize(trans_list.size());
	copy(trans_list.begin(), trans_list.end(), trans_vector.begin());
	sort(trans_vector.begin(), trans_vector.end(), length_bool);
	cout << "Enter double X for 1-st X check:" << endl;
	double X;
	cin >> X;
	cout << "Num of lines which delta<X: " << count_if(trans_vector.begin(), trans_vector.end(), medium_value_bool(X)) << endl;
	list <transport_line> new_list;
	new_list.resize(trans_vector.size());
	cout << "Enter string X for 2-st X check:" << endl;
	string x;
	cin >> x;
	remove_copy_if(trans_vector.begin(), trans_vector.end(), new_list.begin(), if_fs_x(x));
	for_each(trans_vector.begin(), trans_vector.end(), cout_if_max(trans_vector));
	system("pause");
}