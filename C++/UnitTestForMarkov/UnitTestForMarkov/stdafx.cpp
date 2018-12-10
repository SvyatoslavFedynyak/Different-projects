// stdafx.cpp: файл исходного кода, содержащий стандартные включаемые элементы
// UnitTestForMarkov.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"
// TODO: Установите ссылки на любые требующиеся дополнительные заголовки в файле STDAFX.H
// , а не в данном файле
using namespace std;
struct line_place
{
	int start;
	int end;
	line_place() :start(0), end(0) {};
};
struct line
{
	char letter;
	line* next;
	line() :letter(' '), next(nullptr) {};
	line(char let) { letter = let; next = nullptr; }
};
class mystring
{
private:
	int length;
	line* word;

public:
	mystring() :length(0), word(nullptr) {};
	mystring(char* arr);
	mystring(mystring&);
	char operator[](int);
	int length_of_string() { return length; };
	line* Pop(int);
	line_place find(mystring);
	mystring select(int, int);
	bool operator==(mystring&);
	void replace(mystring, mystring&);
	friend istream& operator >> (istream&, mystring&);
	friend ostream& operator<<(ostream&, mystring&);
	void Show();
};
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
mystring::mystring(char* arr)
{
	int num = 0;
	do
	{
		if (arr[num] == (char)nullptr)
		{
			break;
		}
		else
		{
			num++;
		}
	} while (true);
	length = num;
	line* temp = new line;
	word = new line;
	word->letter = arr[0];
	word->next = temp;
	for (int i = 1;i < length;i++)
	{
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->letter = arr[i];
		if (arr[i + 1] == (char)nullptr)
		{
			break;
		}
		else
		{
			temp->next = new line;
		}
	}
}
mystring::mystring(mystring& arr)
{
	length = arr.length;
	word = new line;
	line* temp = arr.word;
	line* new_temp = word;
	for (int i = 0;i < length - 1;i++)
	{
		new_temp->letter = temp->letter;
		new_temp->next = new line;
		temp = temp->next;
		new_temp = new_temp->next;
	}
	new_temp->letter = temp->letter;
}
//char* mystring::TransformIntoChar()
//{
//	line* temp = word;
//	char* new_char = new char[length];
//	for (int i = 0;i < length;i++)
//	{
//		new_char[i] = temp->letter;
//		temp = temp->next;
//	}
//	return new_char;
//}
bool mystring::operator==(mystring& check)
{
	if (length == check.length)
	{
		bool real = true;
		line* temp = word;
		line* check_temp = check.word;
		for (int i = 0;i < length;i++)
		{
			if (temp->letter == check_temp->letter)
			{
				temp = temp->next;
				check_temp = check_temp->next;
			}
			else
			{
				real = false;
				break;
			}
		}
		return real;
	}
	else
	{
		return false;
	}
}
line* mystring::Pop(int place)
{
	line* temp = word;
	for (int i = 0;i < place;i++)
	{
		temp = temp->next;
	}
	return temp;

}
mystring mystring::select(int len, int place)
{
	mystring new_item(*this);
	if (new_item.length < len + place)
	{
		len = length - place;
	}
	new_item.length = len;
	new_item.word = new_item.Pop(place);
	line* temp = new_item.word;
	for (int i = 0;i < len - 1;i++)
	{
		temp = temp->next;
		if (temp->next == nullptr)
		{
			break;
		}
	}
	temp->next = nullptr;
	return new_item;
}
line_place mystring::find(mystring find_line)
{
	line_place find_line_place;
	mystring our_word(*this);
	line* temp = our_word.word;
	bool present = false;
	for (int i = 0;i < length - find_line.length + 1;i++)
	{
		if (find_line[0] == temp->letter)
		{
			if (this->select(find_line.length, i) == find_line)
			{
				find_line_place.start = i;
				find_line_place.end = i + find_line.length - 1;
				present = true;
				break;
			}
		}
		temp = temp->next;
	}
	if (present == true)
	{
		return find_line_place;
	}
	else
	{
		find_line_place.start = -1;
		find_line_place.end = -1;
		return find_line_place;
	}
}
void mystring::replace(mystring local, mystring& new_line)
{
	mystring replaced_word;
	replaced_word.length = length - local.length + new_line.length;
	line* temp;
	line* new_temp;
	line* tail;
	line_place local_place = this->find(local);
	if (local_place.start == 0)
	{
		replaced_word.word = new_line.word;
		temp = replaced_word.Pop(new_line.length - 1);
		new_temp = this->Pop(local_place.end + 1);
		temp->next = new_temp;
		*this = replaced_word;
	}
	else if (local_place.start == -1)
	{

	}
	else
	{
		replaced_word.word = word;
		tail = this->Pop(local_place.end + 1);
		temp = replaced_word.Pop(local_place.start - 1);
		temp->next = new_line.word;
		new_temp = new_line.Pop(new_line.length - 1);
		new_temp->next = tail;
		*this = replaced_word;
	}
}
char mystring::operator[](int number)
{
	if (number < length)
	{
		return this->Pop(number)->letter;
	}
	else
	{
		return ' ';
	}
}
void mystring::Show()
{
	cout << word->letter;
	line* temp = word->next;
	for (int i = 1;i < length;i++)
	{
		if (temp != nullptr)
		{
			cout << temp->letter;
			if (temp->next != nullptr)
			{
				temp = temp->next;
			}
		}
		else
		{
			break;
		}

	}
	cout << endl;
}
ostream& operator<<(ostream& out, mystring& cons)
{
	line* temp = cons.word;
	for (int i = 0;i < cons.length;i++)
	{
		if (temp != nullptr)
		{
			cout << temp->letter;
			if (temp->next != nullptr)
			{
				temp = temp->next;
			}
		}
		else
		{
			break;
		}

	}
	return out;
}
istream& operator >> (istream& in, mystring& cons)
{
	char* arr = new char[1000];
	in >> arr;
	cons = arr;
	return in;
}