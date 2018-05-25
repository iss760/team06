# 2048.c

> Console version of the 2048 game in C language

![](screen.jpg)

## Gameplay

### 규칙

1. 게임을 시작하면 4x4 게임판에 2개의 2또는 4의 숫자 블록이 랜덤으로 배치되어있다.
2. 방향기를 사용해 모든 블록을 위, 아래, 왼쪽, 오른쪽으로 밀수 있다.
3. 블록을 밀때 이동하는 방향에 같은 숫자 블록이 있을 경우 합쳐지고 빈 칸에 랜덤으로 2 또는 4의 숫자 블록이 나온다.
4. 만약 칸이 모두 채워지고, 밀어도 합칠수 없으면 게임이 종료된다.

### 애니메이션 변경

게임 실행 도중 a키를 불러  블록들이 움직일때 애니메이션을 바꿀 수 있다.

## Requirements
- GNU GCC Compiler

gcc compiler 다운로드&실행방법

### 1)다운로드

window전용

https://sourceforge.net/projects/mingw/
사이트 내에 들어가서 설치를 하게된댜.
<만약 다른OS를 사용하고 있다면 사이트 냉서 OS선택부분에 자신의 OS선택후 다운로드를 진행한다.>
-> 설치경로를 기억하여 [제어판]-[시스템]-[고급시스템 설정]-[환경변수]-시스템변수에 설치경로를 추가해 준다.
-> 설치관리자로 설치가 진행되는데 패키지 전부가 아닌 일부 패키지 다운이 가능하다.

### 2)설치 확인

cmd창에서 gcc -v 를 입력해 보면 설치여부와 버전확인이 가능하다.

### 3)실행 방법

gcc compiler를 설치한 경로로 이동후 실행
cmd창에gcc -o (새로 만들 실행파일의 경로) (컴파일 할 소스파일) 입력
ex) gcc -o C:\Users\사용자이름\Desktop\test.exe C:\Users\사용자이름\Desktop\main.c(지정한 위치에 실행파일이 생성된다.)

+ gcc compiler 관련 명령어

- gcc 파일명: default로 out파일이 생성된다.
- gcc -c 파일명: 오브젝트파일이 생성된다.
- gcc -c 오브젝트파일명 -> gcc -o 실행파일명: 실행파일이 생성된다.
    (= gcc -o 실행파일파일명)
    
 다운로드 및 실행 관련 도움 사이트 링크 : http://goproprada.tistory.com/387
