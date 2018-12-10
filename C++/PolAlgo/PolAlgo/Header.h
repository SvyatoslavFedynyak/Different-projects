#pragma once
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

template <typename T>
class Stack1
{
private:
	T *arr;
	int n;
	int pos;
public:
	Stack1<T>()
	{
		n = 20;
		arr = new T[n];
		pos = 0;
	}
	void pop()
	{
		pos--;
	}
	void push(const T a)
	{
		arr[pos++] = a;
	}
	T Peek()
	{
		return arr[pos - 1];
	}
	bool isEmpty()
	{
		if (pos != 0)
			return true;
		else
			return false;
	}


	~Stack1()
	{
		delete[] arr;
	}
};
