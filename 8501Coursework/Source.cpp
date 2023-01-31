#include <iostream>
#include <vector>
#include <string>
#include "Term.h"
#include "Expression.h"
#include "OutputSet.h"

using namespace std;

vector<Term> parse(char, string);
vector<Term> inputTerms();
vector<int> inputOutputSet();
int option();
void displayOptions();
Term createTerm(string);

Expression expression;
OutputSet out;

int main() {
	return option();
}

void display() {
	cout << endl << "Expression: " << endl;
	expression.printExpression();
	cout << "Output Set: " << endl;
	out.printSet();
}

void displayOptions() {
	cout << endl << "=====================================" << endl;
	cout << "What do you want to do?" << endl;
	cout << endl << "1. Create expression" << endl;
	cout << endl << "2. Generate expression" << endl;
	cout << endl << "3. Save expression to file" << endl;
	cout << endl << "4. Read expression from file" << endl;
	cout << endl << "5. Create output set" << endl;
	cout << endl << "6. Generate output set" << endl;
	cout << endl << "7. Save output set to file" << endl;
	cout << endl << "8. Read output set from file and generate expression set to file" << endl;
	cout << endl << endl << "9. Exit" << endl << endl;
	display();
}

int option() {
	int choice;
	bool repeat =true;
	while (repeat) {
		displayOptions();
		cin >> choice;
		string input;
		switch (choice)
		{
		case 1:
			expression = Expression(inputTerms());
			break;
		case 2:
			cout << "Generating Expression....." << endl;
			expression.generateExpression(out.getValues());
			break;
		case 3:
			cout << "Saving to file....." << endl;
			cin >> input;
			expression.saveToFile(input);
			break;
		case 4:
			cout << "Loading from file....." << endl;
			cin >> input;
			expression.readFromFile(input);
			break;
		case 5:
			cout << "What is your output set?" << endl;
			out = OutputSet(inputOutputSet());
			break;
		case 6: {
			vector<int> intVec;
			int x1, x2;
			cout << "Between which x values do you want to generate (inclusive)" << endl << "x: ";
			cin >> x1;
			cin >> x2;
			x1 = (x1 > -1) ? x1 : 1;
			x2 = (x1 >= x2) ? x1 + 1 : x2;
			for (int i = x1; i < x2 + 1; i++) {
				intVec.push_back(expression.calculateForX(i));
			}
			out = OutputSet(intVec);
			break;
		}
		case 7:
			cout << "Saving output set....." << endl;
			cin >> input;
			out.saveToFile(input);
			break;
		case 8:
			cout << "Reading output set....." << endl;
			cin >> input;
			out = OutputSet(input);
			break;
		case 9:
			cout << "Exiting....." << endl;
			repeat = false;
			break;
		default:
			cout << "Invalid option Exiting....." << endl;
			repeat = false;
			break;
		}
	}
	return 0;
}

vector<Term> inputTerms() {
	vector<Term> terms;
	int termCount, coe, ind;
	cout << "How many terms?";
	cin >> termCount;
	termCount = (0 < termCount && 5 > termCount) ? termCount : 1;
	for (int i = 0; i < termCount; i++) {
		cout << endl << "coefficient of term " << i+1 << ':'<< endl;
		cin >> coe;
		cout << "index of term " << i+1 << ':' << endl;
		cin >> ind;
		terms.push_back(Term(coe, ind));
	}
	return terms;
}

vector<int> inputOutputSet() {
	vector<int> terms;
	int inCount;
	cout << "How many terms?";
	cin >> inCount;
	for (int i = 0; i < inCount; i++) {
		int in;
		cout << endl << "Value number " << i + 1 << ':' << endl;
		cin >> in;
		terms.push_back(in);
	}
	return terms;
}

vector<Term> parse(char delimiter, string input) {
	vector<Term> terms;
	while (input.find(delimiter) != string::npos) {
		string s = input.substr(0, input.find(delimiter));
		input = input.substr(input.find(delimiter)+1, input.size()-1);
		terms.push_back(createTerm(s));
	}
	terms.push_back(createTerm(input));

	for (int i = 0; i < terms.size(); i++) cout << "Term is: " << terms.at(i).coefficient << ' ' << terms.at(i).index << endl;
	return terms;
}

Term createTerm(string sTerm) {
	return Term(stoi(sTerm.substr(0, 2)),stoi(sTerm.substr(3, 3)));
}