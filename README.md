# PS-tester
c++로 문제풀때, 예제 쉽게 테스트 할 수 있게 해주는 라이브러리(?)

## 사용법
```c++
#include "TestCase.cpp"
void solve(){...};
int main() {
  // 1. 예제 파일 이름 기본값으로 실행
  runTest(solve()); // 예제 파일 이름 기본값은 "tc.txt"
  // 2. 파일이름 명시
  // runTest(solve(), "filename.txt"); // 또는 파일이름 명시
  return 0;
}
```
예제파일 양식 규칙을 따라서 예제파일을(기본이름: `tc.txt`) 작성하고 실행하면 된다!
**컴파일러 c++20이상을 지원해야 한다.**

## visual studio c++20 설정
프로젝트 > [프로젝트 이름] 속성 > c++언어 표준을 `ISO C++20표준 /stdc:c++20`으로 설정

## 출력 결과 예시
![image](https://user-images.githubusercontent.com/16981721/137499027-7e05fdfa-8e11-4f91-bdd8-0323ca295c96.png)  
![image](https://user-images.githubusercontent.com/16981721/137499231-a6d372b3-b90d-4894-b90f-53b9b1d9dfb4.png)  


## 예제파일 양식 규칙
```
TestCase Start
<Test case>
TestCase End
Answer Start
<Answer>
Answer End
```
1. 파일에서 첫번째 줄은 "TestCase Start"로 시작해야한다.  
2. "TestCase Start"로 시작하는 줄의 다음 줄부터 `입력 예제`를 작성해야한다.  
4. `입력 예제`가 끝나면, 다음 줄은 "TestCase End"로 시작해야한다.  
5. "TestCase End"로 시작하는 줄의 다음 줄은 "Answer Start"로 시작해야한다.  
6. "Answer Start"로 시작하는 줄의 다음 줄부터 `출력 예제`를 작성해야한다.  
7. `출력 예제`가 끝나면, 다음 줄은 "Answer End"로 시작해야한다.  
8. 파일에서 마지막 줄은 "Answer End"로 시작하는 줄로 끝나야한다.  

- ~로 시작해야한다 : 뒤에는 뭐가오든 상관없다.  
(따라서, n번째 예제라는 의미의 n을 써두면 예제를 작성하는데 편함)
- 또 오랫동안 ps안하다가 이거 또 만들지 말자

## 주의사항
solve함수를 반복적으로 실행하기 때문에,  
사용하는 변수들을 전역변수로 선언하고,  
초기화가 필요한 변수들을 초기화 하지 않으면 한번 실행할 때와 다르게 오류가 발생할 수 있습니다.  
(TMI : runTest 버근줄 알고 한참고침)
