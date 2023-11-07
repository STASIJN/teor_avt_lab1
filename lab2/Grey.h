
#include <iostream>
#include <vector>
#include <string>
#include "Connect.h"
#include <fstream>
#include <math.h>

#define G(x) ((x-1) ^ ((x-1)>>1))

#ifndef GREY_H
#define GREY_H

class Grey {
public:
	std::string State;
	int grey_code;
	std::string grey_str;

	Grey(int state_index, std::string str);

};



#endif