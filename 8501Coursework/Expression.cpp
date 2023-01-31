#include "Expression.h"

using namespace std;

Expression::Expression(vector<Term> input):
	terms(input){}

Expression::Expression()
{}

void Expression::addTerm(Term term) {
	if(term.coefficient!=0)terms.push_back(term);
}

vector<Term> Expression::getTerms() {
	return terms;
}

int Expression::getTermsSize() {
	return terms.size();
}

int Expression::calculateForX(int x) {
	int result = 0;
	for (int i = 0; i < terms.size(); i++) result += terms.at(i).valueOf(x);
	return result;
}

void Expression::printExpression() {
	if (terms.size() != 0) {
		for (int i = 0; i < terms.size() - 1; i++) cout << terms[i].coefficient << 'x' << terms[i].index << " + ";
		cout << terms[terms.size() - 1].coefficient << 'x' << terms[terms.size() - 1].index << endl;
	}
}

void Expression::saveToFile(const string& filename) {
	try {
		ofstream outputFile(filename + ".txt", std::ios_base::app);
		stringstream line;
		for (int i = 0; i < terms.size(); i++) {
			if (i != 0) line << ' ';
			line << terms[i].coefficient << 'x' << terms[i].index;
		}
		if(line.str().size()!=0)outputFile << line.str() << '\n';
		outputFile.close();
	}catch (exception const& e) {
		cout << endl << "File write error" << endl;
	}
}

void Expression::readFromFile(const string& filename) {
	terms.clear();
	string line;
	try {
		ifstream outputFile(filename + ".txt", std::ios_base::in);
		getline(outputFile, line);
		parseFromFile(line);
		int coefficient = stoi(line.substr(0, line.find('x')));
		int index = stoi(line.substr(line.find('x') + 1, line.size() - 1));
		this->addTerm(Term(coefficient, index));
		outputFile.close();
	}catch (exception const& e) {
		cout << endl << "File read error" << endl;
	}
}

void Expression::parseFromFile(string& line) {
	while (line.find(' ') != string::npos) {
		string sTerm = line.substr(0, line.find(' '));
		int coefficient = stoi(sTerm.substr(0, sTerm.find('x')));
		int index = stoi(sTerm.substr(sTerm.find('x') + 1, sTerm.size() - 1));
		line = line.substr(line.find(' ') + 1, line.size() - 1);

		this->addTerm(Term(coefficient, index));
	}
}

Term Expression::generateTerm(const vector<int>& yValues) {
	vector<int> diffSet, prevSet;
	prevSet = yValues;
	int depth = 0;
	while (prevSet[0] != prevSet[1]) {
		depth++;
		diffSet.clear();
		for (int i = 0; i < prevSet.size() - 1; i++) {
			diffSet.push_back(prevSet[i + 1] - prevSet[i]);
		}
		prevSet.clear();
		prevSet = diffSet;
	}
	if(depth!=0)return Term(integrateValue(prevSet[0], depth), depth);
	return Term(prevSet[0], depth);
}

int Expression::integrateValue(int y, int depth) {
	for (int i = 1; i <= depth; i++) y /= i;

	return y;
}

bool Expression::validate() {
	if (terms.size() > 4) return false;
	for (int i = 0; i < terms.size(); i++) {
		if (terms[i].index == 0) {
			if (terms[i].coefficient > 1000 || terms[i].coefficient < -1000) return false;
		}
		else {
			if (terms[i].coefficient > 9 || terms[i].coefficient < -9) return false;
			if (terms[i].index > 4 || terms[i].index < 0) return false;
		}
	} return true;
}

void Expression::generateExpression(const vector<int>& yValues) {
	terms.clear();
	vector<int> adjustedValues = yValues;
	int startX = 0;
	bool valid = false;
	while (!valid && startX < 100) {
		this->addTerm(generateTerm(yValues));
		generateTerms(adjustedValues, yValues, startX);
		valid = validate();
		if (!valid) rewrite(); valid = validate();
		if(!valid){
			startX++;
			adjustedValues = yValues;
			terms.clear();
		}
	}
}

void Expression::generateTerms(vector<int>& adjust, const vector<int>& yValues, const int startX) {
	while (adjust[0] != 0 || adjust[1] != 0) {
		int x = startX;
		for (int i = 0; i < adjust.size(); i++) {
			adjust[i] = yValues[i] - this->calculateForX(x);
			x++;
		}
		this->printExpression();
		this->addTerm(generateTerm(adjust));
	}
}

void Expression::rewrite() {
	int i = 0, spareTerms = 4 - terms.size();
	while (spareTerms > 0 && i < terms.size()) {
		if (terms[i].index == 0) {
			rewriteForConstraint(1000, &spareTerms, &i);
		}
		else if (terms[i].index != 0) {
			rewriteForConstraint(9, &spareTerms, &i);
		}
	}
}

void Expression::rewriteForConstraint(int constrain, int* spareTerms, int* i) {
	if (terms[*i].coefficient > constrain) {
		this->addTerm(Term(constrain, terms[*i].index));
		terms[*i].coefficient -= constrain;
		*spareTerms -= 1;
	}
	else if (terms[*i].coefficient < -constrain) {
		this->addTerm(Term(-constrain, terms[*i].index));
		terms[*i].coefficient += constrain;
		*spareTerms -= 1;
	}
	else {
		*i += 1;
	}
}
