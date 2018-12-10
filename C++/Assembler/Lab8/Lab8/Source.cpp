#include <iostream>
using namespace std;
void main() {
	int year, leap;
	cin >> year;
	__asm {
		mov ebx, 0
		mov ecx, 400
		mov eax, year
		cdq

		div ecx
		test edx, edx
		jz is_leap
		mov eax, year
		cdq
		mov ecx, 4
		div ecx
		test edx, edx
		jz maybe_leap
		jmp result
		is_leap :
		mov ebx, 1
			jmp result
			maybe_leap :
		mov eax, year
			cdq
			mov ecx, 100
			div ecx
			test edx, edx
			jz result
			jmp is_leap
			result :
		mov leap, ebx
	}
	if (leap > 0) { cout << "Yes" << endl; }
	else { cout << "No" << endl; }
	system("pause");
}