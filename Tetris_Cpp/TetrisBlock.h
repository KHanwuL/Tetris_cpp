#pragma once
#include <vector>

struct tetromino {
	int x;
	int y;
	std::vector<std::vector<int>> shape;
};

std::vector<std::vector<std::vector<int>>> tetrominoes = 
{
	{
		{2, 2, 2, 2} // I block
	},

	{
		{2, 2},
		{2, 2}		// O block
	},

	{
		{2, 2, 2},
		{0, 2, 0}	// T block
	},

	{
		{0, 2, 2},
		{2, 2, 0}	// S block
	},

	{
		{2, 2, 0},
		{0, 2, 2}	// Z block
	},

	{
		{2, 0, 0},
		{2, 2, 2}	// J block
	},

	{
		{0, 0, 2},
		{2, 2, 2}	// L block
	}
};

std::vector<std::vector<int>> L_rotate(const std::vector<std::vector<int>>& shape)	//반시계 방향으로 회전
{
	int n = shape.size();
	int m = shape[0].size();

	std::vector<std::vector<int>> Lrotated(m, std::vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			Lrotated[m - j - 1][i] = shape[i][j];
		}
	}

	return Lrotated;
}

std::vector<std::vector<int>> R_rotate(const std::vector<std::vector<int>>& shape)	//시계 방향으로 회전
{
	int n = shape.size();
	int m = shape[0].size();

	std::vector<std::vector<int>> R_rotated(m, std::vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			R_rotated[j][n - i - 1] = shape[i][j];
		}
	}

	return R_rotated;
}
