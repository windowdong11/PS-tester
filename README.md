# PS-tester
c++로 문제풀때, 예제(테스트케이스) 채점을 위한 환경  
예제를 여러 파일로 구성하고, 각 파일마다 채점, 실행시간 측정  
(실행시간은 근사치 정도로만 사용)  
m1 맥에서 사용하려고 만듬

## 도커 환경
ubuntu-21.04  
gcc 10.3.0

## 사용법(vscode)
```c++
#include "TestCase.cpp"
void solve(){...};
int main() {
  // 1. 다중 테스트케이스(파일) 테스트
  runTests(solve(), {"testfile1.txt", "testfile2.txt"});
  // 2. 단일 테스트케이스(파일) 테스트
  runTest(solve(), "testfile1.txt");
  return 0;
}
```
## 예제파일 양식 규칙
```
<Test case>
answer
<Answer>
```
<Test case> 자리에 테스트케이스  
"answer"로 분리  
<Answer> 자리에 정답  

## 주의사항
solve함수를 반복적으로 실행하기 때문에,  
사용하는 변수들을 전역변수로 선언하고,  
초기화가 필요한 변수들을 초기화 하지 않으면 한번 실행할 때와 다르게 오류가 발생할 수 있습니다.  
(TMI : runTest 버근줄 알고 한참고침)
