#include <iostream>
#include <cmath>
using namespace std;
const int n = 5;
const float _26 = 26, _1 = 1, _4=4;
float c, d;
float a[n], y[n];
void Calculate()
{
	_asm
	{
		//заповнення регістрів
		lea esi, a
		lea edi, y
		mov ecx, n
		finit
		cycle_start:
		fld [esi]//а[i] 
			fsub c//a[i]-c
			fld _1//заносимо 1 для арктангенса
			fpatan//arctg(a[i]-c) 
			fld d//заносим d
			fmul //arctg(a[i]-c)*d
			fadd _26//arctg(a[i]-c)*d+26
			fld _4//4
			fmul c//4*c
			fld [esi]//заносимо a[i]
			fdiv //4*c/a[i]
			fadd _1//4*c/a[i]+1
			fdiv//(arctg(a[i]-c)*d+26)/(4*c/a[i]+1)
			fstp [edi]//запис у відповідь
			//перехід до наступних
			add esi, 4
			add edi, 4
		loop cycle_start//кінець циклу
	}
}
void EnterData()
{
	cout << "Enter c and d:" << endl;
	cin >> c >> d;
	for (int i = 0;i < n;i++)
	{
		cout << "Enter a[i]: ";
		cin >> a[i];
	}
	cout << endl;
}
void ShowResult()
{
	for (int i = 0;i < n;i++)
	{
		cout << "Y[" << i << "]= " << y[i] << endl;
	}
}
void CalcuylateCpp()
{
	for (int i = 0;i < n;i++)
	{
		y[i] = (atan(a[i] - c)*d + 26) / (((4 * c) / a[i]) + 1);
	}
}
int main()
{
	EnterData();
	Calculate();
	cout << "By Assembler:" << endl;
	ShowResult();
	CalcuylateCpp();
	cout << "By C++:" << endl;
	ShowResult();
	system("pause");
}