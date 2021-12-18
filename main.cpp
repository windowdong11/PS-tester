/*
PS_Tester : https://github.com/windowdong11/PS-tester
(TestCase)
*/
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
  #include "test/TestCase.h"
  #define TC_GEN
  #ifndef TC_GEN
    //#define ONLINE_JUDGE
  #endif
#endif
using namespace std;

// ! ---------- 여기부터는 tc만들기 위한 
// TODO : 템플릿화 하기, 파일분리
#ifdef TC_GEN
template<
  typename T,
  typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
class intRandom {
  random_device rd;
  mt19937 rdengine;
  map<pair<T,T>, uniform_int_distribution<T>> dis;
	public:
	intRandom(): rdengine(rd()){}
	T operator() (const T minval, const T maxval){
    if(dis.find({minval, maxval}) == dis.end()){
      // add new uniform_int_distribution
      dis[{minval, maxval}] = uniform_int_distribution<T>(minval, maxval);
    }
    return dis[{minval, maxval}](rdengine);
	}
};

intRandom<int> i_rand;
intRandom<long long> ll_rand;

void InitGlobal_AC(){
  // Initialize global variables for solve_AC().
}

void solve_AC() {
  InitGlobal_AC();
  // Write AC code here.
  //* Example : calculate sum of n numbers
  int n;
  cin >> n;
  int ans = 0;
  while(n--) {
    int t;
    cin >> t;
    ans += t;
  }
  cout << ans;
}

bool regen(stringstream ans){
  // regenerate testcase when regen() returns true
  //* Example : regenerate testcase when the answer is 0
  int s;
  ans >> s;
  if(s == 0) return true;
  return false;
}

void gen_tc(){
  // testcase generator
  //* Example: generate n numbers
  int n = i_rand(1, 1000);
  cout << n << '\n';
  while(n--)
    cout << i_rand(0, 1000) << ' ';
}
#endif

// ! ---------- 여기부터는 문제풀이용 solve 코드

void initGlobal(){
  //Initialize global varibles for solve().
}


void solve(){
  //Write solving code
  //* Example : Solving code.
  int n;
  int numbers[1000];
  cin >> n;
  for(int i = 0; i < n; ++i) cin >> numbers[i];
  int sum = 0;
  for(int i = 0; i < n; ++i) sum += numbers[i];
  cout << sum;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  #ifdef TC_GEN
  const int minidx = 1;
  const int tcCnt = 5;
  gen_tc_files(gen_tc, solve_AC, generate_TCNames(minidx, minidx + tcCnt - 1), regen);
  runTests(solve, initGlobal, generate_TCNames(minidx, minidx + tcCnt - 1));
  #else
  #ifdef ONLINE_JUDGE
  solve();
  #else
  runTests(solve, initGlobal, generate_TCNames(1, 1));
  #endif
  #endif
  return 0;
}