#include <iostream>
#include <Windows.h>
using namespace std;
//��������� � FORMAT �� 3 %s ��� ��������� �-� ���
char FORMAT[] = "%s %s %s %s %s\n";
char HELLO[] = "Hello";
char WORLD[] = "world";
//��������� ��� �����
char BY[] = "by";
char NAME1[] = "Svyatoslav";
char NAME2[] = "Fedydnyak";

int main()
{
	_asm
	{
		//�������� �� � ���
		mov eax, offset NAME1
		push eax
		mov eax, offset NAME2
		push eax
		mov eax, offset BY
		push eax
		mov eax, offset WORLD
		push eax
		mov eax, offset HELLO
		push eax
		mov eax, offset FORMAT
		push eax
		
		mov edi, printf
		call edi
		//��������� �� 3 pop ebx
		pop ebx
		pop ebx
		pop ebx
		pop ebx
		pop ebx
		pop ebx
	}
	system("pause");
}
