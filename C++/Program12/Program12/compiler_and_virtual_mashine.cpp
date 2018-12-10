#include "compiler_and_virtual_mashine.h"
int compiler::temp_count = 0;

void compiler::string_to_tokens()
{
	text.reserve(text.size() * 2);
	for (auto iter = text.begin(); iter != text.end(); ++iter)
	{
		if (*iter == '>' || *iter == ';' || *iter == '=' || *iter == '*' || *iter == '/' || *iter == '+' || *iter == '-'
			|| *iter == '(' || *iter == ')' || *iter == '{' || *iter == '}' || *iter == '[' || *iter == ']')
		{
			text.insert(iter++, ' ');
			++iter;
			if (iter == text.end())
			{
				break;
			}
			text.insert(iter, ' ');
		}
	}
}

void compiler::handle_block()
{
	if (tokens.front().lexema == "while" || tokens.front().lexema == "whilenot" || tokens.front().lexema == "if"
		|| tokens.front().lexema == "ifnot")
	{
		handle_operator_block();
	}
	else
	{
		handle_command();
	}
}

void compiler::handle_operator_block()
{
	string name;
	if (tokens.front().lexema == "if" || tokens.front().lexema == "ifnot")
	{
		if (tokens.front().lexema == "if")
		{
			name = "GOTOIFNOT";
		}
		else
		{
			name = "GOTOIF";
		}
		tokens.pop_front();//������� if ��� ifnot
		tokens.pop_front();//������� [
						   //�������� �����
		handle_expression();
		string var_temp = operands.top().lexema;
		operands.pop();//�������� ������� ���� ��������
		commands.emplace_back(name + ' ' + var_temp + ' ');
		//�������� �� �������, ���� ������� ���������, ���� ������� ����� � �����
		auto iter_com_last = --commands.end();
		tokens.pop_front();//������� ����� ������ {
		while (tokens.front().lexema != "}")
		{
			handle_block();
		}
		//����� �����, �� ���� ������� �������, ���� ����� �� ����������
		int exit_line_number = commands.size();
		//�������� ��������, ���� ������� ����� � �����
		*iter_com_last += to_string(exit_line_number);
		tokens.pop_front();//������� ������� ������ }
	}
	else
	{
		if (tokens.front().lexema == "while")
		{
			name = "GOTOIFNOT";
		}
		else
		{
			//tokens.front().lexema == "whilenot"
			name = "GOTOIF";
		}
		tokens.pop_front();//������� while ��� whilenot
		tokens.pop_front();//������� [
						   //�� ���� ����� ������� ����������� � ����
		int cycle_return_line = commands.size();
		//�������� �����
		handle_expression();
		string var_temp = operands.top().lexema;
		operands.pop();//�������� ������� ���� ��������
		commands.emplace_back(name + ' ' + var_temp + ' ');
		//�������� �� ������� �������, ���� ������� ���������, ���� ������� ����� � �����
		auto iter_com_last = --commands.end();
		tokens.pop_front();//������� ����� ������ {
		while (tokens.front().lexema != "}")
		{
			handle_block();
		}
		//����
		name = "GOTO";
		commands.emplace_back(name + ' ' + to_string(cycle_return_line));

		//����� �����, �� ���� ������� �������, ���� ����� �� ����������
		int exit_line_number = commands.size();
		//�������� ��������, ���� ������� ����� � �����
		*iter_com_last += to_string(exit_line_number);
		tokens.pop_front();//������� ������� ������ }
	}
}

void compiler::handle_command()
{
	string name;
	if (tokens.front().lexema == "read" || tokens.front().lexema == "write")
	{
		if (tokens.front().lexema == "read")
		{
			name = "READ";
		}
		else
		{
			name = "WRITE";
		}
		tokens.pop_front();//������� read ��� write
		tokens.pop_front();//������� >
						   //�������� �� ����� ��������� ��������
		if (is_good_variable(tokens.front().lexema))
		{
			commands.emplace_back(name + ' ' + tokens.front().lexema);
		}
		else
		{
			throw "The bad variable! Its name has not only letters a-z, A-Z or has key words.";
		}
		tokens.pop_front();//������� �����
		tokens.pop_front();//������� ;
	}
	else
	{
		//������� ������
		string var_in = tokens.front().lexema;
		if (!is_good_variable(var_in))
		{
			throw "The bad variable! Its name has not only letters a-z, A-Z or has key words.";
		}
		tokens.pop_front();//������� �����
		tokens.pop_front();//������� =
						   //�������� �����
		handle_expression();
		name = "COPY";
		string var_temp = operands.top().lexema;
		operands.pop();//�������� ������� ���� ��������
		commands.emplace_back(name + ' ' + var_temp + ' ' + var_in);
	}
}

void compiler::handle_expression()
{
	auto iter = tokens.begin();
	//�������� ���� ������
	auto iter_end_ex = iter;
	while (iter_end_ex->lexema != ";" && iter_end_ex->lexema != "]")
	{
		++iter_end_ex;
	}
	list<token> expression;
	//��������� �������� ����� � ������ ������ tokens � ���������� ���� � ����� ������ ������ expression
	//(����� �� ���� � ��� ���� ���������)
	expression.splice(expression.begin(), tokens, iter, iter_end_ex);
	tokens.pop_front();//������� ; ��� ]

					   //�ղ�: ������� ������������� ������ � ������ ������ ������ expression;
					   //��ղ�: ������ ������ ��� ��������� ������ � commands.
					   //������� ��������� :
					   //operands � ���� ��������; - ������ ��� �����
					   //operators � ���� ���������;
					   //temp_count � �������� ���������� ������.

	while (!expression.empty())
	{
		token tok = expression.front();
		expression.pop_front();
		if (is_number(tok.lexema) || is_good_variable(tok.lexema))
		{
			operands.emplace(tok);
		}
		else
		{
			if (is_operator(tok.lexema))
			{
				while (!operators.empty() && priority(operators.top()) >= priority(tok))
				{
					generate_command();
				}
				operators.emplace(tok);
			}
			else
			{
				if (tok.lexema == "(")
				{
					operators.emplace(tok);
				}
				if (tok.lexema == ")")
				{
					while (operators.top().lexema != "(")
					{
						generate_command();
					}
					operators.pop();
				}
			}
		}
	}
	while (!operators.empty())
	{
		if (operators.top().lexema == "(")
		{
			throw "Bad expression!";
		}
		generate_command();
	}
}

bool compiler::is_good_variable(string st)
{
	//���������� ������� # � �����, ��� �������� �������� �� �� ������� ������ �������: �#index
	int count_of_sharp = count(st.begin(), st.end(), '#');
	if ((count_of_sharp == 1 || count_of_sharp == 0) && st[0] != '#' && st[st.size() - 1] != '#')
	{
		//�������� �� ������ �� ������� � ��������� �������
		if (st != "read" && st != "write" && st != "while" && st != "whilenot" && st != "if" && st != "ifnot")
		{
			for (size_t i = 0; i < st.length(); ++i)
			{
				//�� � � ����� ���� # - ������ �������� ������
				if (st[i] == '#')
				{
					++i;
				}
				//�������� �� st - ����� � ������ ����� ����� a-z, A-Z
				if (st[i] < 65 || (st[i] > 90 && st[i] < 97) || st[i] > 122)
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool compiler::is_operator(string st)
{
	return st == "+" || st == "-" || st == "*" || st == "/" ? true : false;
}

int compiler::priority(token t)
{
	if (t.lexema == "*" || t.lexema == "/")
	{
		return 2;
	}
	if (t.lexema == "+" || t.lexema == "-")
	{
		return 1;
	}
	if (t.lexema == "(")
	{
		return 0;
	}
}

void compiler::generate_command()
{
	//������� ���������:
	//operands � ���� ��������; - ������ ��� �����
	//operators � ���� ���������;
	//temp_count � �������� ���������� ������.
	string name;
	string op = operators.top().lexema;
	operators.pop();
	string right = operands.top().lexema;
	operands.pop();
	string left = operands.top().lexema;
	operands.pop();
	if (op == "+")
	{
		name = "ADD";
	}
	if (op == "-")
	{
		name = "SUB";
	}
	if (op == "*")
	{
		name = "MUL";
	}
	if (op == "/")
	{
		name = "DIV";
	}
	string res = "t" + to_string(temp_count);
	commands.emplace_back(name + ' ' + left + ' ' + right + ' ' + res);
	operands.emplace(token(res));
	++temp_count;
}

void compiler::read_from_file(istream & is)
{
	string string_ = "";
	while (!is.eof())
	{
		is >> string_;
		text += string_;
	}
	string_to_tokens();
	stringstream stream(text);
	token var_read;
	while (!stream.eof())
	{
		stream >> var_read.lexema;
		tokens.emplace_back(var_read);
	}
}

void compiler::execute()
{
	while (!tokens.empty())
	{
		handle_block();
	}
}

void compiler::write(ostream & os)
{
	for (auto iter_com = commands.begin(); iter_com != commands.end(); ++iter_com)
	{
		os << *iter_com;
		if (++iter_com != commands.end())
		{
			os << endl;
		}
		--iter_com;
	}
}

void virtual_machine::handle_block(int& i)
{
	//���������� �������� ����� � ���� � ������ ������ �������
	stringstream line(lines[i]);
	string name;
	line >> name;
	if (name == "GOTOIFNOT" || name == "GOTOIF")
	{
		handle_operator_block(i);
	}
	else
	{
		handle_command(i);
	}
}

void virtual_machine::handle_operator_block(int& i)
{
	double value;
	//���������� �������� ����� � ���� � ������ ������ �������
	stringstream line(lines[i]);
	string name;
	line >> name;//������ ������� GOTOIFNOT ��� GOTOIF, ��� �� ��� �� ���������������,
				 //���� ������ ��������� ������� - ����� ��� �����
	line >> name;
	if (is_number(name))
	{
		//���� �����, �� ��������� � string � double value
		value = atof(name.c_str());
	}
	else
	{
		//�����
		//����� �� �����, ���� ���� � ��������� ������,
		//����� a#index ���������� �� a#1(�������� ������ ������� index)
		name = change_if_elem_of_array(name);
		//���� �����, �� �������� �������� ���� ����� � value
		value = variables[name];
	}
	//������ �����, ��� �����, �� ���� ����� ������� �������, ���� ����� �� ���������� 
	int exit_cycle_line;
	line >> exit_cycle_line;

	if (value > 0)
	{
		++i;//��� �� ����� ����� ������� ����� ������
			//���������� �������� ����� � ���� � ������ ������ �������
		stringstream line_in_if(lines[i]);
		line_in_if >> name;//������ ����� ������� ���������� �����
						   //�������� ���� �������� ���������(if ��� ifnot), ���� �� �� ����� ������(while ��� whilenot)
						   //��� ���� ��� ���� �� ����������
		while (i != exit_cycle_line && name != "GOTO")
		{
			handle_block(i);
			//���������� �������� ����� � ���� � ������ ������ �������
			stringstream line_in_while(lines[i]);
			line_in_while >> name;
		}
	}
	else
	{
		//�������� ����� "�" ����� �����, �� ���� ������� �������, ���� ����� �� ����������
		i = exit_cycle_line;
	}
	if (i != exit_cycle_line && name == "GOTO")
	{
		//���� �������� � �� ��������, �� ���������� ���� while ��� whilenot

		//���������� �������� ����� � ���� � ������ ������ �������
		stringstream line_goto(lines[i]);
		line_goto >> name;//������ ������� GOTO, ��� �� ��� �� ���������������,
						  //���� ������ ��������� ������� - 
						  //�����, ��� �����, �� ���� ����� ������� �����������, ��� ������� ����
		int goto_line;
		line_goto >> goto_line;

		//�������� ����� "�" ����� �����, �� ���� ������� �����������, ��� ������� ����
		i = goto_line;
	}
}

void virtual_machine::handle_command(int& i)
{
	double value;
	//���������� �������� ����� � ���� � ������ ������ �������
	stringstream line(lines[i]);
	string name;
	line >> name;
	if (name == "READ" || name == "WRITE" || name == "COPY")
	{
		if (name == "READ")
		{
			line >> name;//������ ����� ���� READ
						 //����� �� �����, ���� ���� � ��������� ������,
						 //����� a#index ���������� �� a#1(�������� ������ ������� index)
			name = change_if_elem_of_array(name);
			cin >> value;
			//������ �� ������ ����� �� ��������
			variables[name] = value;
		}
		else
		{
			if (name == "WRITE")
			{
				line >> name;//������ ����� ���� WRITE
							 //����� �� �����, ���� ���� � ��������� ������,
							 //����� a#index ���������� �� a#1(�������� ������ ������� index)
				name = change_if_elem_of_array(name);
				cout << variables[name] << " ";
			}
			if (name == "COPY")
			{
				line >> name;//������ ����� ���� COPY
				if (is_number(name))
				{
					//���� �����, �� ��������� � string � double value
					value = atof(name.c_str());
				}
				else
				{
					//���� �����
					//����� �� �����, ���� ���� � ��������� ������,
					//����� a#index ���������� �� a#1(�������� ������ ������� index)
					name = change_if_elem_of_array(name);
					//���� �����, �� �������� �������� ���� ����� � value
					value = variables[name];
				}
				line >> name;//������ �����,� ��� ������� �������� ����� ��� �����
							 //����� �� �����, ���� ���� � ��������� ������,
							 //����� a#index ���������� �� a#1(�������� ������ ������� index)
				name = change_if_elem_of_array(name);
				variables[name] = value;
			}
		}
		++i;//��� �� ����� ����� ������� ����� ������
	}
	else
	{
		handle_action(i);
	}
}

void virtual_machine::handle_action(int& i)
{
	double right, left;
	//���������� �������� ����� � ���� � ������ ������ �������
	stringstream line(lines[i]);
	string name;
	line >> name;
	//������ � ������ ����� ����� ��� ����� ���� ADD(+) ��� SUB(-) ��� MUL(*) ��� DIV(/) - �� left
	string var;
	line >> var;
	if (is_number(var))
	{
		//���� �����, �� ��������� � string � double left
		left = atof(var.c_str());
	}
	else
	{
		//���� �����
		//����� �� �����, ���� ���� � ��������� ������,
		//����� a#index ���������� �� a#1(�������� ������ ������� index)
		var = change_if_elem_of_array(var);
		//���� �����, �� �������� �������� ���� ����� � left
		left = variables[var];
	}
	//������ � ������ ����� ����� ��� ����� - right
	line >> var;
	if (is_number(var))
	{
		//���� �����, �� ��������� � string � double right
		right = atof(var.c_str());
	}
	else
	{
		//���� �����
		//����� �� �����, ���� ���� � ��������� ������,
		//����� a#index ���������� �� a#1(�������� ������ ������� index)
		var = change_if_elem_of_array(var);
		//���� �����, �� �������� �������� ���� ����� � right
		right = variables[var];
	}
	//������ � ������ ����� �����, ��� ������ �������� ���������� 䳿
	line >> var;

	if (name == "ADD")
	{
		variables[var] = left + right;
	}
	if (name == "SUB")
	{
		variables[var] = left - right;
	}
	if (name == "MUL")
	{
		variables[var] = left * right;
	}
	if (name == "DIV")
	{
		variables[var] = left / right;
	}
	++i;//��� �� ����� ����� ������� ����� ������
}

string virtual_machine::change_if_elem_of_array(string st)
{
	int pos = st.find('#');
	//�������� ����������, ���� # � � ����� 
	if (pos != -1)
	{
		//��������, �� ��� ���� # ����� �� �����
		string index = (variables.find(st.substr(pos + 1)) != variables.end()) ?
			to_string(int(variables[st.substr(pos + 1)])) : st.substr(pos + 1);
		st = st.substr(0, pos) + index;
	}
	return st;
}

void virtual_machine::read_from_file(istream & is)
{
	string string_ = "";
	while (!is.eof())
	{
		getline(is, string_);
		lines.emplace_back(string_);
	}
}

void virtual_machine::execute()
{
	int i = 0;
	while (i != lines.size())
	{
		handle_block(i);
	}
}

bool is_number(string st)
{
	bool is_dot = false;
	for (size_t i = 0; i < st.length(); ++i)
	{
		//�������� �� � st � ������ � st - ����� �����
		if (is_dot == false && st[i] == '.')
		{
			is_dot = true;
			continue;
		}
		//�������� �� st - ����� � ������ ����� 0-9
		if (st[i] < 48 || st[i] > 57)
		{
			return false;
		}
	}
	return true;
}
