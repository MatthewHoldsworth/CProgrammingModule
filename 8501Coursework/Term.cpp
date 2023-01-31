#include "Term.h"

using namespace std;

Term::Term(int coef, int indi) :
	coefficient(coef),
	index(indi) {}

void Term::differentiate() {
	coefficient *= index;
	index -= 1;
}

void Term::integrate() {
	index += 1;
	coefficient /= index;
}

int Term::valueOf(int x) {
	return pow(x, index) * coefficient;
}