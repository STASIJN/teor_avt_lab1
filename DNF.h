#include <iostream>
#include <vector>
#include <string>
#include "Impl.h"

#ifndef DNF_H
#define DNF_H

class DNF
{
public:
	std::vector<Impl> Data;
	std::vector<Impl> TDNF;
	std::vector<int> Num_tabl;
	int implicat_size;
public:
	DNF(std::string);
	//~DNF();
	void Gluing(void);
	void Minimize();
	void MDNF(void);
	void Print(std::ostream &);
	Impl& GetImpl(int);
	std::string string_assembly();
};

#endif