#pragma once
#include <conio.h> // �ܼ� ������� �����ϴ� ���

//_kbhit() : Ű���尡 ������ �� �����ϴ� �Լ�. 
//_getch() : Ű���尡 �Էµ� ���ڸ� ��ȯ�ϴ� �Լ�.

void InputKey() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':   //�� �ٷ� ������

            break;
		case 'a':   //�������� �� ĭ �̵�

            break;
		case 's':   //�Ʒ��� �� ĭ �̵�

            break;
		case 'd':   //���������� �� ĭ �̵�

            break;
		case 'q':   //�ݽð� �������� ȸ��

            break;
        case 'e':   //�ð� �������� ȸ��

            break;
        }
    }
}