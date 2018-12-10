#include "compiler_and_virtual_mashine.h"
void main()
{
	//code_for_compiler2.txt або code_for_compiler.txt або exe_test.txt
	ifstream fin_com("exe_test.txt");
	compiler my_compiler;
	my_compiler.read_from_file(fin_com);
	fin_com.close();

	ofstream fout_com("code_for_machine.txt");
	my_compiler.execute();
	my_compiler.write(fout_com);
	fout_com.close();

	ifstream fin_vir_mach("code_for_machine.txt");
	virtual_machine my_virtual_machine;
	my_virtual_machine.read_from_file(fin_vir_mach);
	fin_vir_mach.close();

	my_virtual_machine.execute();

	system("pause");
}