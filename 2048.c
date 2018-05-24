#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

// Window's size
#define WW 40
#define WH 11

// Keyboard ASCII
#define UP 72
#define RIGHT 77
#define DOWN 80
#define LEFT 75
#define ENTER 13
#define ESC 27

// Global vals
bool anim;
char emptyCell[5];
char cell[4][4][5];
unsigned short score;
bool gameEnded;

// Prototypes
void gotoXY(unsigned short,unsigned short);
void setColor(char*);
void center(char*,unsigned short);
void init();
void welcomeView();
void endView();
void display();
bool isEmpty(char*);
void addRandomValue(bool);
short mergeable(short,short);
short mergeAndMove(char*,char*,bool);
unsigned short getAction();
bool doProcess(unsigned short);


void gotoXY(unsigned short x,unsigned short y){
	/*x, y값으로 커서의 위치를 설정하는 함수*/
 HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
 COORD position={x,y}; //좌표값 저장
 SetConsoleCursorPosition(handle,position); //콘설 커서를 좌표에 이동시킨다
}
void setColor(char *cell1){
 unsigned short cColor; //cColor의 16비트중 뒤의 8비트가 색상지정관련비트
 switch(atoi(cell1)){     //(글자색-앞 4비트,배경색-뒤 4비트)
  case 2: cColor=207; break;  
  case 4: cColor=224; break;  //보기쉽도록 색상변경
  case 8: cColor=160; break;
  case 16: cColor=179; break;
  case 32: cColor=159; break;
  case 64: cColor=223; break;
  case 128: cColor=143; break;
  case 256: cColor=15; break;
  case 512: cColor=207; break;
  case 1024: cColor=239; break;
  case 2048: cColor=175; break;
  case 4096: cColor=191; break;
  default: cColor=7; break;
 }
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cColor);
}
//center함수
//str을 중앙으로 출력을 위함
void center(char *str, unsigned short y){ 
 gotoXY((WW-strlen(str))/2,y);
 printf("%s",str);
}



void init(){
 // Game coded to learn C
 SetConsoleTitle("2048 :: YoannBoyer.com");

 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SMALL_RECT windowSize = {0,0,WW,WH}; //가로는 0 ~ WW(40), 세로는 0 ~ WH(11)으로 윈도우 사이즈 초기화
 SetConsoleWindowInfo(handle,1,&windowSize); //콘솔화면의 크기와 위치 설정

 CONSOLE_SCREEN_BUFFER_INFO info;
 GetConsoleScreenBufferInfo(handle,&info); //콘솔 스크린 버퍼 정보 가져오기
 int width_size = info.srWindow.Right - info.srWindow.Left + 1;
 int height_size = info.srWindow.Bottom - info.srWindow.Top + 1;

 COORD new_size = {width_size, height_size}; //콘솔화면의 좌표계 설정
 SetConsoleScreenBufferSize(handle,new_size); //콘솔 스크린 버퍼 사이즈를 new_size로 변경
 srand(time(NULL));

 strcpy(emptyCell,"    "); //emptyCell을 빈칸으로지정

 anim = false;
 gameEnded = false;

 unsigned short x,y;
 //모든 셀을 빈칸으로 초기화
 for(x=0; x<4; x++){
  for(y=0; y<4; y++){
   strcpy(cell[x][y], emptyCell);
  }
 }

 score = 0;

 addRandomValue(true);
 addRandomValue(true);
}


void welcomeView(){//처음시작화면함수
 center("2048",2);//2048 윗부분에 출력
 center("Press Enter to start",7);//가운데에 출력
 center("",WH);

 while(getch() != ENTER){ //enter키 입력 받았는지 확인하는 반복문
 }

 system("cls");//화면 지우기
}
void endView(){
 system("cls");
 gameEnded = true;

 center("Press Enter to restart", 10);
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
 center("You lost !", 6);
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
 center("Esc to exit", 11);
 setColor("");

 display();

 gotoXY(WW,WH);

 bool checkAction = true;
 unsigned short ch;
 while(checkAction){
  ch = getch();
  if (ch == ENTER){
   checkAction = false;
   system("cls");
   init();
  } else if (ch == ESC){
   exit(0);
  }
 }
}
//display함수
//칸에따른 경계선과 셀에 할당된 값에 따라 글자, 배경색 정해짐
//각 셀의 위치와 색이 값에 맞는 출력
void display(){
 unsigned short x,y;
 if (!gameEnded){
  for (x=0; x<4; x++){
   gotoXY((WW-20)/2,5+x);
   for(y = 0; y < 4; y++){
    printf("|");
    setColor(cell[x][y]);
    printf("%s", cell[x][y]);
    setColor("");
   }
   printf("|");
  }
 }

 char str[13] = "Score : ";
 char sc[5];
 sprintf(sc,"%d",score);
 strcat(str,sc);
 center(str,2);

 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
 gotoXY(WW,0);      //오른쪽위로 출력위한 커서이동
 printf(" ");
 gotoXY(WW-9,0);    
 printf("Anim : ");
 printf(anim == true ? "ON" : "OFF");
 setColor("");

 center("",WH);
}


bool isEmpty(char *cell1){
	/*셀을 받아 그 셀이 비어있으면 false를 아니면 true를 반환*/
 bool check;
 check = strcmp(cell1, emptyCell);
 if(check == true)
	 return false;
 else
	 return true;
}

void addRandomValue(bool add){
	/*빈 셀의 임의의 위치에 2, 4중 하나의 수를 넣는 함수*/
 unsigned short x,y;

 if (add){
	 //빈 셀을 찾기 위한 반복문
  do{
   x = rand()%4;
   y = rand()%4;
  } while (!isEmpty(cell[x][y]));

  char str[5];
  int randInRange = (rand()%2+1)*2;

  sprintf(str,"%4d",randInRange); //2, 4중 임의의 숫자를 str에 넣
  strcpy(cell[x][y], str);

  bool end = true;
  bool fullBoard = true;
  for(x=0; x<4; x++){
   for(y=0; y<4; y++){
    if (isEmpty(cell[x][y])){ //셀들 중 비어있는 셀이 있을 경우 fullBoard를 false로 바꿈
     fullBoard = false;
    }
    if (mergeable(x,y) > 0){ //블록이 합쳐질 수 있을 경우 end를 false로 바꿈
     end = false;
    }
   }
  }
  if (end && fullBoard){ //블록이 더 이상 합쳐질 수 없고 모든 셀들이 꽉 찼을 경우 endView() 함수 호출
   endView();
  }
 }
}

short mergeable(short r, short c){

	unsigned short i = 0;			// merge가 가능한 경우의 수를 담아 놓는 변수


	if (c > -1) {

		if (!isEmpty(cell[0][c])) {

			if (!strcmp(cell[0][c], cell[1][c])) {
				i++;		
			}		// 1행과의 결합

			else if (!strcmp(cell[0][c], cell[2][c]) && isEmpty(cell[1][c])) {
				i++;
			}		// 2행과의 결합

			else if (!strcmp(cell[0][c], cell[3][c]) && isEmpty(cell[1][c]) && isEmpty(cell[2][c])) {
				i++;
			}		// 3행과의 결합

		}
		// (0,c)칸의 블록이 존재하는 경우에 1행,2행,3행과 결합이 가능한지를 판단	

		if (!isEmpty(cell[1][c]) && i == 0) {

			if (!strcmp(cell[1][c], cell[2][c])) {
				i++;
			}		// 2행과의 결합

			else if (!strcmp(cell[1][c], cell[3][c]) && isEmpty(cell[2][c])) {
				i++;
			}		// 3행과의 결합

		}
		// (1,c)칸의 블록이 존재하고 위에 조건문에서 결합 가능한 곳을 찾지못한 경우에 (1,c)의 블록이 2행, 3행과 결합이 가능한지를 판단	

		if (!strcmp(cell[2][c], cell[3][c]) && !isEmpty(cell[2][c])) {
			i++;
		}
		// 게임판의 (2,c)위치에 블록이 존재하고 3행과 덧셈이 가능한 경우를 체크

	}
	// 게임판의 c열에 세로로 같은 값이  있는지 확인한 뒤 결합 가능여부를 판단											



	if (r > -1) {

		if (!isEmpty(cell[r][0])) {

			if (!strcmp(cell[r][0], cell[r][1])) {
				i++;
			}		// 1열과의 결합

			else if (!strcmp(cell[r][0], cell[r][2]) && isEmpty(cell[r][1])) {
				i++;
			}		// 2열과의 결합

			else if (!strcmp(cell[r][0], cell[r][3]) && isEmpty(cell[r][1]) && isEmpty(cell[r][2])) {
				i++;
			}		// 3열과의 결합

		}
		// (r,0)칸의 블록이 존재하는 경우에 1열,2열,3열과 결합이 가능한지를 판단

		if (!isEmpty(cell[r][1]) && i == 0) {

			if (!strcmp(cell[r][1], cell[r][2])) {
				i++;
			}		// 2열과의 결합

			else if (!strcmp(cell[r][1], cell[r][3]) && isEmpty(cell[r][2])) {
				i++;
			}		// 3열과의 결합

		}
		// (r,1)칸의 블록이 존재하고 위에 조건문에서 결합 가능한 곳을 찾지못한 경우에 (r,1)의 블록이 2열, 3열과 결합이 가능한지를 판단

		if (!strcmp(cell[r][2], cell[r][3]) && !isEmpty(cell[r][2])) {
			i++;
		}
		// 게임판의 (r,2)위치에 블록이 존재하고 3열과 결합이 가능한 경우를 체크

	}
	// 게임판의 c열에 세로로 같은 값이  있는지 확인한 뒤 결합 가능여부를 판단		


	return i;				// 결합 가능한 경우의 수를 저장한 값을 return해준다.
}



short mergeAndMove(char *cell1, char *cell2, bool dontMerge) {

	if (anim) {
		clock_t wait = clock() + 0.002*CLOCKS_PER_SEC;
		while (clock()<wait) {}
		display();
	}
	// 애니매이션 효과로 변화

	if (isEmpty(cell2)) {		//Nothing

		return -1;

	}
	// 함수에서 메인 블록 열할을 하는 cell2의 블록이 비어있어서 움직이지도 못하고 더할 수 도 없는 상황


	if (isEmpty(cell1)) {  //Move	

		strcpy(cell1, cell2);
		strcpy(cell2, emptyCell);
		return 0;

	}
	//cell2가 존재하고 cell1이 비어있는 경우 cell의 값을 비어있는 블록 cell1의 위치로 복사하고 기존 cell2위치는 비어있는 블록으로 전환 

	else if (!strcmp(cell1, cell2) && !dontMerge) { //Merge  dontMerge : 이미 merge가 수행됬는지 여부를 확인

		strcpy(cell2, emptyCell);
		char str[5];
		sprintf(str, "%4d", atoi(cell1) * 2);				//atoi()는 C형식 문자열을 정수로 변환하여 변환된 값을 return 시켜준다.
		strcpy(cell1, str);
		score += atoi(cell1);							//더해서 만들어진 값 만큼 점수를 더해준다.
		return 1;

	}
	// cell1, cell2가 모두 존재하고 dontMerge가 true값일 경우 cell2에 값을 빈셀로 바꾸고 cell1의 값을 두 배로 증가시켜 화면에 출력

	else {

		return -1;

	}
	//위 사항들 외에 경우는 작업을 수행할 수 없다고 판단하여 -1을 return

}

unsigned short getAction(){
 unsigned short ch;
 /* 무한루프로 키보드의 입력을 받는다. */
 do{
  ch = getch();			// 키보드 입력을 받을 변수
  /* 방향키를 입력받을때 */
  if (ch == 0xE0){
   switch(getch()){
    case UP: return 0; break;		// Up입력
    case RIGHT: return 1; break;	// Right입력
    case DOWN: return 2; break;		// Down 입력
    case LEFT: return 3; break;		// Left 입력
   }
  } 
  /* a키를 입력 받을때 */
  else if (ch == 97){
   anim = !anim;	// Animation가능 On/Off
   display();
  }
  Sleep(10);		// 키보드입력 대기시간
 } while(1);
}

bool doProcess(unsigned short direction){
 short x,y,mergeStatus,nbMerge;		// 좌표, merge상태, merge가능 개수를 확인 하는 변수 선언
 bool redo;				// 다시 merge할지를 확인하는 변수 선언
 bool done = false, merged = false;	// 동작했는지, merge되었는지 확인하는 변수 선언

/* direction(방향키)값에 따라 동작을 구현 */
 switch (direction){
  /* Up방향키 입력시 */
  case 0:
  /* 가로축 순환 */	  
  for(y=0; y<4; y++){
   /* 초기 변수 설정 */
   redo = true;
   merged = false;
   nbMerge = mergeable(-1,y);
   /* merge를 반복 */
   while(redo){
    nbMerge--;		// merge 가능 개수 감소
    redo = false;
    /* 세로축 순환 */
    for(x=0; x<3; x++){
     mergeStatus = mergeAndMove(cell[x][y],cell[x+1][y], merged);	// merge 실행
     if (mergeStatus > -1){done = true;}				// 작동확인
     if (mergeStatus == 0){redo = true;}				// merge 반복을 위한 True
     if (mergeStatus == 1){merged = true;}				// merge 완료확인
    }
    /* merge 할게 남았을때 */
    if (nbMerge > 0){
     redo=true;		// while문 반복을 위한 True
     merged = false;	// merge가 끝나지 않았다는 False
    }
   }
  }
  break;
  
  /* Right방향키 입력시 */
  case 1:
  /* 세로축 순환 */
  for(x=0; x<4; x++){
   /* 초기 변수 설정 */
   redo = true;
   merged = false;
   nbMerge = mergeable(x,-1);
   /* merge를 반복 */
   while(redo){
    nbMerge--;		// merge 가능 개수 감소
    redo = false;
    /* 가로축 순환 */
    for(y=3; y>0; y--){
     mergeStatus = mergeAndMove(cell[x][y],cell[x][y-1], merged);	// merge 실행
     if (mergeStatus > -1){done = true;}				// 작동확인
     if (mergeStatus == 0){redo = true;}				// merge 반복을 위한 True
     if (mergeStatus == 1){merged = true;}				// merge 완료 확인
    }
    /* merge할게 남았을 때 */
    if (nbMerge > 0){
     redo=true;		// while문 반복을 위한 True
     merged = false;	// merge가 끝나지 않았다는 False
    }
   }
  }
  break;

  /* Down방향키 입력시 */
  case 2:
  /* 가로축 순환 */
  for(y=0; y<4; y++){
   /* 초기 변수 설정 */
   redo = true;
   merged = false;
   nbMerge = mergeable(-1,y);
   /* merge를 반복 */
   while(redo){
    nbMerge--;		// merge가능 개수 감소
    redo = false;
    /* 세로축 순환 */
    for(x = 3; x>0; x--){
     mergeStatus = mergeAndMove(cell[x][y],cell[x-1][y], merged);	// merge 실행
     if (mergeStatus > -1){done = true;}				// 작동확인
     if (mergeStatus == 0){redo = true;}				// merge 반복을 위한 True
     if (mergeStatus == 1){merged = true;}				// merge 완료 확인
    }
    /* merge 할게 남았을때 */
    if (nbMerge > 0){
     redo=true;		// while문 반복을 위한 True
     merged = false;	// merge가 끝나지 않았다는 False
    }
   }
  }
  break;

  /* Left 방향키 입력시*/
  case 3:
  /* 세로축 순환 */
  for(x=0; x<4; x++){
   /* 초기 변수 설정 */
   redo = true;
   merged = false;
   nbMerge = mergeable(x,-1);
   /* merge를 반복 */
   while(redo){	
    nbMerge--;		// merge가능 개수 감소
    redo = false;
    /* 가로축 순환 */
    for(y=0; y < 3; y++){
     mergeStatus = mergeAndMove(cell[x][y],cell[x][y+1], merged);	// merge 실행
     if (mergeStatus > -1){done = true;}				// 작동확인
     if (mergeStatus == 0){redo = true;}				// merge 반복을 위한 True
     if (mergeStatus == 1){merged = true;}				// merge 완료 확인
    }
    /* merge 할게 남았을 때 */
    if (nbMerge > 0){
     redo=true;		// while문 반복을 위한 True
     merged = false;	// merge가 끝나지 않았다는 False
    }
   }
  }
  break;
 }

 return done;	// 동작여부 반환
}


int main(){

 init(); //시작 및 초기화 함수 호출

 welcomeView(); //시작 화면 호출

 while(1){
  display(); //화면 출력함수 호출
  addRandomValue(doProcess(getAction())); //셀에 임의의 숫자 대입
 }
 return 0;
}

