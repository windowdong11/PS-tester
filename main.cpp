#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include "test/TestCase.h"
#endif
using namespace std;
int n;
vector<int> nums;
int operators[4];
int ansmax, ansmin;
int result;

void back(int k){
  if(k == n - 1){
    ansmax = max(ansmax, result);
    ansmin = min(ansmin, result);
    return;
  }
  for(int i = 0; i < 4; ++i){
    if(operators[i]){
      int prev = result;
      switch(i){
        case 0:
          result += nums[k + 1];
          break;
        case 1:
          result -= nums[k + 1];
          break;
        case 2:
          result *= nums[k + 1];
          break;
        case 3:
          result /= nums[k + 1];
          break;
      }
      --operators[i];
      back(k + 1);
      ++operators[i];
      result = prev;
    }
  }
}

void solve(){
  ansmax = -1000000000;
  ansmin = 1000000000;
  cin >> n;
  nums = vector<int>(n);
  for(int i = 0; i < n; ++i)
    cin >> nums[i];
  for(int i = 0; i < 4; ++i)
    cin >> operators[i];
  result = nums[0];
  back(0);
  cout << ansmax << '\n' << ansmin;
}


int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef ONLINE_JUDGE
  runTests(solve, {"tc1.txt", "tc2.txt", "tc3.txt"});
  #else
  solve();
  #endif
  return 0;
}