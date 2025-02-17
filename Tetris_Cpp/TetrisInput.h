#pragma once
#include <conio.h> // 콘솔 입출력을 제공하는 헤더

//_kbhit() : 키보드가 눌렀을 때 반응하는 함수. 
//_getch() : 키도드가 입력된 문자를 반환하는 함수.

void InputKey() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':

            break;
        case 'a':

            break;
        case 's':

            break;
        case 'd':

            break;
        case 'q':

            break;
        case 'e':

            break;
        }
    }
}