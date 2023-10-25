#include <iostream>
#include <vector>
#include <string>
#include "Connect.h"
#include <fstream>
#include <math.h>


#ifndef GREY_H
#define GREY_H

class Grey {
public:
	std::string State;
	int grey_code;

	Grey(int state_index);

};



#endif