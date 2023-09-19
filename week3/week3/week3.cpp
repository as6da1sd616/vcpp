#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <chrono> //시간관련함수 
#define ESC 27
#define ENTER 13
using namespace std; //c로 짰는데 크로노가  c++써야하길래 std:: 생략을 위한 이름사용 
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int main() {
	chrono::system_clock::time_point StartTime = chrono::system_clock::now();//시간 시작지점

	while (1) {

		int x, p = 0;
		printf("command>");
		int cnt = 0, cnt1 = 0, cnt2 = 0;//길이
		int adogen = 0;//아도겐
		int fuck = 0;//뻐큐
		int solyugen = 0;//소류겐

		while ((x = _getch()) != ESC) {

			/*printf("\n아도겐:%d", adogen);
			printf("\ncnt:%d", cnt);*/
			if (x != 224) {//방향키가 아닐때 
				p = x;
				printf("%c", p);
				if ((adogen == 1 && p != RIGHT) || (adogen == 2 && p != 97))//아도겐초기화
				{
					cnt = 0;
					adogen = 0;
				}
				if ((fuck == 1 && p != DOWN) || (fuck == 2 && p != RIGHT) || (fuck == 3 && p != 102))//뻐큐초기화
				{
					cnt1 = 0;
					fuck = 0;
				}
				if ((solyugen == 1 && p != DOWN) || (solyugen == 2 && p != RIGHT) || (solyugen == 3 && p != 97))//소류겐초기화
				{
					cnt2 = 0;
					solyugen = 0;
				}
			}
			else { ////방향키일때 
				p = _getch();
				if ((p == LEFT)) {//왼쪽
					printf("←");
				}
				if ((p == RIGHT)) {//오른쪽
					printf("→");
				}
				if ((p == UP)) {//위
					printf("↑");
				}
				if ((p == DOWN)) {//아래
					printf("↓");
				}

				if ((adogen == 1 && p != RIGHT) || (adogen == 2 && p != 97))//아도겐초기화
				{
					cnt = 0;
					adogen = 0;

				}
				if ((fuck == 1 && p != DOWN) || (fuck == 2 && p != RIGHT) || (fuck == 3 && p != 102))//뻐큐초기화
				{
					cnt1 = 0;
					fuck = 0;
				}
				if ((solyugen == 1 && p != UP) || (solyugen == 2 && p != RIGHT) || (solyugen == 3 && p != 97))//소류겐초기화
				{
					cnt2 = 0;
					solyugen = 0;
				}



				if ((p == DOWN)) {//아도겐1
					adogen++;
					cnt++;
					StartTime = chrono::system_clock::now();//시간 시작지점					
				}
				if ((p == RIGHT) && (cnt == 1)) {//아도겐2
					adogen++;
					cnt++;
				}
				////////////////////////////////////////////
				if ((p == RIGHT)) {//뻐큐1
					fuck++;
					cnt1++;
					StartTime = chrono::system_clock::now();//시간 시작지점
				}
				if ((p == DOWN) && (cnt1 == 1)) {//뻐큐2
					fuck++;
					cnt1++;
				}
				if ((p == RIGHT) && (cnt1 == 2)) {//뻐큐3
					fuck++;
					cnt1++;
				}
				////////////////////////////////////////////
				if ((p == RIGHT)) {//소류겐1
					solyugen++;
					cnt2++;
					StartTime = chrono::system_clock::now();//시간 시작지점
				}
				if ((p == UP) && (cnt2 == 1)) {//소류겐2
					solyugen++;
					cnt2++;
				}
				if ((p == RIGHT) && (cnt2 == 2)) {//소류겐3
					solyugen++;
					cnt2++;
				}




			}
			if ((p == 97) && (cnt == 2) && (adogen == 2)) {//아도겐3
				break;
			}
			if ((p == 102) && (cnt1 == 3) && (fuck == 3)) {//뻐큐4
				break;
			}
			if ((p == 97) && (cnt2 == 3) && (solyugen == 3)) {//소류겐4
				break;
			}

			int sum = 0;





		}
		chrono::system_clock::time_point EndTime = chrono::system_clock::now();//시간 끝나는지점 
		chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(EndTime - StartTime);//시간 저장
		if ((p == 97) && (cnt == 2) && (adogen == 2) && (mill.count() <= 300)) {//아도겐3출력
			printf("\n아도겐! =o \n");
			cnt = 0;
			adogen = 0;

		}
		else if ((p == 102) && (cnt1 == 3) && (fuck == 3) && (mill.count() <= 300)) {//뻐큐4출력
			printf("\n뻐큐! ( -_-)-ㅗ \n");
			cnt1 = 0;
			fuck = 0;
		}
		else if ((p == 97) && (cnt2 == 3) && (solyugen == 3) && (mill.count() <= 300)) {//소류겐4출력
			printf("\n소류겐! ol\n");
			printf("\tl\n");
			printf("\tㅣㄱ\n");
			cnt2 = 0;
			solyugen = 0;
		}
		else {
			cout << "\n기술 사용 실패 300ms(0.3초)안에 입력 : " << mill.count() << endl; //콤보 시작후 총 입력시간
		}

		if (x == ESC) break;



	}



	return 0;
}