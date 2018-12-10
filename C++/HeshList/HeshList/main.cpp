#include <iostream>
#include <string>
using namespace std;
struct check
{
	int number;
	string key;
	check* next;
	check* same;
	check() { number = 0; key = " "; };
};
class table
{
private:
	int n;
	check* slots;
	int numb[1000];
public:
	table() { slots = NULL; }
	table(int);
	void Add(int, string);
	void AddInto(int, string, int);
	void Remove(int);
	void Show();
	check* Pop(int);
	int operator[](string);
	//~table(void);
};

void table::Add(int entered_number, string entered_key)
{
	check* temp = new check;
	temp->number = entered_number;
	temp->key = entered_key;
	int int_key = 0;
	for (int i = 0;i < entered_key.length();i++)
	{
		int_key += entered_key[i];
	}
	if (numb[int_key] == -1)
	{
		temp->next = slots;
		slots = temp;
		numb[int_key] = n;
		n++;
	}
	else
	{
		this->Pop(numb[int_key])->same = temp;
	}
	
}
void table::AddInto(int entered_number, string entered_key, int place)
{
	if (place == n)
	{
		this->Add(entered_number, entered_key);
	}
	else
	{
		check* temp = this->Pop(place);
		check* tail = temp->next;
		check* new_temp = new check;
		temp->next = new_temp;
		new_temp->key = entered_key;
		new_temp->number = entered_number;
		new_temp->next = tail;
		int int_key = 0;
		for (int i = 0;i < entered_key.length();i++)
		{
			int_key += entered_key[i];
		}
		numb[int_key] = n;
		n++;
	}

}
void table::Remove(int place)
{
	check* prev;
	if (place == n - 1)
	{
		slots = this->Pop(place)->next;
	}
	else if (place == 0)
	{
		delete this->Pop(place + 1)->next;
	}
	else
	{
		prev = this->Pop(place + 1);
		check* tail = new check;
		tail = prev->next;
		prev->next = tail->next;
		delete tail;
	}
	n--;
}
void table::Show()
{
	check* temp = slots;
	int i = 1;
	while (i <= n)
	{
		cout << "Table [" << n - i << "] elements number is: " << temp->number << endl;
		cout << "Table [" << n - i << "] elements key is: " << temp->key << endl;
		temp = temp->next;
		i++;
	}
}
table::table(int mum)
{
	fill(numb, numb + 1000, -1);
	n = 0;
	int ent_num;
	string ent_key;
	for (int i = 0;i < mum;i++)
	{
		cout << "Enter [" << i + 1 << "] slot number:" << endl;
		cin >> ent_num;
		cout << "Enter [" << i + 1 << "] slot key:" << endl;
		cin >> ent_key;
		this->Add(ent_num, ent_key);
	}
}
check* table::Pop(int open_number)
{
	check *temp = slots;
	if ((slots != NULL) && (open_number <= n))
	{
		for (int i = 0;i < n - open_number - 1;i++)
		{
			temp = temp->next;
		}
	}
	return temp;
}
//int hash_func(string entered_key)//хеш функція
//{
//	const int p = 2;
//	int hash = 0, p_pow = 2;
//	int quantity = 'z' - 'a' + 1;
//	hash += (entered_key[0] - 'a' + 1)*quantity;
//	for (int i = 1; i<entered_key.length(); ++i)
//	{
//		hash += (entered_key[i] - 'a' + 1) * p_pow;
//		p_pow *= p;
//	}
//	hash = hash % 2000;
//	return hash;
//}
int table::operator[](string search_key)
{
	int int_key = 0;
	for (int i = 0;i < search_key.length();i++)
	{
		int_key += search_key[i];
	}
	check *temp = this->Pop(numb[int_key]);
	if (search_key == temp->key)
	{
		return temp->number;
	}
	else
	{
		if (temp->same->key == search_key)
		{
			return temp->same->number;
		}
		else
		{
			cout << "There is no slot with this key" << endl;
			return 0;
		}	
	}

}
int main()
{
	cout << "Please enter list data: " << endl;
	int a = 4;
	table first(a);
	string answer;
	string key_;
	int place_, number_;
	bool exit = false;;
	do
	{
		cout << endl;
		cout << "To open slot write: open" << endl;
		cout << "To add new slot write: add" << endl;
		cout << "To remove slot write: remove" << endl;
		cout << "To show all list write: show" << endl;
		cout << "To exit write: exit" << endl;
		cin >> answer;
		if (answer == "open")
		{
			cout << "Enter key:" << endl;
			cin >> key_;
			cout << "The number is: " << first[key_] << endl;
		}
		else if (answer == "add")
		{
			cout << "Enter place: " << endl;
			cin >> place_;
			cout << "Enter key: " << endl;
			cin >> key_;
			cout << "Enter number: " << endl;
			cin >> number_;
			first.AddInto(number_, key_, place_);
		}
		else if (answer == "remove")
		{
			cout << "Enter place: " << endl;
			cin >> place_;
			first.Remove(place_);
		}
		else if (answer == "show")
		{
			first.Show();
		}
		else if (answer == "exit")
		{
			exit = true;
		}
		else
		{
			cout << "Wrong command" << endl;
		}
	} while (exit == false);
}