#include <iostream>
#include "Markov.h"
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
mystring::mystring(char letter)
{
	length = 1;
	word = new line;
	word->letter = letter;
	word->next = nullptr;
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
	bool present=false;
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
		temp = replaced_word.Pop(new_line.length-1);
		new_temp = this->Pop(local_place.end+1);
		temp->next = new_temp;
		*this = replaced_word;
	}
	else if (local_place.start == -1)
	{

	}
	else
	{
		replaced_word.word = word;
		tail = this->Pop(local_place.end+1);
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
int main()
{
	mystring first;
	cin >> first;
	markov first_markov(first);
	cout << first << endl;
	cout<<AlternativeAlgoritmMarkova(first_markov)<<endl;
	/*markov first_markov;
	cout<<first_markov.GetWord()<<endl<<endl;
	AlgoritmMarkova(first_markov);*/
	/*cout << AlgoritmMarkova(first_markov) << endl;*/
	system("pause");
}