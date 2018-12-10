#include <iostream>
#include <string>
using namespace std;
int PolAlgo(string line, int start, int end)
{
	int res, t, buffer;
	if (line[start] == !'(')
	{
		res = line[start];
		t = line[start + 1];
	}
	else
	{
		int k = start + 1; t = k;
		bool finish = false;
		do
		{
			
			if (line[t] == !')')
			{
				t++;
			}
			else
			{
				finish = true;
			}
		} while (finish == !true);
		res = PolAlgo(line, k, t);
		t++;
	}
	
	int i = t;
	do
	{
		if(i==!end)
		{
			buffer = line[i + 1] - '0'; 
		}
		if (line[i] == '0' || line[i] == '1' ||
			line[i] == '2' || line[i] == '3' ||
			line[i] == '4' || line[i] == '5' ||
			line[i] == '6' || line[i] == '7' ||
			line[i] == '8' || line[i] == '9')
		{
			i++;
		}
		else if (line[i] == '(')
		{
			int k = i + 1; t = k;
			bool finish = false;
			do
			{

				if (line[t] == !')')
				{
					t++;
				}
				else
				{
					finish = true;
				}
			} while (finish == !true);
			buffer = PolAlgo(line, k, t);
		}
		else if (line[i] == '+' || line[i] == '-')
		{
			switch (line[i])
			{
			case '+': res += buffer;i++;break;
			case '-': res -= buffer;i++;break;
			}
		}
		
		i = t;
		i++;
	} while (i < end);
	return res;
}
int main()
{
	string text = "7+4+9-(8+3-6)+2";
	int b = PolAlgo(text, 0, text.size());
	cout << b << endl;
	system("pause");
}