#include "Header.h"
using namespace std;

int prioritet(const char a, const char b)
{
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))
		return 0;
	else
		if (a == '*' || a == '/')
			return 1;
		else
			if (b == '*' || b == '/')
				return -1;
			else
				if ((a == '-' || a == '+') && (b == '-' || b == '+'))
					return 0;
				else
					if (a == '-' || a == '+')
						return 1;
					else
						if (b == '-' || b == '+')
							return -1;
						else
							return 0;
}

string read(const string s)
{
	Stack1<char> st;
	string rezult;
	int i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] > '0' && s[i] <= '9') || s[i] == '.')
		{
			rezult.insert(rezult.end(), s[i]);
		}
		else
			if (s[i] == '(')
			{
				st.push(s[i]);
			}
			else
				if (s[i] == ')')
				{
					while (st.Peek() != '(')
					{
						rezult.insert(rezult.end(), st.Peek());
						st.pop();
					}
					st.pop();
				}
				else
					if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
					{
						rezult.push_back('&');
						while (st.isEmpty() && (prioritet(s[i], st.Peek()) == 0 || prioritet(s[i], st.Peek()) == -1))
						{
							rezult.insert(rezult.end(), st.Peek());
							st.pop();
						}
						st.push(s[i]);
					}

		i++;

	}
	rezult.push_back('&');
	while (st.isEmpty())
	{
		rezult.insert(rezult.end(), st.Peek());
		st.pop();
	}
	return rezult;
}

double func(const string row, int pos)
{
	Stack1 <double> st;
	int i;
	string s;
	for (i = pos; row[i] != '\0'; i++)
	{
		if (row[i] == '&')
		{
			st.push(atof(s.c_str()));
			s.clear();
		}
		else
			if ((row[i] >= '0' && row[i] < '9') || row[i] == '.')
			{
				s.push_back(row[i]);
			}
		if (row[i] == '/' || row[i] == '*' || row[i] == '+' || row[i] == '-')
		{
			double right = st.Peek();
			st.pop();
			double left = st.Peek();

			st.pop();
			switch (row[i])
			{
			case '/':st.push(left / right); break;
			case '*':st.push(left * right); break;
			case '-':st.push(left - right); break;
			case '+':st.push(left + right); break;
			}

		}


	}
	double rezult = st.Peek();
	return rezult;
}


void main()
{
	string c;
	cin >> c;
	string b = read(c);
	cout << endl;
	cout << b;
	cout << endl;
	cout << func(b, 0);
	_getch();
}