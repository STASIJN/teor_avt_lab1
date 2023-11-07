#include <iostream>
#include <vector>
#include <string>
#include "Connect.h"
#include <fstream>
#include <math.h>

#ifndef KEY_H
#define KEY_H



class Key {
public:
	std::string Input;
	std::string State;
	std::string Output;

	Key(std::string Input_i, std::string State_i, std::string Output_i);

};



#endif