#include "Grey.h"

Grey::Grey(int state_index, std::string str)
{
	if (state_index == -1) {
		this->State = "-";
		this->grey_code = -1;

	}
	else {
		this->State = S(state_index);

		this->grey_code = state_index ^ (state_index >> 1);

	}
	this->grey_str = str;
}
