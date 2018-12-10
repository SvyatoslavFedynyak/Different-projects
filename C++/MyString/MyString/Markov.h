#pragma once
#include "mystring.h"
#include <time.h>
struct rule
{
	mystring first;
	mystring second;
	rule() :first(""), second("") {};
};
const rule* rules = new rule[7];

class markov
{
private:
	mystring word;
	rule rules[8];
public:
	markov(mystring word_);
	markov();
	bool transform(rule);
	mystring GetWord() { return word; }
	void Show() { cout << word; }
	friend mystring AlgoritmMarkova(markov word_);
	friend mystring AlternativeAlgoritmMarkova(markov word_);
};
markov::markov()
{
	rules[0].first = "|b";
	rules[0].second = "ba|";
	rules[1].first = "ab";
	rules[1].second = "ba";
	rules[2].first = "b";
	rules[2].second = "_";
	rules[3].first = "*|";
	rules[3].second = "b*";
	rules[4].first = "*";
	rules[4].second = "c";
	rules[5].first = "|c";
	rules[5].second = "c";
	rules[6].first = "ac";
	rules[6].second = "c|";
	rules[7].first = "c";
	rules[7].second = "_";
	srand(time(0));
	int num;
	char symb;
	char* char_word = new char[100];
	for (int i = 0;i < 100;i++)
	{
		num = rand() % 6;
		switch (num)
		{
		case 0:symb = 'a';break;
		case 1:symb = 'b';break;
		case 2:symb = 'c';break;
		case 3:symb = '*';break;
		case 4:symb = '|';break;
		case 5:symb = '_';break;
		}
		char_word[i] = symb;
	}
	word = char_word;
}
markov::markov(mystring word_)
{
	rules[0].first = "|b";
	rules[0].second = "ba|";
	rules[1].first = "ab";
	rules[1].second = "ba";
	rules[2].first = "b";
	rules[2].second = "_";
	rules[3].first = "*|";
	rules[3].second = "b*";
	rules[4].first = "*";
	rules[4].second = "c";
	rules[5].first = "|c";
	rules[5].second = "c";
	rules[6].first = "ac";
	rules[6].second = "c|";
	rules[7].first = "c";
	rules[7].second = "_";
	word = word_;
}
bool markov::transform(rule r)
{
	if (word.find(r.first).start == -1)
	{
		return false;
	}
	else
	{
		word.replace(r.first, r.second);
		return true;
	}
}
mystring AlgoritmMarkova(markov word_)
{
	bool able_to_transform[8] = { true, true, true, true, true, true, true, true };
	int i = 0;
	while (able_to_transform[0] == true ||
		able_to_transform[1] == true ||
		able_to_transform[2] == true ||
		able_to_transform[3] == true ||
		able_to_transform[4] == true ||
		able_to_transform[5] == true ||
		able_to_transform[6] == true ||
		able_to_transform[7] == true)
	{
		able_to_transform[i] = word_.transform(word_.rules[i]);
		i++;
		if (i == 8)
		{
			i = 0;
		}
	}
	return word_.word;
}
mystring AlternativeAlgoritmMarkova(markov word_)
{
	char new_letter;
	char buffer;
	for (int i = 0;i < word_.word.length_of_string();i++)
	{
		new_letter = word_.word[i];
		buffer = new_letter;
		new_letter += word_.word.length_of_string()+1;
		mystring new_string = new_letter;
		word_.word.replace(buffer, new_string);
	}
	return word_.word;
}