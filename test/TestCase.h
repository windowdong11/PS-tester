#pragma once
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
enum class TestResult;
TestResult runTest(void (*solve)(), void (*initGlobal)(), const std::string &fileName);
void runTests(void (*solve)(), void (*initGlobal)(), const std::vector<std::string> &fileNames);
std::vector<std::string> generate_TCNames(const int tcCnt, const std::string start = "tc", const std::string end = "", const std::string ext = ".txt");
void testExample();