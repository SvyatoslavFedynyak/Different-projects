#pragma once
#include "forEach.h"
using namespace std;
template <typename T>
class list
{
private:
	struct list_slot
	{
		T value;
		list_slot* next;
		list_slot() { value = NULL; next = nullptr; }
		list_slot(T val) { value = val; next = nullptr; }
		list_slot(T val, list_slot* nxt) { value = val; next = nxt; }
	};
	list_slot* first;
	int num;
public:
	list() { first = new list_slot; num = 0; }
	void Add(T);
	void Show();
	friend void forEachList(list<T> entered_struct, pfunct func)
	{
		list_slot* temp = entered_struct.first;
				for (int i = 0;i < entered_struct.num;i++)
				{
					temp->value=func(temp->value);
					temp = temp->next;
				}
	}
	void Remove(int);
	void AddInto(int, T);
	int Find(T);
};
//template <typename T>
//void forEachList(list<T> entered_struct, pfunct func)
//{
//	list_slot temp = slotentered_struct.first;
//for (int i = 0;i < entered_struct.num;i++)
//{
//	temp->value = func(temp->value);
//	temp = temp->next;
//}
//}
template <typename T>
void list<T>::Add(T val)
{
	if (num == 0)
	{
		first->value = val;
		first->next = new list_slot;
	}
	else
	{
		list_slot* temp = first;
		for (int i = 0; i < num; i++)
		{
			temp = temp->next;
		}
		temp->value = val;
		temp->next = new list_slot;
	}
	num++;
}
template <typename T>
void list<T>::AddInto(int number, T val)
{
	list_slot* temp = first;
	list_slot* tail;
	for (int i = 0; i < number-1; i++)
	{
		temp = temp->next;
	}
	tail = temp->next;
	temp->next = new list_slot(val, tail);
}
template <typename T>
void list<T>::Show()
{
	list_slot* temp = first;
	for (int i = 0; i < num; i++)
	{
		cout << temp->value;
		if (i < num - 1) { cout << " -> "; }
		if (temp->next == nullptr)
		{
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	cout << endl;
}
template <typename T>
void list<T>::Remove(int number)
{
	list_slot* temp = first;
	for (int i = 0;i < number-1;i++)
	{
		temp = temp->next;
	}
	temp->next = temp->next->next;
}
template <typename T>
int list<T>::Find(T value_)
{
	int res=0;
	bool res_pres=false;
	list_slot* temp = first;
	for (int i = 0;i < num;i++)
	{
		if (temp->value == value_)
		{
			res=i;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	return res;
}