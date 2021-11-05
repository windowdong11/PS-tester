#include "TestCase.h"
using namespace std;

class MyTimer
{
private:
	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;

public:
	MyTimer() {}
	~MyTimer() {}

	void start()
	{
		begin = chrono::steady_clock::now();
	}
	long long stop()
	{
		end = chrono::steady_clock::now();
		return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	}
} timer;

stringstream readTestCase(ifstream &in)
{
	stringstream testcase;
	string line;
	while (!(line == "answer" || in.eof()))
	{
		getline(in, line);
		testcase << line + '\n';
	}
	return testcase;
}

stringstream readAnswer(ifstream &in)
{
	stringstream answer;
	string line;
	while (!in.eof())
	{
		getline(in, line);
		answer << line + '\n';
	}
	return answer;
}

void trim_end(string &str)
{
	str.erase(
			find_if(str.rbegin(), str.rend(),
							[](unsigned char c)
							{ return !isspace(c); })
					.base(),
			str.end());
}

enum class TestResult
{
	AC,
	WA,
	TLE,
	RE,
	MLE,
	CE,
	UNKNOWN,
	TC_ERROR
};

TestResult runTest(void (*solve)(), const string &fileName)
{
	// Read test case, answer
	ifstream in(fileName);
	if(in.fail())
	{
		cerr << "Failed to open file: " << fileName << endl;
		return TestResult::TC_ERROR;
	}
	stringstream testCase = readTestCase(in);
	if (cin.eof())
	{
		cout << "[PS_Tester Error] Seperator 'answer' does not exist in file : " + fileName + '\n';
		return TestResult::TC_ERROR;
	}
	string answer = readAnswer(in).str();
	trim_end(answer);
	in.close();
	// Run solve
	stringstream solveCout;
	auto originCin = cin.rdbuf(), originCout = cout.rdbuf();
	cin.rdbuf(testCase.rdbuf());
	cout.rdbuf(solveCout.rdbuf());
	timer.start();
	solve();
	long long solveTime = timer.stop();
	cin.rdbuf(originCin);
	cout.rdbuf(originCout);
	// Get result
	string solveResult = solveCout.str();
	trim_end(solveResult);
	// Compare result
	cout << (answer == solveResult ? "AC\n" : "WA\n");
	if (solveResult == answer)
	{
		cout << "AC, " << solveTime << "[ms]\n";
		return TestResult::AC;
	}
	else
	{
		cout << "WA, " << solveTime << "[ms]\n";
		cout << "[res]\n"
				 << solveResult << '\n';
		cout << "[ans]\n"
				 << answer << '\n';
		return TestResult::WA;
	}
}

void runTests(void (*solve)(), const vector<string> &fileNames)
{
	vector<string> passed, failed;
	for (auto &fileName : fileNames)
	{
		TestResult result = runTest(solve, fileName);
		if (result == TestResult::AC)
			passed.push_back(fileName);
		else
			failed.push_back(fileName);
	}
	cout << "Passed : " << passed.size() << '\n';
	for (auto &fileName : passed)
		cout << fileName << '\n';
	cout << "Failed : " << failed.size() << '\n';
	for (auto &fileName : failed)
		cout << fileName << '\n';
}

void solveExample()
{
	for (int i = 0; i < 2; ++i)
	{
		string line;
		getline(cin, line);
		if (line == "Test case line 1")
			cout << "Answer line 1\n";
		else if (line == "Test case line 2")
			cout << "Answer line 2\n";
	}
}

void testExample()
{
	runTests(solveExample, {"test/example/tc1.txt", "test/example/tc2.txt"});
}