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
//#include<cstdlib> - ���� �� ���� ��������� ��������, �� ��������� �� �������� ��� ������� atof
using namespace std;
//�������� �� ������ � ������
bool is_number(string st);

class compiler
{
private:
	//����� � �����
	string text;

	struct token
	{
		string lexema;
		token() :lexema("") {}
		token(string lex) :lexema(lex) {}
	};
	//������ �����
	list<token> tokens;
	//������ ������
	list<string> commands;
	//operators � ���� ���������;
	stack<token> operators;
	//	operands � ���� ��������; - ������ ��� �����
	stack<token> operands;
	//temp_count � �������� ���������� ������.
	static int temp_count;
	//�������� ����� �� �����
	void string_to_tokens();
	//�������� ����
	void handle_block();
	//�������� while, whilenot, if, ifnot
	void handle_operator_block();
	//�������� read, write ��� ��������� ���������� ������ handle_expression()
	void handle_command();
	//�������� �����
	void handle_expression();
	//�������� �� ����� �� ��������� �����
	bool is_good_variable(string st);
	//�������� �� � ������ ����������
	bool is_operator(string st);
	//�������� ���������
	int priority(token t);
	//����������� ������ ADD, SUB, MUL, DIV
	void generate_command();
public:
	compiler() {}
	//������� ��� � �����
	void read_from_file(istream& is);
	//����������� ���
	void execute();
	//�������� ������������� ��� � ����� ����
	void write(ostream& os);
};

class virtual_machine
{
private:
	//��� ����������� �� ����, ������� � �����������
	map<string, double> variables;

	//������ ����� ������
	vector<string> lines;
	//�������� ����
	void handle_block(int& i);
	//�������� GOTOIFNOT, GOTOIF � GOTO
	void handle_operator_block(int& i);
	//�������� READ, WRITE, COPY ��� ��������� ���������� �� handle_action()
	void handle_command(int& i);
	//�������� �� ADD, SUB, MUL, DIV
	void handle_action(int& i);
	//���� st ������� ������, ��������� �#index, �� ������� index �� �������� �����
	string change_if_elem_of_array(string st);
public:
	//������� ������������� ��� � �����
	void read_from_file(istream& is);
	//��������� ��� ���
	void execute();
};
