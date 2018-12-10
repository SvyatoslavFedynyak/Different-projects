#include <iostream>
#include <string>
#include <fstream>
#include<windows.h>
using namespace std;
struct Good
{
	int code;
	string name;
	string producer;
	double price;
	int number;
	Good() :code(0), name(""), producer(""), price(0), number(0) {};
	Good(int code_, string name_, string producer_, double price_, int number_)
	{
		code = code_;
		name = name_;
		producer = producer_;
		price = price_;
		int number = number_;
	}
};
struct Shop
{
	string name;
	string adress;
	string type;
	Shop() :name(""), adress(""), type("") {};
	Shop(string name_, string adress_, string type_)
	{
		name = name_;
		adress = adress_;
		type = type_;
	}
};
class TradePost
{
private:
	Shop shop;
	int num;
	Good* good;
public:
	TradePost();
	TradePost(int);
	string GetShopName() { return shop.name; }
	string GetShopAdress() { return shop.adress; }
	int GetNumOfGoods() { return num; }
	string GetGoogProducer(int num) { return good[num].producer; }
	void Show();
	void EnterInfo();
	void ReadFromFile(ifstream& in);
	void SaveToFile(ofstream& out);
};
TradePost::TradePost()
{
	good = new Good;
}
TradePost::TradePost(int n)//1 завдання
{
	num = n;
	good = new Good[n];
}
void TradePost::EnterInfo()
{
	cout << "Enter name" << endl;
	cin >> shop.name;
	cout << "Enter adress" << endl;
	cin >> shop.adress;
	cout << "Enter type" << endl;
	cin >> shop.type;
	for (int i = 0;i < num;i++)
	{
		cout << "Enter good name" << endl;
		cin >> good[i].name;
		cout << "Enter code" << endl;
		cin >> good[i].code;
		cout << "Enter number" << endl;
		cin >> good[i].number;
		cout << "Enter price" << endl;
		cin >> good[i].price;
		cout << "Enter producer" << endl;
		cin >> good[i].producer;
	}
}
void TradePost::Show()
{
	cout << "Shop name is: " << shop.name << endl;
	cout << "Shop adress is: " << shop.adress << endl;
	cout << "Shop type is: " << shop.type << endl;
	for (int i = 0;i < num;i++)
	{
		cout << "Good name is: " << good[i].name << endl;
		cout << "Good code is: " << good[i].code << endl;
		cout << "Good number is: " << good[i].number << endl;
		cout << "Good price is: " << good[i].price << endl;
		cout << "Good producer is: " << good[i].producer << endl;
	}
}
void TradePost::SaveToFile(ofstream& out)//3 завдання(2 частна)
{
	int shop_name_lenght = (int)shop.name.length() + 1;
	int shop_adress_lenght = (int)shop.adress.length() + 1;
	int shop_type_lenght = (int)shop.type.length() + 1;
	int* good_name_lenght = new int[num];
	int* good_producer_lenght = new int[num];
	for (int i = 0;i < num;i++)
	{
		good_name_lenght[i] = (int)good[i].name.length() + 1;
		good_producer_lenght[i] = (int)good[i].producer.length() + 1;
	}
	out.write((char*)&shop_name_lenght, sizeof(shop_name_lenght));
	out.write(shop.name.c_str(), shop_name_lenght);
	out.write((char*)&shop_adress_lenght, sizeof(shop_adress_lenght));
	out.write(shop.adress.c_str(), shop_adress_lenght);
	out.write((char*)&shop_type_lenght, sizeof(shop_type_lenght));
	out.write(shop.type.c_str(), shop_type_lenght);
	for (int i = 0;i < num;i++)
	{
		out.write((char*)&good_name_lenght, sizeof(good_name_lenght));
		out.write(good[i].name.c_str(), good_name_lenght[i]);
		out.write((char*)&good_producer_lenght, sizeof(good_producer_lenght));
		out.write(good[i].producer.c_str(), good_producer_lenght[i]);
		out.write((char*)&good[i].code, sizeof(good[i].code));
		out.write((char*)&good[i].number, sizeof(good[i].number));
		out.write((char*)&good[i].price, sizeof(good[i].price));
	}
}
void TradePost::ReadFromFile(ifstream& in)//2 завдання
{
	int shop_name_lenght;
	int shop_adress_lenght;
	int shop_type_lenght;
	int* good_name_lenght = new int[num];
	int* good_producer_lenght = new int[num];
	char* buffer;
	in.read((char*)&shop_name_lenght, sizeof(shop_name_lenght));
	buffer = new char[shop_name_lenght];
	in.read(buffer, shop_name_lenght);
	shop.name = buffer;
	in.read((char*)&shop_adress_lenght, sizeof(shop_adress_lenght));
	buffer = new char[shop_adress_lenght];
	in.read(buffer, shop_adress_lenght);
	shop.adress = buffer;
	in.read((char*)&shop_type_lenght, sizeof(shop_type_lenght));
	buffer = new char[shop_type_lenght];
	in.read(buffer, shop_type_lenght);
	shop.type = buffer;
	for (int i = 0;i < num;i++)
	{
		in.read((char*)&good_name_lenght[i], sizeof(good_name_lenght[i]));
		buffer = new char[good_name_lenght[i]];
		in.read(buffer, good_name_lenght[i]);
		good[i].name = buffer;
		in.read((char*)&good_producer_lenght[i], sizeof(good_producer_lenght[i]));
		buffer = new char[good_producer_lenght[i]];
		in.read(buffer, good_producer_lenght[i]);
		good[i].producer = buffer;
		in.read((char*)&good[i].code, sizeof(good[i].code));
		in.read((char*)&good[i].number, sizeof(good[i].number));
		in.read((char*)&good[i].price, sizeof(good[i].price));
	}
}
double transkey(string line)
{
	int size=line.length();
	double res=line[0];
	for (int i = 1;i < size;i++)
	{
		res += line[i] / (28 * i);
	}
	return res;
}
void SortShopsEnter(int n, TradePost* arr, ofstream& out)//3 завдання(1 частна)
{
	TradePost temp;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n-1;j++)
		{
			if (transkey(arr[j].GetShopAdress) > transkey(arr[j + 1].GetShopAdress))
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
	int* shop_adress_lenght = new int[n];
	for (int i = 0;i < n;i++)
	{
		shop_adress_lenght[i] = (int)arr[i].GetShopAdress().length() + 1;
		out.write((char*)&shop_adress_lenght[i], sizeof(shop_adress_lenght[i]));
		out.write(arr[i].GetShopAdress().c_str(), shop_adress_lenght[i]);
	}
}
void ShowShopsWithMaxNumOfGoods(int n, TradePost* arr)//4 завдання
{
	int max = 0;
	for (int i = 0;i < n;i++)
	{
		if (arr[i].GetNumOfGoods() > max)
		{
			max = arr[i].GetNumOfGoods();
		}
	}
	for (int i = 0;i < n;i++)
	{
		if (arr[i].GetNumOfGoods() == max)
		{
			arr[i].Show();
		}
	}
}
TradePost ShopWithMinNumOfGood(int n, TradePost* arr, string produser)//5 завдання
{
	struct post
	{
		int arr_number;
		int number;
		post() :number(0), arr_number(0) {};
	};
	post* post_witn_min_goods = new post[n];
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < arr[i].GetNumOfGoods();j++)
		{
			if (arr[i].GetGoogProducer(j) == produser)
			{
				post_witn_min_goods[i].arr_number++;
			}
		}
		post_witn_min_goods[i].number = i;
	}
	int min = post_witn_min_goods[0].arr_number;
	for (int i = 1;i < n;i++)
	{
		if (min < post_witn_min_goods[i].arr_number)
		{
			min = post_witn_min_goods[i].arr_number;
		}
	}
	int opennumber;
	for (int i = 0;i < n;i++)
	{
		if (min == post_witn_min_goods[i].arr_number)
		{
			opennumber = post_witn_min_goods[i].number;
			break;
		}
	}
	return arr[opennumber];
}
int main()
{
	system("pause");
}
