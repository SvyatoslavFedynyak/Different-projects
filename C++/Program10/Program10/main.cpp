#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <utility>
using namespace std;
class Colont
{
protected:
	string colont_body;
public:
	Colont() {};
	Colont(string col) { colont_body = col; }
	virtual void SetBody(string col) { colont_body = col; }
};
class HighColont :public Colont
{
protected:
	string additional_word;
public:
	HighColont() {};
	HighColont(string _body, string add) { colont_body = _body; additional_word = add; };
	void Print() { cout << colont_body << " " << additional_word; }
	void SaveToFile(ofstream& file)
	{
		file << colont_body << " " << additional_word;
	}
	void AddAdditionalWord(string w) { additional_word = w; }
};
class LowColont :public Colont
{
protected:
	int num_of_rep;
public:
	LowColont() {};
	LowColont(string _body, int num) { colont_body = _body; num_of_rep = num; };
	void SaveToFile(ofstream& file)
	{
		file << colont_body << " " << num_of_rep;
	}
	void Print() { cout << colont_body << " " << num_of_rep; }
};
class HighColontWithNumber :public HighColont
{
private:
	int number;
public:
	HighColontWithNumber(string _body, string add, int num) { colont_body = _body; additional_word = add; number = num; };
	void Print() { cout << colont_body << " " << additional_word << " " << number; }
	void SaveToFile(ofstream& file)
	{
		file << colont_body << " " << additional_word << " " << number;
	}
	void SetNumber(int num) { number = num; }
};
class LowColontWithAddWord :public LowColont
{
private:
	string add_word;
public:
	LowColontWithAddWord(string _body, int num, string add) { colont_body = _body; num_of_rep = num; add_word = add; };
	void Print() { cout << colont_body << " " << num_of_rep << " " << add_word; }
	void SaveToFile(ofstream& file)
	{
		file << colont_body << " " << num_of_rep << " " << add_word;
	}
	void SetAddWord(string word) { add_word = word; }
};
class Report
{
public:
	string body;
	pair<HighColont, LowColont> colonts;
public:
	Report() {};
	void ShowInConsole()
	{
		colonts.first.Print();
		cout << endl;
		for (int i = 0;i < 50;i++)cout << "_";
		cout << endl;
		cout << body << endl;
		for (int i = 0;i < 50;i++)cout << "_";
		cout << endl;
		colonts.second.Print();
		cout << endl;
	}
	void SaveToFile(ofstream& file)
	{
		colonts.first.SaveToFile(file);
		file << endl;
		for (int i = 0;i < 25;i++)file << "-";
		file << endl;
		for (int i = 0;i < body.size();i++)
		{
			file << body[i];
			if (((i % 25) == 0) && (i > 0))
			{
				file << endl;
			}
		}
		file << endl;
		for (int i = 0;i < 25;i++)file << "-";
		file << endl;
		colonts.second.SaveToFile(file);
		for (int i = 0;i < 4;i++)file << endl;
	}
};
class VirtualReportBuilder
{
protected:
	Report curr_rep;
public:
	VirtualReportBuilder() {};
	void SetBody(string input_body) { curr_rep.body = input_body; };
	void SetHighColont(HighColont hc) { curr_rep.colonts.first = hc; };
	void SetLowColont(LowColont lc) { curr_rep.colonts.second = lc; };
	Report getReport() { return curr_rep; }
};
int main()
{
	list<Report> report_list;
	VirtualReportBuilder builder;
	do
	{
		cout << "Enter command:" << endl;
		string command;
		cin >> command;
		if (command == "exit")break;
		else if (command == "create")
		{
			cout << "Enter text";
			cout << endl;
			string text;
			cin.ignore(1, '/n');
			getline(cin, text);
			builder.SetBody(text);
			report_list.push_back(builder.getReport());
		}
		//SetHighColont
		else if (command == "shc")
		{
			cout << "Enter body:" << endl;
			string body, add;
			cin >> body;
			cout << "Enter add word:" << endl;
			cin >> add;
			builder.SetHighColont(HighColont(body, add));
		}
		//SetHighColontWithNumber
		else if (command == "shcwn")
		{
			cout << "Enter body:" << endl;
			string body, add;
			int num;
			cin >> body;
			cout << "Enter add word:" << endl;
			cin >> add;
			cout << "Enter num:" << endl;
			cin >> num;
			builder.SetHighColont(HighColontWithNumber(body, add, num));
		}
		//SetLowColont
		else if (command == "slc")
		{
			string body; int num;
			cout << "Enter body:" << endl;
			cin >> body;
			cout << "Enter num:" << endl;
			cin >> num;
			builder.SetLowColont(LowColont(body, num));
		}
		//SetLowColontWithAddWord
		else if (command == "slcwaw")
		{
			string body, add; int num;
			cout << "Enter body:" << endl;
			cin >> body;
			cout << "Enter num:" << endl;
			cin >> num;
			cout << "Enter additional word:" << endl;
			cin >> add;
			builder.SetLowColont(LowColontWithAddWord(body, num, add));
		}
	} while (true);
	list<Report>::iterator list_iter = report_list.begin();
	ofstream fout("file.txt");
	for (int i = 0;i < report_list.size();i++)
	{
		list_iter->SaveToFile(fout);
		list_iter++;
	}
}