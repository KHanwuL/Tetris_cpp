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

const char BLOCK_TYPES[][4] =	//�ó� ���� �����ڵ� ���ڷ� 3����Ʈ�̹Ƿ� �ΰ� '\0'�� ������ ���ڷ� �־� �� ���ڿ��� ����� ������ ũ�⸦ 4���� char�� �����ϱ� ���� [4]�� �Ҵ�
{
	"  ",  // �� ����
	"��",  // ������
	"��"    // ���
};

void displayMap() {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			std::cout << BLOCK_TYPES[ORIGIN_MAP[y][x]];
		}
		std::cout << '\n';
	}
}