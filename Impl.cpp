#include "Impl.h"

Impl::Impl(int Num_i)
{
	Num = Num_i;
	Ind = 0;
	int i;
	for (i = 0; pow(2, i) < Num; i++);

	for (; i >= 0; i--){

		if (pow(2, i) == Num) {
			Ind++;
			i = -1;
			continue;
		}
		if (pow(2, i) < Num){
			Num -= pow(2, i);
			Ind++;
		}
		
	}
	Num = Num_i;
	P = 0;
	Pw = 0;
	Inf = 0;
}

Impl::Impl(Impl& other, int P_i)
{
	this->Num = other.Num;
	this->Ind = other.Ind;
	this->Inf = other.Inf;
	this->P = other.P + P_i;
	this->Pw = false;

}

int Impl::Count(int Num)
{
	int i, ret;
	for (i = 0; pow(2, i) < Num; i++);

	if (pow(2, i) != Num && Num != 0) {
		ret = 0;
	}
	else {
		ret = pow(2, i);
	}
	return ret;
}


bool Impl::operator < (const Impl other)
{
	bool ret;
	
	if (this->P == other.P &&
		other.Ind - this->Ind == 1 &&
		this->Num < other.Num &&
		Count(other.Num - this->Num) != 0) {

		ret = true;
	}
	else {

		ret = false;
	}

	return ret;
}

bool Impl::operator == (const Impl other)
{
	bool ret;

	if (this->P == other.P &&
		this->Num == other.Num) {

		ret = true;
	}
	else {

		ret = false;
	}

	return ret;
}

bool Impl::operator + (int N)
{
	bool ret;
	if ((N & (~this->P)) == this->Num) {
		ret = true;
	}
	else {
		ret = false;
	}
	return ret;
}

int Impl::Count(const Impl& a, const Impl& b)
{
	return (Count(b.Num - a.Num));

}

void Impl::SetPw(void)
{
	this->Pw = 1;
}

/*std::string Impl::operator << (Impl)
{


}*/