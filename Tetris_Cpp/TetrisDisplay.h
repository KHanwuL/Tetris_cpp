#pragma once
#include <iostream>
#include "TetrisBlock.h"

constexpr int MAP_WIDTH = 12;
constexpr int MAP_HEIGHT = 22;

int ORIGIN_MAP[MAP_HEIGHT][MAP_WIDTH];

void initMap() {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) {
				ORIGIN_MAP[y][x] = 1;
			}
			else ORIGIN_MAP[y][x] = 0;
		}
	}
}

const char BLOCK_TYPES[][4] =	//▣나 □은 유니코드 문자로 3바이트이므로 널값 '\0'을 마지막 문자로 넣어 각 문자열이 저장될 공간의 크기를 4개의 char로 고정하기 위해 [4]로 할당
{
	"  ",  // 빈 공간
	"▣",  // 프레임
	"□"    // 블록
};

void displayMap() {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			std::cout << BLOCK_TYPES[ORIGIN_MAP[y][x]];
		}
		std::cout << '\n';
	}
}