/*
PS_Tester : https://github.com/windowdong11/PS-tester
(TestCase)
*/
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
  #include "test/TestCase.h"
  #define TC_GEN
  #ifndef TC_GEN
    #define ONLINE_JUDGE
  #endif
#endif
using namespace std;

// ! ---------- 여기부터는 tc만들기 위한 
// TODO : 템플릿화 하기, 파일분리
#ifdef TC_GEN
class intRandom {
  random_device rd;
  mt19937 rdengine;
  map<pair<int,int>, uniform_int_distribution<int>> dis;
	public:
	intRandom(): rdengine(rd()){}
	int operator() (const int minval, const int maxval){
    if(dis.find({minval, maxval}) == dis.end()){
      // add new uniform_int_distribution
      dis[{minval, maxval}] = uniform_int_distribution<int>(minval, maxval);
    }
    return dis[{minval, maxval}](rdengine);
	}
}i_rand;

namespace GEN_TC {
  //global variables here
  int a, b;
  void InitGlobal_AC(){
    // Initialize global variables for solve_AC().
  }

  void solve_AC() {
    InitGlobal_AC();
    // Write AC code here.
    cin >> a >> b;
    cout << a + b;
  }
}

void gen_tc(){
  // testcase generator
  cout << i_rand(0, 100) << i_rand(0, 100);
}


#endif

// ! ---------- 여기부터는 문제풀이용 solve 코드

void initGlobal(){
  //Initialize global varibles for solve().
}

void solve(){
  //Write solving code.
  int a, b;
  cin >> a >> b;
  int s = a + b;
  cout << s;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  #ifdef TC_GEN
  gen_tc_files(gen_tc, GEN_TC::solve_AC, generate_TCNames(1, 20));
  runTests(solve, initGlobal, generate_TCNames(1, 20));
  #else
  #ifdef ONLINE_JUDGE
  solve();
  #else
  runTests(solve, initGlobal, generate_TCNames(1, 20));
  #endif
  #endif
  return 0;
}