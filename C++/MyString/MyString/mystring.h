#pragma once
#include <iostream>
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
	mystring(char letter);
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