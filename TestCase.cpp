/*
! Test case format
	- n : natural numbers (1, 2, 3, ...)

TestCase Start [n : option, strongly recommended]
<Test case>
TestCase End
Answer Start
<Answer>
Answer End
*/
#include "TestCase.h"
#include "MyTimer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

auto originCin = cin.rdbuf();
auto originCout = cout.rdbuf();
MyTimer timer;

void runTest(void (*solve)(), string tcFileName) {
	ifstream tcIn(tcFileName);
	stringstream solveIn;
	stringstream solveOut;
	if (!tcIn.is_open()) {
		cout << "Error : Test case file not open.\n"
			<< "FileName : " << tcFileName << '\n';
		throw "test case file not open";
	}
	string tmp;
	int curTCIdx = 0;
	vector<int> ac, wa;
	while (!tcIn.eof()) {
		++curTCIdx;
		getline(tcIn, tmp);
		if (!tmp.starts_with("TestCase Start")) throw "Wrong format.\n[TestCase Start] should come before <Test case>.\n";
		solveIn = stringstream();
		solveOut = stringstream();

		// Read TestCase
		cout << "Running case, " << curTCIdx << "\n";
		//cout << "TestCase Start [" << curTCIdx << "]\n";
		getline(tcIn, tmp);
		do {
			solveIn << tmp << '\n';
			getline(tcIn, tmp);
		} while (!tmp.starts_with("TestCase End"));
		//cout << "TestCase End [" << curTCIdx << "]\n";

		// Read Answer
		string answer;
		getline(tcIn, tmp);
		if (!tmp.starts_with("Answer Start")) throw "Wrong format.\n[Answer Start] should come before <Answer>.\n";

		//cout << "Answer Start [" << curTCIdx << "]\n";
		getline(tcIn, tmp);
		do {
			answer += tmp + '\n';
			getline(tcIn, tmp);
		} while (!tmp.starts_with("Answer End"));
		//cout << "Answer End [" << curTCIdx << "]\n";

		// Run solve function
		cin.set_rdbuf(solveIn.rdbuf());
		cout.set_rdbuf(solveOut.rdbuf());
		// TODO : Add timer, count solve() running time.
		timer.start();
		solve();
		long long solveTime = timer.stop();
		cin.set_rdbuf(originCin);
		cout.set_rdbuf(originCout);
		string solveResult = solveOut.str();

		if (!solveResult.ends_with('\n') && solveResult.length() + 1 == answer.length()) {
			solveResult += '\n';
		}
		if (solveResult == answer) {
			cout << "AC, " << solveTime << "[ms]\n";
			ac.push_back(curTCIdx);
		}
		else {
			cout << "WA, " << solveTime << "[ms]\n";
			cout << "[res]\n" << solveResult << '\n';
			cout << "[ans]\n" << answer << '\n';
			wa.push_back(curTCIdx);
		}
	}
	if (ac.size()) {
		cout << "Right test cases : " << ac.size() << '\n';
		for (auto tc : ac) {
			cout << tc << ' ';
		}
		cout << '\n';
	}
	if (wa.size()) {
		cout << "Wrong test cases" << wa.size() << '\n';
		for (auto tc : wa) {
			cout << tc << ' ';
		}
		cout << '\n';
	}
}