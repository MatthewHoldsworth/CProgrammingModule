#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Term.h"

class Expression
{
public:
	Expression(std::vector<Term>);
	Expression();

	void addTerm(Term);
	void printExpression();
	void generateExpression(const std::vector<int>&);
	void saveToFile(const std::string&);
	void readFromFile(const std::string&);
	void generateTerms(std::vector<int>&, const std::vector<int>&, const int);
	int calculateForX(int);
	int getTermsSize();
	Term generateTerm(const std::vector<int>&);
	std::vector<Term> getTerms();

	std::vector<int> outputSet;
private:
	std::vector<Term> terms;

	void rewriteForConstraint(int, int*, int*);
	void parseFromFile(std::string&);
	void rewrite();
	bool validate();
	int integrateValue(int, int);
};