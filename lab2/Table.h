
#include <iostream>
#include <vector>
#include <string>
#include "Connect.h"
#include <fstream>
#include <math.h>
#include "Grey.h"
#include "Key.h"

#ifndef TABLE_H
#define TABLE_H

class Table {
public:
	std::vector<std::string> f_table;
	std::vector<std::string> g_table;
	std::vector<Connect> connect_table;
	std::vector<std::vector<Grey>> grey_table;
	
	std::vector<std::vector<std::string>> CDNF;
	std::vector<std::vector<std::string>> CDNF_out;
	std::vector<std::string> Q_CDNF;
	std::vector<std::string> O_CDNF;
	std::vector<Key> Check_Key;

	std::vector<std::vector<std::string>> Q_MDNF;
	std::vector<std::vector<std::string>> O_MDNF;


	int count_of_state;
	int count_of_output;
	int count_of_Dtrig;
	int count_of_input;

	int StateCount();
	int InputCount();



	std::string NextState(int input_signal, std::string current_state);
	std::string CurrentOutput(int input_signal, std::string current_state);

	std::string NextState(int input_signal, int current_state);
	std::string CurrentOutput(int input_signal, int current_state);

	std::vector<std::string> CheckConnect(int first_state, int second_state);

	void CreateIncompleteTable(void);

	Table();
	
	void GenerateGreyTable(void);

	//void CountTheQuantityOfState(void);

	void Create_CDNF(void);

	void CreateQCDNF(void);

	void CreateOCDNF(void);

	void CreateOutputCDNF(void);

	void WriteToFile();
	void OverwriteMinimalFile();
	
	void KeyGen();
	bool CheckCorrectnessKey();

	bool CheckCorrectnessOfMinimisationByKey();

	void ReadMDNF();

};
void Print_Table(std::vector<std::string> table);
void Print_Table(std::vector<std::vector<Grey>> table, int count_state);

std::vector<int> get_state_position(std::string input_str);
std::string get_str_state(std::string input_str);
std::string get_str_state(std::string input_str, int start_index);
int get_indx_state(std::string input_str, int start_index);

std::string to_bin(int number);
std::string to_bin(int number, int len);

int to_int(std::string impl);

void Write_To_File(std::string path, std::string CDNF);

void Overwrite_Minimal_File(std::string path);

int I(std::string);

std::string Check_Compliance(std::vector<std::string> mdnf, std::string required_number, std::string input);



#endif
