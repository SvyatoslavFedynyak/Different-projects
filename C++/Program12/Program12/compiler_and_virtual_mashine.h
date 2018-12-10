#pragma once
#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stack>
#include<list>
#include<map>
#include<vector>
#include<algorithm>
//#include<cstdlib> - якщо не буде працювати програма, то підключити цю бібліотеку для функції atof
using namespace std;
//перевірка чи стрічка є числом
bool is_number(string st);

class compiler
{
private:
	//текст з файла
	string text;

	struct token
	{
		string lexema;
		token() :lexema("") {}
		token(string lex) :lexema(lex) {}
	};
	//список знаків
	list<token> tokens;
	//список команд
	list<string> commands;
	//operators – стек операторів;
	stack<token> operators;
	//	operands – стек операндів; - змінних або чисел
	stack<token> operands;
	//temp_count – лічильник тимчасових змінних.
	static int temp_count;
	//розділити текст на знаки
	void string_to_tokens();
	//обробити блок
	void handle_block();
	//обробити while, whilenot, if, ifnot
	void handle_operator_block();
	//обробити read, write або викликати оброблення виразу handle_expression()
	void handle_command();
	//обробити вираз
	void handle_expression();
	//перевірка чи змінна має дозволену назву
	bool is_good_variable(string st);
	//перевірка чи є стрічка оператором
	bool is_operator(string st);
	//пріоритет оператора
	int priority(token t);
	//генерування команд ADD, SUB, MUL, DIV
	void generate_command();
public:
	compiler() {}
	//зчитати код з файлу
	void read_from_file(istream& is);
	//скомпілювати код
	void execute();
	//записати скомпільований код у новий файл
	void write(ostream& os);
};

class virtual_machine
{
private:
	//тут зберігаються всі змінні, включно з тимчасовими
	map<string, double> variables;

	//вектор рядків команд
	vector<string> lines;
	//обробити блок
	void handle_block(int& i);
	//обробити GOTOIFNOT, GOTOIF і GOTO
	void handle_operator_block(int& i);
	//обробити READ, WRITE, COPY або викликати оброблення дій handle_action()
	void handle_command(int& i);
	//обробити дію ADD, SUB, MUL, DIV
	void handle_action(int& i);
	//якщо st елемент масиву, наприклад а#index, то замінить index на відповідне число
	string change_if_elem_of_array(string st);
public:
	//зчитати скомпільований код з файлу
	void read_from_file(istream& is);
	//запустити цей код
	void execute();
};
