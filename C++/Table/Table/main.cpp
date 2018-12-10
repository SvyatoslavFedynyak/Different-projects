#include <iostream>
#include <string>
using namespace std;
struct check
{
	int number;
	string key;
	check() { number = 0; key = " "; };
	check(int num, string k) { number = num; key = k; };
};
class table
{
private:
	check* slots;
	int n;
public:
	table() :n(0), slots() {};
	table(int);
	void EnterInfo();
	void ShowSlotsNum();
	int	OpenNum(string);
	int operator[](string);
	//~table(void);
};

table::table(int mum)
{
	n = mum;
	slots = new check[n];
}
void table::EnterInfo()
{
	for (int i = 0;i < n;i++)
	{
		cout << "Enter [" << i + 1 << "] slot number:" << endl;
		cin >> slots[i].number;
		cout << "Enter [" << i + 1 << "] slot key:" << endl;
		cin >> slots[i].key;
	}
}
int table::OpenNum(string key_)
{
	bool present = false;
	int slot_num;
	for (int i = 0;i < n;i++)
	{
		if (slots[i].key == key_)
		{
			slot_num = slots[i].number;
			present = true;
			break;
		}
	}
	if (present == true)
	{
		return slot_num;
	}
	else
	{
		cout << "No slot with this key";
	}
}
int table::operator[](string key_)
{
	bool present = false;
	int slot_num;
	for (int i = 0;i < n;i++)
	{
		if (slots[i].key == key_)
		{
			slot_num = slots[i].number;
			present = true;
			break;
		}
	}
	if (present == true)
	{
		return slot_num;
	}
	else
	{
		cout << "No slot with this key";
	}
}

void table::ShowSlotsNum()
{
	bool present = false;
	string entered_key;
	int slot_num;
	cout << "Enter key to see slot number:" << endl;
	cin >> entered_key;
	for (int i = 0;i < n;i++)
	{
		if (slots[i].key == entered_key)
		{
			slot_num = slots[i].number;
			present = true;
			break;
		}
	}
	if (present == true)
	{
		cout << "Number of this slot is: " << slot_num << endl;
	}
	else
	{
		cout << "Sorry, but there are no slots with this key" << endl;
	}
}

int main()
{
	int a = 3;
	check* arr = new check[a];
	table first(a);
	cout << "Ok" << endl;
	first.EnterInfo();
	first.ShowSlotsNum();
	system("pause");

}