#pragma once
#include <conio.h> // �ܼ� ������� �����ϴ� ���

//_kbhit() : Ű���尡 ������ �� �����ϴ� �Լ�. 
//_getch() : Ű���尡 �Էµ� ���ڸ� ��ȯ�ϴ� �Լ�.

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