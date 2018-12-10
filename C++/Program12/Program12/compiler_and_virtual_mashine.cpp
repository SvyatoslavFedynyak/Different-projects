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
		tokens.pop_front();//видаляє if або ifnot
		tokens.pop_front();//видаляє [
						   //обробити умову
		handle_expression();
		string var_temp = operands.top().lexema;
		operands.pop();//очистити повністю стек операндів
		commands.emplace_back(name + ' ' + var_temp + ' ');
		//ітератор на елемент, який потрібно доповнити, коли потрібно вийти з умови
		auto iter_com_last = --commands.end();
		tokens.pop_front();//видаляє першу дужкку {
		while (tokens.front().lexema != "}")
		{
			handle_block();
		}
		//номер рядка, на який потрібно перейти, якщо умова не виконується
		int exit_line_number = commands.size();
		//доповнюю ітератор, коли потрібно вийти з умови
		*iter_com_last += to_string(exit_line_number);
		tokens.pop_front();//видаляє останню дужкку }
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
		tokens.pop_front();//видаляє while або whilenot
		tokens.pop_front();//видаляє [
						   //на який рядок потрібно повернутись в циклі
		int cycle_return_line = commands.size();
		//обробити умову
		handle_expression();
		string var_temp = operands.top().lexema;
		operands.pop();//очистити повністю стек операндів
		commands.emplace_back(name + ' ' + var_temp + ' ');
		//ітератор на останній елемент, який потрібно доповнити, коли потрібно вийти з умови
		auto iter_com_last = --commands.end();
		tokens.pop_front();//видаляє першу дужкку {
		while (tokens.front().lexema != "}")
		{
			handle_block();
		}
		//цикл
		name = "GOTO";
		commands.emplace_back(name + ' ' + to_string(cycle_return_line));

		//номер рядка, на який потрібно перейти, якщо умова не виконується
		int exit_line_number = commands.size();
		//доповнюю ітератор, коли потрібно вийти з умови
		*iter_com_last += to_string(exit_line_number);
		tokens.pop_front();//видаляє останню дужкку }
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
		tokens.pop_front();//видаляє read або write
		tokens.pop_front();//видаляє >
						   //перевірка чи змінна правильно записана
		if (is_good_variable(tokens.front().lexema))
		{
			commands.emplace_back(name + ' ' + tokens.front().lexema);
		}
		else
		{
			throw "The bad variable! Its name has not only letters a-z, A-Z or has key words.";
		}
		tokens.pop_front();//видаляє змінну
		tokens.pop_front();//видаляє ;
	}
	else
	{
		//обробка виразу
		string var_in = tokens.front().lexema;
		if (!is_good_variable(var_in))
		{
			throw "The bad variable! Its name has not only letters a-z, A-Z or has key words.";
		}
		tokens.pop_front();//видаляє змінну
		tokens.pop_front();//видаляє =
						   //обробити вираз
		handle_expression();
		name = "COPY";
		string var_temp = operands.top().lexema;
		operands.pop();//очистити повністю стек операндів
		commands.emplace_back(name + ' ' + var_temp + ' ' + var_in);
	}
}

void compiler::handle_expression()
{
	auto iter = tokens.begin();
	//ітератор кінця виразу
	auto iter_end_ex = iter;
	while (iter_end_ex->lexema != ";" && iter_end_ex->lexema != "]")
	{
		++iter_end_ex;
	}
	list<token> expression;
	//видаляємо поточний вираз з списку токенів tokens і вставляємо його у новий список токенів expression
	//(вираз із яким я далі буду працювати)
	expression.splice(expression.begin(), tokens, iter, iter_end_ex);
	tokens.pop_front();//видаляє ; або ]

					   //ВХІД: подання арифметичного виразу у вигляді списку токенів expression;
					   //ВИХІД: список команд для віртуальної машини – commands.
					   //Допоміжні структури :
					   //operands – стек операндів; - змінних або чисел
					   //operators – стек операторів;
					   //temp_count – лічильник тимчасових змінних.

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
	//порахувати кількість # у змінній, для подальшої перевірки чи це елемент масиву вигляду: а#index
	int count_of_sharp = count(st.begin(), st.end(), '#');
	if ((count_of_sharp == 1 || count_of_sharp == 0) && st[0] != '#' && st[st.size() - 1] != '#')
	{
		//перевірка чи стрічка не співпадає з ключовими словами
		if (st != "read" && st != "write" && st != "while" && st != "whilenot" && st != "if" && st != "ifnot")
		{
			for (size_t i = 0; i < st.length(); ++i)
			{
				//чи є у змінній один # - ознака елемента масиву
				if (st[i] == '#')
				{
					++i;
				}
				//перевірка чи st - змінна і містить тільки букви a-z, A-Z
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
	//Допоміжні структури:
	//operands – стек операндів; - змінних або чисел
	//operators – стек операторів;
	//temp_count – лічильник тимчасових змінних.
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
	//перетворюю поточний рядок у потік і зчитую перший елемент
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
	//перетворюю поточний рядок у потік і зчитую перший елемент
	stringstream line(lines[i]);
	string name;
	line >> name;//зчитую елемент GOTOIFNOT або GOTOIF, але він ніде не використовується,
				 //тому зчитую наступний елемент - змінну або число
	line >> name;
	if (is_number(name))
	{
		//якщо число, то переводжу з string у double value
		value = atof(name.c_str());
	}
	else
	{
		//змінна
		//змінюю цю змінну, якщо вона є елементом масиву,
		//тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
		name = change_if_elem_of_array(name);
		//якщо змінна, то присвоюю значення цієї змінної у value
		value = variables[name];
	}
	//зчитую число, яке вказує, на який рядок потрібно перейти, якщо умова не виконується 
	int exit_cycle_line;
	line >> exit_cycle_line;

	if (value > 0)
	{
		++i;//йду на новий рядок вектора рядків команд
			//перетворюю поточний рядок у потік і зчитую перший елемент
		stringstream line_in_if(lines[i]);
		line_in_if >> name;//зчитую першу команду наступного рядка
						   //обробляю блок умовного оператора(if або ifnot), поки він не стане циклом(while або whilenot)
						   //або поки цей блок не закінчиться
		while (i != exit_cycle_line && name != "GOTO")
		{
			handle_block(i);
			//перетворюю поточний рядок у потік і зчитую перший елемент
			stringstream line_in_while(lines[i]);
			line_in_while >> name;
		}
	}
	else
	{
		//присвоюю змінній "і" номер рядка, на який потрібно перейти, якщо умова не виконується
		i = exit_cycle_line;
	}
	if (i != exit_cycle_line && name == "GOTO")
	{
		//якщо попадаємо у цю перевірку, то виконується цикл while або whilenot

		//перетворюю поточний рядок у потік і зчитую перший елемент
		stringstream line_goto(lines[i]);
		line_goto >> name;//зчитую елемент GOTO, але він ніде не використовується,
						  //тому зчитую наступний елемент - 
						  //число, яке вказує, на який рядок потрібно повернутися, щоб відбувся цикл
		int goto_line;
		line_goto >> goto_line;

		//присвоюю змінній "і" номер рядка, на який потрібно повернутися, щоб відбувся цикл
		i = goto_line;
	}
}

void virtual_machine::handle_command(int& i)
{
	double value;
	//перетворюю поточний рядок у потік і зчитую перший елемент
	stringstream line(lines[i]);
	string name;
	line >> name;
	if (name == "READ" || name == "WRITE" || name == "COPY")
	{
		if (name == "READ")
		{
			line >> name;//зчитую змінну після READ
						 //змінюю цю змінну, якщо вона є елементом масиву,
						 //тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
			name = change_if_elem_of_array(name);
			cin >> value;
			//заношу за назвою змінної її значення
			variables[name] = value;
		}
		else
		{
			if (name == "WRITE")
			{
				line >> name;//зчитую змінну після WRITE
							 //змінюю цю змінну, якщо вона є елементом масиву,
							 //тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
				name = change_if_elem_of_array(name);
				cout << variables[name] << " ";
			}
			if (name == "COPY")
			{
				line >> name;//зчитую змінну після COPY
				if (is_number(name))
				{
					//якщо число, то переводжу з string у double value
					value = atof(name.c_str());
				}
				else
				{
					//якщо змінна
					//змінюю цю змінну, якщо вона є елементом масиву,
					//тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
					name = change_if_elem_of_array(name);
					//якщо змінна, то присвоюю значення цієї змінної у value
					value = variables[name];
				}
				line >> name;//зчитую змінну,у яку потрібно присвоїти число або змінну
							 //змінюю цю змінну, якщо вона є елементом масиву,
							 //тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
				name = change_if_elem_of_array(name);
				variables[name] = value;
			}
		}
		++i;//йду на новий рядок вектора рядків команд
	}
	else
	{
		handle_action(i);
	}
}

void virtual_machine::handle_action(int& i)
{
	double right, left;
	//перетворюю поточний рядок у потік і зчитую перший елемент
	stringstream line(lines[i]);
	string name;
	line >> name;
	//зчитую з потоку першу змінну або число після ADD(+) або SUB(-) або MUL(*) або DIV(/) - до left
	string var;
	line >> var;
	if (is_number(var))
	{
		//якщо число, то переводжу з string у double left
		left = atof(var.c_str());
	}
	else
	{
		//якщо змінна
		//змінюю цю змінну, якщо вона є елементом масиву,
		//тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
		var = change_if_elem_of_array(var);
		//якщо змінна, то присвоюю значення цієї змінної у left
		left = variables[var];
	}
	//зчитую з потоку другу змінну або число - right
	line >> var;
	if (is_number(var))
	{
		//якщо число, то переводжу з string у double right
		right = atof(var.c_str());
	}
	else
	{
		//якщо змінна
		//змінюю цю змінну, якщо вона є елементом масиву,
		//тобто a#index перетворюю на a#1(залежить скільки дорівнює index)
		var = change_if_elem_of_array(var);
		//якщо змінна, то присвоюю значення цієї змінної у right
		right = variables[var];
	}
	//зчитую з потоку третю змінну, яка зберігає значення порахованої дії
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
	++i;//йду на новий рядок вектора рядків команд
}

string virtual_machine::change_if_elem_of_array(string st)
{
	int pos = st.find('#');
	//перевірка виконається, якщо # є у змінній 
	if (pos != -1)
	{
		//перевірка, що йде після # число чи змінна
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
		//перевірка чи в st є крапка і st - дійсне число
		if (is_dot == false && st[i] == '.')
		{
			is_dot = true;
			continue;
		}
		//перевірка чи st - число і містить цифри 0-9
		if (st[i] < 48 || st[i] > 57)
		{
			return false;
		}
	}
	return true;
}
