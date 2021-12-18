#include "TestCase.h"
#include <filesystem>
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

void trim_end(string &str)
{
	str.erase(
			find_if(str.rbegin(), str.rend(),
							[](unsigned char c)
							{ return !isspace(c); })
					.base(),
			str.end());
}

stringstream readTestCase(ifstream &in)
{
	stringstream testcase;
	string line;
	while (!(line == "answer" || in.eof()))
	{
		getline(in, line);
		trim_end(line);
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
		trim_end(line);
		answer << line + '\n';
	}
	return answer;
}

// trim each line and add '\n'
string trim_each_line_add_linebreak(stringstream& s){
	string result;
	while(!s.eof()){
		string line;
		getline(s, line);
		trim_end(line);
		result += line + '\n';
	}
	trim_end(result);
	return result;
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

TestResult runTest(void (*solve)(), void (*initGlobal)(), const string &fileName)
{
	cout << fileName << " : ";
	// Read test case, answer
	ifstream in(fileName);
	if (in.fail())
	{
		cerr << "Failed to open file: " << fileName << endl;
		return TestResult::TC_ERROR;
	}
	stringstream testCase = readTestCase(in);
	if (in.eof())
	{
		cout << "[PS_Tester Error] Seperator 'answer' does not exist in file : " + fileName + '\n';
		cout << "Testcase : \n" << testCase.str() << '\n';
		return TestResult::TC_ERROR;
	}
	string answer = readAnswer(in).str();
	trim_end(answer);
	in.close();
	// init global variables
	initGlobal();
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
	string solveResult = trim_each_line_add_linebreak(solveCout);
	// Compare result
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

void runTests(void (*solve)(), void (*initGlobal)(), const vector<string> &fileNames)
{
	vector<string> failed;
	for (auto &fileName : fileNames)
	{
		TestResult result = runTest(solve, initGlobal, fileName);
		if (result != TestResult::AC)
			failed.push_back(fileName);
	}
	cout << "Passed : " << (fileNames.size() - failed.size()) << '\n';
	cout << "Failed : " << failed.size() << '\n';
	for (auto &fileName : failed)
		cout << fileName << '\n';
}

string int_to_string(int num)
{
	char c[] = "0123456789";
	string s;
	while (num)
	{
		s += c[num % 10];
		num /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}

// generate testcase file name
// (when only tcCnt given) default output => "tc1.txt"
vector<string> generate_TCNames(const int tcCntStart, const int tcCntEnd, const string start, const string end, const string ext)
{
	vector<string> f;
	for (int i = tcCntStart; i <= tcCntEnd; ++i)
		f.push_back(start + int_to_string(i) + end + ext);
	return f;
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
	runTests(solveExample, []() {}, {"test/example/tc1.txt", "test/example/tc2.txt"});
}

// ! ---------- Generator ---------- !

void gen_tc_file(void (*tc_generator)(), void (*solve)(), const string filename, bool (*regen)(stringstream)){
	// open
	stringstream content;
	filesystem::path p = filesystem::current_path() / filename;
	unsigned long long gencnt = 0;
	cout << "Generating TC file : " << filename << '\n';
	do
	{
		content = {};
		if(gencnt++) {
			cout << "Regen[trying " << gencnt << "times] : " << filename << '\n';
		}
		ofstream out(p);
		if(!out.is_open()){
			cout << "(err1) Error opening file : " << filename << '\n';
			return;
		}
		// generate tc
		auto originCout = cout.rdbuf();
		cout.rdbuf(content.rdbuf());
		tc_generator();
		// solve tc
		content << "\nanswer\n";
		auto originCin = cin.rdbuf();
		cin.rdbuf(content.rdbuf());
		solve();
		cin.rdbuf(originCin);
		cout.rdbuf(originCout);
		// regenerate
		// write answer to file
		out << content.str();
		out.close();
	} while (regen(stringstream(content.str())));
}

void gen_tc_files(void (*tc_generator)(), void (*solve)(), vector<string> tc_filenames, bool (*regen)(stringstream)){
	for(auto filename: tc_filenames)
		gen_tc_file(tc_generator, solve, filename, regen);
}