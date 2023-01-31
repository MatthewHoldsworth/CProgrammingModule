#pragma once
#include "Expression.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class OutputSet
{
public:
	OutputSet(std::vector<int>);
	OutputSet(std::string&);
	OutputSet();

	void saveToFile(const std::string&);
	void readFromFile(const std::string&);
	void printSet();
	std::vector<int> getValues();

private:
	std::vector<int> yValues;

	void parseFromFile(std::string&, const std::string&, std::ifstream*);
};