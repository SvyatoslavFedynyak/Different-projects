// stdafx.h: включаемый файл для стандартных системных включаемых файлов,
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//
#pragma once
#include "iostream"
#include "time.h"
#include "targetver.h"
// Заголовки CppUnitTest
#include "CppUnitTest.h"

// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
#include "iostream"
#include "time.h"
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