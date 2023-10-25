#include "Connect.h"

Connect::Connect(std::string first_state, std::string second_state, std::vector<std::string> pairing_state_i)
{
	this->connected_state[0] = first_state;
	this->connected_state[1] = second_state;

	this->pairing_state = pairing_state_i;

}