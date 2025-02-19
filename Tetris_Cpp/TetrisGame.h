#pragma once
#include <iostream>
#include <conio.h>
#include <random>
#include <chrono>
#include <thread>
#include "TetrisBlock.h"

Block t_block(START_X, START_Y, tetromino_shape[1], 0);

void updateMap(Block& t) {		// PLAYING_MAP에 블럭 업데이트
	initMap();
	for (int y = 0; y < t.getYsize(); y++) {
		for (int x = 0; x < t.getXsize(); x++) {
			PLAYING_MAP[t.getYpos() + y][t.getXpos() + x] = t.getShape()[y][x];
		}
	}
}

const char BLOCK_TYPES[][5] = {	// ▣나 □은 유니코드 문자로 3바이트 + 공백 1바이트+널 종료 문자 1바이트 = 5바이트
	"  ",	// 빈 공간
	"▣ ",	// 프레임
	"□ ",	// 블록
	"--"	// 경계
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
	if (_kbhit()) {				//_kbhit() : 키보드가 눌렀을 때 반응하는 함수. 
		switch (_getch()) {		//_getch() : 키도드가 입력된 문자를 반환하는 함수.
		case 'w':	//블럭 바로 내리기
			t_block.checkUntillBottom();
			break;
		case 'a':	//왼쪽으로 한 칸 이동
			if (t_block.isMoveAvailable(-1, 0)) t_block.moveBlock(-1, 0);
			break;
		case 's':	//아래로 한 칸 이동
			if (t_block.isMoveAvailable(0, 1)) t_block.moveBlock(0, 1);
			break;
		case 'd':   //오른쪽으로 한 칸 이동
			if (t_block.isMoveAvailable(1, 0)) t_block.moveBlock(1, 0);
			break;
		case 'q':   //반시계 방향으로 회전
			if (t_block.isL_rotateAvailable()) t_block.setRotate(t_block.getRotate() - 1);
			break;
		case 'e':   //시계 방향으로 회전
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