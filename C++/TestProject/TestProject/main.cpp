#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
	ifstream fin("file.txt");
	vector<string> text;
	text.resize(5);
	copy(istream_iterator<string> (fin), istream_iterator<string>(), text.begin());
	cout << text[0]<< text[1]<< text[2] << endl;
	system("pause");

}