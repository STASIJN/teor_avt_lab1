#include "DNF.h"

DNF::DNF(std::string SDNF)
{
	int i;

	for (i = 0; pow(2, i) < strlen(&SDNF[0]); i++);
	implicat_size = i;

	for (i = 0; i < strlen(&SDNF[0]); i++) {

		if (SDNF[i] == '1' || SDNF[i] == '-') {
			Data.push_back(Impl(i));
			if (SDNF[i] == '1') {
				Num_tabl.push_back(i);
			}
		}

	}

}

void DNF::Gluing(void)
{
	std::vector<Impl> temp;
	std::vector<Impl> tdnf;
	this->TDNF = this->Data;

	do {
		temp.clear();
		for (std::vector<Impl>::iterator it = this->TDNF.begin(); it < this->TDNF.end() - 1; advance(it, 1)) {
			for (std::vector<Impl>::iterator jt = it + 1; jt < this->TDNF.end(); advance(jt, 1)) {
				if (*it < *jt) {
					temp.push_back(Impl(*it, Impl::Count(*it, *jt)));
					it->Pw = true;
					jt->Pw = true;
				}

			}
		}

		for (std::vector<Impl>::iterator it = this->TDNF.begin(); it < this->TDNF.end(); advance(it, 1)) {
			if (it->Pw) {
				it->Pw = 0;
			}
			else {
				tdnf.push_back(*it);
			}
		}

		if (this->TDNF.size() != temp.size() && !temp.empty()) {
			this->TDNF.clear();
			std::vector<Impl>::iterator it;
			for ( it = temp.begin(); it < temp.end() - 1; advance(it, 1)) {
				if (it->Pw != true) {
					this->TDNF.push_back(*it);
				}
				for (std::vector<Impl>::iterator jt = it + 1; jt < temp.end(); advance(jt, 1)) {
					if (*it == *jt) {
						it->Pw = true;
						jt->Pw = true;
					}
				}
			}
			if (it->Pw != true) {
				this->TDNF.push_back(*it);
			}
		}

		
		
	} while (!temp.empty());

	this->TDNF = tdnf;

	return;
}


void DNF::MDNF(void)
{
	std::vector<Impl> temp;
	std::vector<int> N = this->Num_tabl;

	//int del = 1;

	bool StrDeletPossible = false;

	std::vector<Impl>::iterator it;

	for (int i = 0; i < this->TDNF.size() /* - del*/; i++) {
		temp = this->TDNF;
		it = temp.begin() + i;
		temp.erase(it);
		for (std::vector<int>::iterator kt = N.begin(); kt < N.end(); advance(kt, 1)) {
			StrDeletPossible = false;
			for (it = temp.begin(); it < temp.end(); advance(it, 1)) {
				if (*it + *kt) {
					StrDeletPossible = true;
					break;
				}
			}
			if (!StrDeletPossible) {
				break;
			}
		}
		if (StrDeletPossible) {
			this->TDNF = temp;
			i--;
			//del++;
		}
	}
	return;
}

std::string DNF::string_assembly()
{
	std::vector<Impl> temp = this->TDNF;
	

	std::vector<Impl>::iterator it;

	std::string out;

	for (it = temp.begin(); it < temp.end(); advance(it, 1)) {
		for (int i = this->implicat_size - 1; i >= 0; i--) {
			if ((int)pow(2, i) & it->P) {
				out += "-";
			}
			else if ((int)pow(2, i) & it->Num) {
				out += "1";
			}
			else {
				out += "0";
			}
		}
		out += "\n";
	}
	return out;
}