#include "OutputSet.h"


using namespace std;


OutputSet::OutputSet(const vector<int> input) :
	yValues(input) {
}

OutputSet::OutputSet(string& filename) {
	readFromFile(filename);
}

OutputSet::OutputSet() {
}

void OutputSet::printSet() {
	if (yValues.size() != 0) {
		for (int i = 0; i < yValues.size() - 1; i++) cout << yValues[i] << ',';
		cout << yValues.back() << endl;
	}
}

void OutputSet::saveToFile(const string& filename) {
	try {
		ofstream outputFile(filename + ".txt", std::ios_base::app);
		stringstream line;
		for (auto it = yValues.begin(); it != yValues.end(); it++) {
			if (it != yValues.begin()) line << ',';
			line << *it;
		}
		outputFile << line.str() << '\n';
		outputFile.close();
	}catch (exception const& e) {
		cout << endl << "File read error" << endl;
	}
}

void OutputSet::readFromFile(const string& filename) {
	yValues.clear();
	Expression expression;
	try {
		ifstream outputFile(filename + ".txt", std::ios_base::in);
		string line;
		getline(outputFile, line);
		parseFromFile(line, filename, &outputFile);
		outputFile.close();
	}catch (exception const& e) {
		cout << endl << "File write error" << endl;
	}
}

void OutputSet::parseFromFile(string& line, const string& filename, ifstream* outputFile) {
	Expression expression;
	while (line.size() != 0) {
		yValues.clear();
		while (line.find(',') != string::npos) {
			yValues.push_back(stoi(line.substr(0, line.find(','))));
			line = line.substr(line.find(',') + 1, line.size() - 1);
		}yValues.push_back(stoi(line));
		expression.generateExpression(yValues);
		expression.saveToFile(filename + "Expressions");
		getline(*outputFile, line);
	}
}

vector<int> OutputSet::getValues() {
	return yValues;
}