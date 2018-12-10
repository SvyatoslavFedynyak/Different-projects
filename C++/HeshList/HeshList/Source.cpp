#include <iostream>
#include <string>
using namespace std;
struct check
{
	int number;
	string key;
	check* next;
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
	void Show();
	check Pop(int);
	int operator[](string);
	//~table(void);
};

void table::Add(int entered_number, string entered_key)
{
	check* temp = new check;
	temp->number = entered_number;
	temp->key = entered_key;
	temp->next = slots;
	slots = temp;
	int int_key=0;
	for(int i=0;i<entered_key.length();i++)
	{
		int_key+=entered_key[i];
	}
	numb[int_key]=n;
	n++;
}
void table::Show()
{
	check* temp = slots;
	int i = 1;
	while (temp != NULL)
	{
		cout << "Table [" << n-i << "] elements number is: " << temp->number << endl;
		cout << "Table [" << n-i << "] elements key is: " << temp->key << endl;
		temp = temp->next;
		i++;
	}
}
table::table(int mum)
{
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
check table::Pop(int open_number)
{
	check *temp = slots;
	if ((slots != NULL) && (open_number <= n))
	{
		for (int i = 1;i < open_number;i++)
		{
			temp = temp->next;
		}
	}
	return *temp;
}
//int hash_func(string entered_key)//õåø ôóíêö³ÿ
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
	int int_key=0;
	for(int i=0;i<search_key.length();i++)
	{
		int_key += search_key[i];
	}
	check *temp = slots;
	if ((slots != NULL) && (numb[int_key] <= n))
	{
		for (int i = 0;i <n - numb[int_key] - 1;i++)
		{
			temp = temp->next;
		}
	}
	return temp->number;
}
int main()
{
	int a = 4;
	table first(a);
	first.Show();
	cout << "Enter key" << endl;
	string key_;
	for(int i=0;i<4;i++)
	{
	cout << "Enter key" << endl;
	cin >> key_;
	cout << first[key_] << endl;
	}
	system("pause");

}