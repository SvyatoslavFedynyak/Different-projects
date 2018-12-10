#include <iostream>
#include <string>
using namespace std;
const int table_size = 4;
struct slot
{
	string key;
	int value;
	slot* same;
	slot() { key = "", value = 0; same = nullptr; }
	slot(string ent_key, int ent_value)
	{
		key = ent_key;
		value = ent_value;
		same = nullptr;
	}
};
class HeshAppl
{
private:
	slot* table[table_size];
	int transkey(string ent_key)
	{
		int hash = 0, p_pow = 2;
		int quantity = 'z' - 'a' + 1;
		hash += (ent_key[0] - 'a' + 1)*quantity;
		for (int i = 1; i < ent_key.length(); ++i)
		{
			hash += (ent_key[i] - 'a' + 1) * p_pow;
			p_pow *= 2;
		}
		hash = hash % table_size;
		return hash;
	}
public:
	HeshAppl();
	void Show();
	void Add(int entered_value, string entered_key);
	slot* Pop(int, int);
	int operator[](string entered_key);
	//~HeshAppl();
};
void HeshAppl::Show()
{
	//static int slot_place = 1;
	for (int i = 0; i < table_size; i++)
	{
		if (table[i] == nullptr)
		{
			cout << endl << "|[" << i << "] value=" << 0 << ", key=" << 0 << "|";
		}
		else
		{
			if (table[i]->same == nullptr)
			{
				cout << endl << "|[" << i << "] value=" << table[i]->value << ", key=" << table[i]->key << "|";
			}
			else
			{
				cout << endl << "|[" << i << "] value=" << table[i]->value << ", key=" << table[i]->key << "|";
				slot* temp = table[i];
				temp = temp->same;
				while (temp->same != nullptr)
				{
					cout << "->|value=" << temp->value << ", key=" << temp->key << "|";
					temp = temp->same;
				}
				cout << endl;
				/*slot* temp = table[i];
					for (int i = 0; i < slot_place; i++)
					{
						if (temp->same == nullptr)
						{
							break;
							slot_place = 0;
						}
						else
						{
							temp = temp->same;
						}
					}
					cout << "Slots value is: " << temp->value << endl;
					cout << "Slots key is: " << temp->key << endl;
					slot_place++;*/
			}
		}
	}
}
slot* HeshAppl::Pop(int open_number, int slot_num)
{
	slot* start_slot = this->table[slot_num];
	slot *temp = start_slot;
	if ((start_slot != nullptr) && (open_number <= table_size))
	{
		while (temp != nullptr)
		{
			temp = temp->same;
		}
	}
	return temp;
}
void HeshAppl::Add(int entered_value, string entered_key)
{

	int transfered_key = transkey(entered_key);
	slot* start_slot = table[transfered_key];
	if (start_slot == nullptr)
	{
		start_slot = new slot(entered_key, entered_value);
		table[transfered_key] = start_slot;
	}
	else
	{
		if (start_slot->key == entered_key)
		{

		}
		else
		{
			slot* temp;
			temp = start_slot;
			while (temp != nullptr)
			{
				temp = temp->same;
				if (temp->key == entered_key)
				{
					break;
				}
			}
			if (temp->key == entered_key)
			{

			}
			else
			{
				temp = new slot(entered_key, entered_value);
				temp->same = start_slot;
				start_slot = temp;
				table[transfered_key] = start_slot;
			}
		}
	}
}
HeshAppl::HeshAppl()
{
	for (int i = 0; i < table_size; i++)
	{
		table[i] = nullptr;
	}
}
int HeshAppl::operator[](string entered_key)
{
	slot *temp = table[transkey(entered_key)];
	if (temp->key == entered_key)
	{
		return temp->value;
	}
	else
	{
		bool present = false;
		while (temp->same != nullptr)
		{
			temp = temp->same;
			if (temp->key == entered_key)
			{
				present = true;
				break;
			}

		}
		if (present = true)
		{
			return temp->value;
		}
		else
		{
			cout << "There is no slot with that key" << endl;
			return 0;
		}
	}

}
int main()
{
	HeshAppl first;
	string command;
	string key_;
	do
	{
		cout << endl;
		cout << "To add element print: add " << endl;
		cout << "To show print :show" << endl;
		cout << "To exit print: exit " << endl;
		cout << "To open slot print: open" << endl;
		cin >> command;
		if (command == "add")
		{
			first.Add();
		}
		else if (command == "show")
		{
			first.Show();
		}
		else if (command == "exit")
		{
			break;
		}
		else if (command == "open")
		{
			cout << "Enter key" << endl;

			cin >> key_;
			cout << first[key_] << endl;
		}
		else
		{
			cout << "Wrong command" << endl;
		}
	} while (true);
}