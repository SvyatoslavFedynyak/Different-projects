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
					mov edx, matrix//������ ������� � ������
					mov eax, i//������� �
					mov edx, [edx + 4 * eax]//edx=matrix[i]
					mov eax, j//eax = j
					mov edx, [edx + 4 * eax]//edx=matrix[i][j]
					test first_summ, 1//��������� �� �� ����� ���� �������(�����)
					jnz f_s//��������� �������
					jz n_f_s

				f_s:
					add prev_summ, edx//������ �� 1 ����
					jmp _summary

				n_f_s:
					add curr_summ, edx//������ �� ������� ����
					jmp _summary

				_summary:
					mov eax, n//������ ������
					dec eax//�������� �� 1
					test eax, j//���������� �� �� ������� ������ �����
					jnz _end_of_line
					jz not_end_of_line
					
				_end_of_line:
					test first_summ, 1//���� ������� �������� �� ��� ����
						jnz f_s2
						jz n_f_s2
					
				f_s2:
					mov first_summ, 0//����� �� ��� �� ����� ����
					mov horizontal, 1//���� �� ���������� ������� 1 ����
					jmp _end
					

				n_f_s2:
					mov eax, prev_summ//������ ������
					test eax, curr_summ//��������� �������� � ���� ���������
					jz _true
					jnz _false

				_true:
					mov horizontal, 1//������� �� ��� ������(������������ ��)
					jmp _end

				_false:
					mov horizontal, 0//��� �� ������
					jmp _end

				not_end_of_line://���� �� ����� �� ������ ��� ����
					jmp _end

				_end:
			}
			if (horizontal == 0)break;//�������� ���� ������� ����� ��� ���������� ����
		}
	}
	//for (int j = 0;j < n;j++)
	//{
	//	for (int i = 0; i < n; i++)
	//	{
	//		_asm
	//		{
	//			mov edx, matrix//������ ������� � ������
	//			mov eax, i//������� �
	//			mov edx, [edx + 4 * eax]//edx=matrix[i]
	//			mov eax, j//eax = j
	//			mov edx, [edx + 4 * eax]//edx=matrix[i][j]
	//			test first_summ, 1//��������� �� �� ����� ���� �������(�����)
	//			jnz f_s//��������� �������
	//			jz n_f_s

	//			f_s :
	//			add prev_summ, edx//������ �� 1 ����
	//				jmp _summary

	//				n_f_s :
	//			add curr_summ, edx//������ �� ������� ����
	//				jmp _summary

	//				_summary :
	//			mov eax, n//������ ������
	//				dec eax//�������� �� 1
	//				test eax, j//���������� �� �� ������� ������ �����
	//				jnz _end_of_line
	//				jz not_end_of_line

	//				_end_of_line :
	//			test first_summ, 1//���� ������� �������� �� ��� ����
	//				jnz f_s2
	//				jz n_f_s2

	//				f_s2 :
	//			mov first_summ, 0//����� �� ��� �� ����� ����
	//				mov horizontal, 1//���� �� ���������� ������� 1 ����
	//				jmp _end


	//				n_f_s2 :
	//			mov eax, prev_summ//������ ������
	//				test eax, curr_summ//��������� �������� � ���� ���������
	//				jz _true
	//				jnz _false

	//				_true :
	//			mov horizontal, 1//������� �� ��� ������(������������ ��)
	//				jmp _end

	//				_false :
	//			mov horizontal, 0//��� �� ������
	//				jmp _end

	//				not_end_of_line ://���� �� ����� �� ������ ��� ����
	//			jmp _end

	//				_end :
	//		}
	//		if (horizontal == 0)break;//�������� ���� ������� ����� ��� ���������� ����
	//	}
	//}//� ���� ���� ���������� ������� ��� �� ��������� ���� � �� j ��� ���� ���������� �� �������� � �� ������
	if (horizontal == 0)cout << "Matrix isn't magic" << endl;
	else cout << "Matrix is magic" << endl;
	system("pause");
}