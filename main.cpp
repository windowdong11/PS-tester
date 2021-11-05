#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "test/TestCase.h"
#endif
using namespace std;

void solve(){
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef ONLINE_JUDGE
  int tcCnt = 7;// set number of test cases
  runTests(solve, [&]() -> vector<string> { // generate testcase file name, ex) "tc1.txt"
    vector<string> f;
    for(int i = 1; i <= tcCnt; ++i)
      f.push_back(
        "tc"
        + [](int num) -> string // int to string
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
          }(i)
        + ".txt");
    return f;
  }());
  #else
  solve();
  #endif
  return 0;
}