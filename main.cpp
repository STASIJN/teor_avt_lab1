#include <iostream>
#include <fstream>
#include <string>
#include "Impl.h"
#include "DNF.h"
#include <stdarg.h>

using namespace std;





int main()
{
	setlocale(LC_ALL, "Rus");

	ifstream scale;
	ofstream mdnf;
	string path = "scale.txt";
	string mdnf_path = "mdnf.txt";
	string SDNF;
	scale.open(path);

	if (!scale.is_open()) {

		cout << "Ошибка открытия файла!(\n" << endl;

	}
	else {

		getline(scale, SDNF);
		scale.close();
		DNF dnf_c(SDNF);
		dnf_c.Gluing();
		dnf_c.MDNF();
		SDNF = dnf_c.string_assembly();
		cout << SDNF << endl;
		mdnf.open(mdnf_path);
		if (!mdnf.is_open()) {

			cout << "Ошибка открытия файла!(\n" << endl;

		}
		else {
			mdnf << SDNF;
		}
	}


	return 0;
}