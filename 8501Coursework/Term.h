#pragma once
#include <cmath>
#include <iostream>

class Term
{
public:
	Term(int coef, int indi);

	void integrate();
	void differentiate();
	int valueOf(int);

	int coefficient;
	int index;
private:

};