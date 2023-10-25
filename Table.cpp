#include "Table.h"

std::string Table::NextState(int input_signal, std::string current_state)
{
	std::string next_state;
	if (input_signal > f_table.size()) {
		std::cout << "Неверный номер входного сигнала!(\n" << std::endl;
	}
	else {

		next_state = this->f_table[input_signal-1];

		int state_index = 0;
		int i = 0;
		int cur_state_len = current_state.length() - 1;
		while (i <= cur_state_len) {
			state_index += ((int)current_state[i] - 48) * pow(10,(cur_state_len - i));
			i++;
		}
		//state_index -=;

		i = 1;
		int j = 0;
		while (i != state_index) {
			if (next_state[j] == ' ') {
				i++;
			}
			j++;
		}
		
		std::string tmp = "";
		while (next_state[j] != ' ') {
			tmp += next_state[j];
			j++;	
		}

		next_state = tmp;
	}

	return next_state;
}

std::string Table::NextState(int input_signal, int current_state)
{
	std::string next_state;
	if (input_signal > f_table.size()) {
		std::cout << "Неверный номер входного сигнала!(\n" << std::endl;
	}
	else {

		next_state = this->f_table[input_signal - 1];

		int i = 1;
		int j = 0;
		while (i != current_state) {
			if (next_state[j] == ' ') {
				i++;
			}
			j++;
		}

		std::string tmp = "";
		while (next_state[j] != ' ') {
			tmp += next_state[j];
			j++;
			if (j == next_state.length()) {
				break;
			}
		}

		next_state = tmp;
	}

	return next_state;
}

std::string Table::CurrentOutput(int input_signal, std::string current_state)
{
	std::string current_output;
	if (input_signal > g_table.size()) {
		std::cout << "Неверный номер входного сигнала!(\n" << std::endl;
	}
	else {

		current_output = this->g_table[input_signal - 1];

		int state_index = 0;
		int i = 0;
		int cur_state_len = current_state.length() - 1;
		while (i <= cur_state_len) {
			state_index += ((int)current_state[i] - 48) * pow(10, (cur_state_len - i));
			i++;
		}

		i = 1;
		int j = 0;
		while (i != state_index) {
			if (current_output[j] == ' ') {
				i++;
			}
			j++;
		}
	
		std::string tmp = "";
		while (current_output[j] != ' ') {
			tmp += current_output[j];
			j++;
		}

		current_output = tmp;

	}

	return current_output;
}

std::string Table::CurrentOutput(int input_signal, int current_state)
{
	std::string current_output;
	if (input_signal > g_table.size()) {
		std::cout << "Неверный номер входного сигнала!(\n" << std::endl;
	}
	else {

		current_output = this->g_table[input_signal - 1];

		int i = 1;
		int j = 0;
		while (i != current_state) {
			if (current_output[j] == ' ') {
				i++;
			}
			j++;
		}

		std::string tmp = "";
		while (current_output[j] != ' ') {
			tmp += current_output[j];
			j++;
			if (j == current_output.length()) {
				break;
			}
		}

		current_output = tmp;

	}

	return current_output;
}

Table::Table()
{
	std::ifstream f_table_i;
	std::string f_table_path = "f_table.txt";

	std::ifstream g_table_i;
	std::string g_table_path = "g_table.txt";

	f_table_i.open(f_table_path);
	if (!f_table_i.is_open()) {

		std::cout << "Ошибка открытия файла!(\n" << std::endl;

	}
	else {
		while (!f_table_i.eof()) {
			std::string tmp;
			getline(f_table_i, tmp);
			this->f_table.push_back(tmp);
		}
	}
	f_table_i.close();

	this->count_of_state = get_state_position(f_table[0]).size();
	this->count_of_Dtrig = ceil(log2(this->count_of_state));

	int max_output = 0;

	g_table_i.open(g_table_path);
	if (!g_table_i.is_open()) {

		std::cout << "Ошибка открытия файла!(\n" << std::endl;

	}
	else {
		while (!g_table_i.eof()) {
			std::string tmp;
			getline(g_table_i, tmp);
			for (int i = 0; i < std::strlen(&tmp[0]); i++) {
				if (max_output < (int)tmp[i]) {
					max_output = (int)tmp[i];
				}
			}
			this->g_table.push_back(tmp);
		}
	}
	this->count_of_output = max_output - 48 + 1;
	g_table_i.close();



}

int Table::StateCount()
{
	int len = this->f_table[0].length();
	int state_count = 1;
	for (int i = 0; i < len; i++) {
		if (this->f_table[0][i] == ' ') {
			state_count++;
		}

	}

	return state_count;
}

int Table::InputCount()
{
	return this->f_table.size();
}

std::vector<std::string> Table::CheckConnect(int first_state, int second_state)
{
	std::vector<std::string> tmp;
	int input_count = this->InputCount();

	for (int k = 1; k < input_count; k++) {
		if (this->NextState(k, first_state) != "-" && this->NextState(k, second_state) != "-" &&
			this->NextState(k, first_state) != this->NextState(k, second_state)
			) {
			if (this->CurrentOutput(k, first_state) == this->CurrentOutput(k, second_state) ||
				this->CurrentOutput(k, first_state) != "-" && this->CurrentOutput(k, second_state) == "-" ||
				this->CurrentOutput(k, first_state) == "-" && this->CurrentOutput(k, second_state) != "-"
				){
				tmp.push_back(this->NextState(k, first_state) + " " + this->NextState(k, second_state));
			}
			else {
				tmp.clear();
				tmp.push_back("~");
				break;
			}
		}
	}
	if (tmp.empty()) {
		tmp.push_back(" ");
	}
	return tmp;
}


void Table::CreateIncompleteTable(void)
{
	int state_count = this->StateCount(); 

	for (int i = 1; i < state_count; i++) {
		for (int j = i + 1; j <= state_count; j++) {
			this->connect_table.push_back(Connect(S(i), S(j), this->CheckConnect(i, j)));
		}

	}

}

std::vector<int> get_state_position(std::string input_str)
{
	std::vector<int> tmp;
	tmp.push_back(0);

	for (int i = 1; i < std::strlen(&input_str[0]); i++) {
		if ((input_str[i] == ' ') && (i+1 < std::strlen(&input_str[0]))) {
			tmp.push_back(i+1);
		}
	}

	return tmp;
}
/*
void Table::CountTheQuantityOfState(void)
{
	std::vector<std::string> tmp_table = this->f_table;
	std::vector<std::vector<int>> tmp_state_position;

	int table_len = tmp_table.size();

	for (int i = 0; i < tmp_table.size(); i++) {
		tmp_state_position.push_back(get_state_position(tmp_table[i]));
	}

	int table_wid = tmp_state_position[0].size();
	////////////////////////////////////////////////////////////////////

	int tmp_count_state = 0;



	this->count_of_state = tmp_count_state;
}
*/
void Table::GenerateGreyTable(void)
{
	std::vector<Grey> tmp_grey_str;
	std::vector<int> tmp_state_position = get_state_position(this->f_table[0]);

	int len_table = this->f_table.size();
	int widt_table = tmp_state_position.size();
	int tmp_index;
	

	for (int i = 0; i < len_table; i++) {
		tmp_grey_str.clear();
		tmp_state_position = get_state_position(this->f_table[i]);
		for (int j = 0; j < widt_table; j++) {
			tmp_index = get_indx_state(this->f_table[i], tmp_state_position[j]);
			tmp_grey_str.push_back(Grey(tmp_index));
		}
		this->grey_table.push_back(tmp_grey_str);
	}

}


std::string get_str_state(std::string input_str)
{
	std::string tmp = "";

	for (int i = 0; i < std::strlen(&input_str[0]); i++) {
		if (input_str[i] == ' ') {
			break;
		}
		tmp += input_str[i];
	}

	return tmp;
}


std::string get_str_state(std::string input_str, int start_index)
{
	std::string tmp = "";

	for (int i = start_index; i < std::strlen(&input_str[0]); i++) {
		if (input_str[i] == ' ') {
			break;
		}
		tmp += input_str[i];
	}

	return tmp;
}

int get_indx_state(std::string input_str, int start_index)
{
	std::string tmp = "";
	int tmp_int = 0;

	for (int i = start_index; i < std::strlen(&input_str[0]); i++) {
		if (input_str[i] == ' ') {
			break;
		}
		tmp += input_str[i];
	}

	int tmp_len = std::strlen(&tmp[0]);

	if (tmp == "-") {
		tmp_int = -1;
	}
	else {
		for (int i = 0; i < tmp_len; i++) {
			tmp_int += ((int)tmp[i] - 48) * pow(10, tmp_len - 1 - i);
		}
	}
	return tmp_int;
}



void Print_Table(std::vector<std::string> table)
{
	for (int i = 0; i < std::strlen(&table[0][0]); i++) {
		std::cout << "_";
	}
	std::cout << "\n\n";
	std::vector<int> tmp_position;
	for (int i = 0; i < table.size(); i++) {
		tmp_position = get_state_position(table[i]);
		std::cout << table[i] << std::endl;
	}
	for (int i = 0; i < std::strlen(&table[0][0]); i++) {
		std::cout << "_";
	}
}

void Print_Table(std::vector<std::vector<Grey>> table, int count_state)
{
	for (int i = 0; i < table[0].size(); i++) {
		std::cout << "_";
	}
	std::cout << std::endl;
	for (int i = 1; i < count_state+1; i++) {
		std::cout<< S(i) << "=" << to_bin(i ^ (i >> 1)) << "; ";
	}
	std::cout << std::endl;
	for (int i = 0; i < table[0].size(); i++) {
		std::cout << "_";
	}

	std::cout << "\n\n";
	std::vector<int> tmp_position;
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			std::cout << table[i][j].State << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < table[0].size(); i++) {
		std::cout << "_";
	}
}


std::string to_bin(int number)
{
	int i, beffor = -1;
	std::string tmp = "";

	while (number > 0) {
		
			for (i = 0; pow(2, i) <= number; i++);
			i -= 1;
			if (beffor == -1) {
				tmp += "1";
				beffor = i;
			}
			else if (beffor - i == 1) {
				tmp += "1";
				beffor = i;
			}
			else {
				beffor -= 1;
				while (beffor > i) {
					tmp += "0";
					beffor -= 1;
				}
				tmp += "1";
			}
			number -= pow(2, i);
		
			if (number == 0) {
			while (beffor > 0) {
				tmp += "0";
				beffor -= 1;
			}
		}
	}
	if (tmp == "") tmp = "0";
	return tmp;

}