

#include <iostream>
#include <vector>
#include <string>

#ifndef CONNECT_H
#define CONNECT_H

#define S(x) ("S" + std::to_string(x))

class Connect {
public:
	std::string connected_state[2];
	std::vector<std::string> pairing_state;
public:
	Connect(std::string first_state, std::string second_state, std::vector<std::string> pairing_state_i);


};


#endif