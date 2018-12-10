#include <iostream>
#include <time.h>
using namespace std;
int main()
{
	srand(time(NULL));
	cout << "Enter size of matrix:" << endl;
	int n;
	cin >> n;
	int** matrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << "|";
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j];
			if (!(j == n - 1))cout << " ";
		}
		cout << "|" << endl;
	}
	int curr_summ = 0, prev_summ=0;
	int first_summ=1;
	int horizontal=1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;j++)
		{
			_asm
			{
					mov edx, matrix//задаємо матрицю в регістр
					mov eax, i//передаєм і
					mov edx, [edx + 4 * eax]//edx=matrix[i]
					mov eax, j//eax = j
					mov edx, [edx + 4 * eax]//edx=matrix[i][j]
					test first_summ, 1//перевіряєм це це перша сума сповпця(рядка)
					jnz f_s//відповідний перехід
					jz n_f_s

				f_s:
					add prev_summ, edx//додаємо до 1 суми
					jmp _summary

				n_f_s:
					add curr_summ, edx//додаємо до нинішньої суми
					jmp _summary

				_summary:
					mov eax, n//задаємо регістр
					dec eax//зменшуємо на 1
					test eax, j//перевіряємо чи не останній прохід циклу
					jnz _end_of_line
					jz not_end_of_line
					
				_end_of_line:
					test first_summ, 1//якщо останній перевірка на поч суму
						jnz f_s2
						jz n_f_s2
					
				f_s2:
					mov first_summ, 0//тепер це вже не перша сума
					mov horizontal, 1//поки що виконується оскільки 1 сума
					jmp _end
					

				n_f_s2:
					mov eax, prev_summ//задаємо регістр
					test eax, curr_summ//порівнюємо теперішню і суму істинності
					jz _true
					jnz _false

				_true:
					mov horizontal, 1//матриця ще далі магічна(необовязкова дія)
					jmp _end

				_false:
					mov horizontal, 0//вже не магічна
					jmp _end

				not_end_of_line://якщо не кінець лінії заново йде цикл
					jmp _end

				_end:
			}
			if (horizontal == 0)break;//перевірка після кожного циклу для оптимізації коду
		}
	}
	//for (int j = 0;j < n;j++)
	//{
	//	for (int i = 0; i < n; i++)
	//	{
	//		_asm
	//		{
	//			mov edx, matrix//задаємо матрицю в регістр
	//			mov eax, i//передаєм і
	//			mov edx, [edx + 4 * eax]//edx=matrix[i]
	//			mov eax, j//eax = j
	//			mov edx, [edx + 4 * eax]//edx=matrix[i][j]
	//			test first_summ, 1//перевіряєм це це перша сума сповпця(рядка)
	//			jnz f_s//відповідний перехід
	//			jz n_f_s

	//			f_s :
	//			add prev_summ, edx//додаємо до 1 суми
	//				jmp _summary

	//				n_f_s :
	//			add curr_summ, edx//додаємо до нинішньої суми
	//				jmp _summary

	//				_summary :
	//			mov eax, n//задаємо регістр
	//				dec eax//зменшуємо на 1
	//				test eax, j//перевіряємо чи не останній прохід циклу
	//				jnz _end_of_line
	//				jz not_end_of_line

	//				_end_of_line :
	//			test first_summ, 1//якщо останній перевірка на поч суму
	//				jnz f_s2
	//				jz n_f_s2

	//				f_s2 :
	//			mov first_summ, 0//тепер це вже не перша сума
	//				mov horizontal, 1//поки що виконується оскільки 1 сума
	//				jmp _end


	//				n_f_s2 :
	//			mov eax, prev_summ//задаємо регістр
	//				test eax, curr_summ//порівнюємо теперішню і суму істинності
	//				jz _true
	//				jnz _false

	//				_true :
	//			mov horizontal, 1//матриця ще далі магічна(необовязкова дія)
	//				jmp _end

	//				_false :
	//			mov horizontal, 0//вже не магічна
	//				jmp _end

	//				not_end_of_line ://якщо не кінець лінії заново йде цикл
	//			jmp _end

	//				_end :
	//		}
	//		if (horizontal == 0)break;//перевірка після кожного циклу для оптимізації коду
	//	}
	//}//є така сама асемблерна вставка але за поміняними місця і та j щоб сума рахувалась по стовпцям а не рядкам
	if (horizontal == 0)cout << "Matrix isn't magic" << endl;
	else cout << "Matrix is magic" << endl;
	system("pause");
}