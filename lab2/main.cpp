#include <iostream>
#include <vector>
#include <string>
#include "Connect.h"
#include "Table.h"
#include <fstream> 
#include "Grey.h"

int main()
{
	Table struct_sin;
	setlocale(0, "RUSSIAN");

	struct_sin.GenerateGreyTable();

	std::cout << "\nf_table\n";
	Print_Table(struct_sin.f_table);

	std::cout << "\n\n";

	std::cout << "\ng_table\n";
	Print_Table(struct_sin.g_table);

	std::cout << "\nGrey_table\n";
	Print_Table(struct_sin.grey_table, struct_sin.count_of_state);

	struct_sin.KeyGen();

	std::cout << "\nCDNF\n";

	struct_sin.Create_CDNF();
	struct_sin.CreateOCDNF();
	struct_sin.CreateQCDNF();
	struct_sin.CreateOutputCDNF();

	struct_sin.WriteToFile();

	struct_sin.OverwriteMinimalFile();

	struct_sin.ReadMDNF();

	while(!struct_sin.CheckCorrectnessOfMinimisationByKey());

	std::cout << "Проверенно ключем, все гуд)" << std::endl;

	return 0;
}