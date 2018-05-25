# 2048.c

> Console version of the 2048 game in C language

![](screen.jpg)

### Gameplay
- Like in the initial game, use your arrow keys to move the tiles. When two tiles with the same number touch, they merge into one.
- You can also change animation of the moving cells by pressing the `a` key during the game.

### Requirements
- GNU GCC Compiler

gcc compiler 다운로드&실행방법

1)다운로드

window전용

https://sourceforge.net/projects/mingw/
사이트 내에 들어가서 설치를 하게된댜.
<만약 다른OS를 사용하고 있다면 사이트 냉서 OS선택부분에 자신의 OS선택후 다운로드를 진행한다.>
->설치경로를 기억하여 [제어판]-[시스템]-[고급시스템 설정]-[환경변수]-시스템변수에 설치경로를 추가해 준다.
->설치관리자로 설치가 진행되는데 패키지 전부가 아닌 일부 패키지 다운이 가능하다.

2)설치 확인

cmd창에서 gcc -v 를 입력해 보면 설치여부와 버전확인이 가능하다.

3)실행 방법

gcc compiler를 설치한 경로로 이동후 실행
cmd창에gcc -o (새로 만들 실행파일의 경로) (컴파일 할 소스파일) 입력
ex) gcc -o C:\Users\사용자이름\Desktop\test.exe C:\Users\사용자이름\Desktop\main.c(지정한 위치에 실행파일이 생성된다.)

++gcc compiler 관련 명령어

-gcc 파일명: default로 out파일이 생성된다.
-gcc -c 파일명: 오브젝트파일이 생성된다.
-gcc -c 오브젝트파일명 -> gcc -o 실행파일명: 실행파일이 생성된다.
    (= gcc -o 실행파일파일명)
