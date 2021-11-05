#pragma once
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
enum class TestResult;
TestResult runTest(void (*solve)(), const std::string &fileName);
void runTests(void (*solve)(), const std::vector<std::string> &fileNames);
void testExample();