#pragma once
#include <iostream>
#include <conio.h>
#include <random>
#include <chrono>
#include <thread>
#include "TetrisBlock.h"

Block t_block(START_X, START_Y, tetromino_shape[1], 0);

void updateMap(Block& t) {		// PLAYING_MAP�� �� ������Ʈ
	initMap();
	for (int y = 0; y < t.getYsize(); y++) {
		for (int x = 0; x < t.getXsize(); x++) {
			PLAYING_MAP[t.getYpos() + y][t.getXpos() + x] = t.getShape()[y][x];
		}
	}
}

const char BLOCK_TYPES[][5] = {	// �ó� ���� �����ڵ� ���ڷ� 3����Ʈ + ���� 1����Ʈ+�� ���� ���� 1����Ʈ = 5����Ʈ
	"  ",	// �� ����
	"�� ",	// ������
	"�� ",	// ���
	"--"	// ���
};

void displayMap() {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			std::cout << BLOCK_TYPES[PLAYING_MAP[y][x]];
		}
		std::cout << '\n';
	}
}

void InputKey() {
	if (_kbhit()) {				//_kbhit() : Ű���尡 ������ �� �����ϴ� �Լ�. 
		switch (_getch()) {		//_getch() : Ű���尡 �Էµ� ���ڸ� ��ȯ�ϴ� �Լ�.
		case 'w':	//�� �ٷ� ������
			t_block.checkUntillBottom();
			break;
		case 'a':	//�������� �� ĭ �̵�
			if (t_block.isMoveAvailable(-1, 0)) t_block.moveBlock(-1, 0);
			break;
		case 's':	//�Ʒ��� �� ĭ �̵�
			if (t_block.isMoveAvailable(0, 1)) t_block.moveBlock(0, 1);
			break;
		case 'd':   //���������� �� ĭ �̵�
			if (t_block.isMoveAvailable(1, 0)) t_block.moveBlock(1, 0);
			break;
		case 'q':   //�ݽð� �������� ȸ��
			if (t_block.isL_rotateAvailable()) t_block.setRotate(t_block.getRotate() - 1);
			break;
		case 'e':   //�ð� �������� ȸ��
			if (t_block.isR_rotateAvailable()) t_block.setRotate(t_block.getRotate() + 1);
			break;
		}
	}
}

int TetrisGame()
{
	emptyMap();
	t_block.setRandom();
	updateMap(t_block);
	displayMap();
	while (1) {
		InputKey();

		t_block.checkBottom();
		system("cls");
		initMap();
		updateMap(t_block);
		displayMap();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}