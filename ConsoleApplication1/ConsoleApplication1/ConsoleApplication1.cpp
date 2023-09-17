#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <conio.h>
#define ESC 27
#define ENTER 13

int main() {
	puts("이은석의 행복한 VC++");
	while (1) {
		
		char x, p;
		printf("command>");
		int cnt = 0;
		while ((x=_getch()) != ESC && x!=ENTER) {
			p = x;
			cnt++;
			printf("%c", p);

		
		}
		if (x == ESC) break;
		puts("");
		if (cnt != 1) puts("다시 입력하세요");
		else if (p == 'q') puts("qwer 화이팅");
		else if (p == 'w') puts("과제 너무 좋다");
		else if (p == 'e') puts("담주부턴 과제량 1/3배다");
		else if (p == 'r') puts("행복합니다");
		else puts("다시 입력하세요");
	
	
	
	}



	return 0;
}