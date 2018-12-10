#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include "list"
using namespace std;
list <string> transform_into_list(string sentense)
{
	list <string> list_sentense;
	string word;
	int i = 0, length = 0;
	do
	{
		while (sentense[i] != ' ')
		{
			i++;
			length++;
			if (i == sentense.size())
			{
				break;
			}
		}
		word = sentense.substr(i - length, length);
		list_sentense.push_back(word);
		if (i == sentense.size())
		{
			break;
		}
		length = 0;
		i++;
	} while (true);
	return list_sentense;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	pair <string, string> translate_pair;
	list <pair<string, string>> translate_box;
	ifstream fin("translate_list.txt");
	string temp1, temp2;
	do
	{
		fin >> temp1;
		fin >> temp2;
		translate_pair.first = temp1;
		translate_pair.second = temp2;
		translate_box.push_back(translate_pair);
		if (fin.eof())
		{
			break;
		}
	} while (true);
	cout << "Введіть речення (українською)" << endl;
	string sentense;
	getline(cin, sentense);
	list <string> list_sentense = transform_into_list(sentense);
	list <string>::iterator sentense_iterator = list_sentense.begin();
	list <pair<string, string>>::iterator box_iterator = translate_box.begin();
	for (int i = 0;i < list_sentense.size();i++)
	{
		for (int j = 0;j < translate_box.size();j++)
		{
			if (*sentense_iterator == box_iterator->first)
			{
				*sentense_iterator = box_iterator->second;
				break;
			}
			else
			{
				box_iterator++;
			}
		}
		box_iterator = translate_box.begin();
		sentense_iterator++;
	}
	sentense_iterator = list_sentense.begin();
	for (int i = 0;i < list_sentense.size();i++)
	{
		cout << *sentense_iterator << " ";
		sentense_iterator++;
	}
	cout << endl;
	string new_ua_word, new_eng_word;
	cout << "Введіть нові слова в перекладач:" << endl;
	cout << "Введіть українське:" << endl;
	cin >> new_ua_word;
	cout << "Введіть англійське:" << endl;
	cin >> new_eng_word;
	ofstream fout("translate_list.txt", ios::app);
	fout << " ";
	fout << new_ua_word;
	fout << " ";
	fout << new_eng_word;
	system("pause");
}