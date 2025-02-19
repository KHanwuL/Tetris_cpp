#pragma once
#include <conio.h> // 콘솔 입출력을 제공하는 헤더

//_kbhit() : 키보드가 눌렀을 때 반응하는 함수. 
//_getch() : 키도드가 입력된 문자를 반환하는 함수.

void InputKey() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':   //블럭 바로 내리기

            break;
		case 'a':   //왼쪽으로 한 칸 이동

            break;
		case 's':   //아래로 한 칸 이동

            break;
		case 'd':   //오른쪽으로 한 칸 이동

            break;
		case 'q':   //반시계 방향으로 회전

            break;
        case 'e':   //시계 방향으로 회전

            break;
        }
    }
}