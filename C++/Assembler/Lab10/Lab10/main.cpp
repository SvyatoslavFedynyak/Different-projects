#include <iostream>
using namespace std;
int main()
{
	_int32 arr = 255555555555555;//(‭11101000|011|0|110|10010101000|0110|111111100011100011‬) - результат має бути 3
	int res=0;
	int mask = 0110;
	_asm
	{
		mov cx, 48//кількість проходів циклу
		mov eax, mask //маска 0110
	check://початок циклу
		mov ebx, arr//задаємо масив
		and ebx, eax//накладання маски
		jz _true//перехід якщо істина
		jnz _false//якщо фальш
	_true:
		inc res//збільшуємо результат
		jmp _end//перехід в кінець
	_false:
		jmp _end
	_end:
		shl eax, 1//зсув вправо на 1 біт
		dec cx//зменшення проходження циклу на 1
	loop check//кінець циклу
	}
	cout << res << endl;
	system("pause");
}