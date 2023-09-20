#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef IMPL_H
#define IMPL_H

class Impl
{
public:
	int Num;
	int Ind;
	int P;
	bool Pw;
	bool Inf;

	static int Count(int);

public:
	Impl(int);
	Impl(Impl&, int);
	static int Count(const Impl&, const Impl&);
	//~Impl();
	void SetPw(void);
	static Impl Patch(Impl&, Impl&);
	bool operator < (Impl);
	bool operator == (Impl);
	bool operator + (int);
	//std::string operator << (Impl);
};

#endif