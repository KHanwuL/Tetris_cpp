#pragma once
#include <vector>
#include <Windows.h>

constexpr int MAP_WIDTH = 12;
constexpr int MAP_HEIGHT = 22;

constexpr int START_X = 4;
constexpr int START_Y = 1;

int CURRENT_MAP[MAP_HEIGHT][MAP_WIDTH];																	// 마지막으로 저장된 맵
int PLAYING_MAP[MAP_HEIGHT][MAP_WIDTH];																	// 블럭이 떨어지고 있는 중인 맵

void emptyMap() {																						// 빈 맵으로 초기화
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (x == 0 || y == MAP_HEIGHT - 1 || x == MAP_WIDTH - 1) { CURRENT_MAP[y][x] = 1; PLAYING_MAP[y][x] = 1; }
			else if (y == 0) { CURRENT_MAP[y][x] = 3; PLAYING_MAP[y][x] = 3; }
			else { CURRENT_MAP[y][x] = 0; PLAYING_MAP[y][x] = 0; }
		}
	}
}

void initMap() {																						// PLAYING_MAP을 CURRENT_MAP으로 초기화
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			PLAYING_MAP[y][x] = CURRENT_MAP[y][x];
		}
	}
}

std::vector<std::vector<std::vector<int>>> tetromino_shape =							//테트리스 블럭 모양
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

class Block {																							// 테트리스 블럭 클래스
private:
	int m_xPos, m_yPos;
	int m_bRotate;	// 블럭 방향
	std::vector<std::vector<int>> m_bShape;
public:
	Block(int x, int y, std::vector<std::vector<int>> shape, int angle): m_xPos(x), m_yPos(y), m_bShape(shape), m_bRotate(angle) { m_bShape = rotateShape(m_bShape, m_bRotate); }
	inline int getXpos() const { return m_xPos; }
	inline int getYpos() const { return m_yPos; }
	inline int getRotate() const { return m_bRotate; }
	inline std::vector<std::vector<int>> getShape() const { return m_bShape; }
	inline size_t getXsize() const { return m_bShape[0].size(); }
	inline size_t getYsize() const { return m_bShape.size(); }
	
	inline void setPosition(int x, int y) { m_xPos = x; m_yPos = y; }
	inline void setShape(std::vector<std::vector<int>> shape) { m_bShape = shape; }
	inline void setRotate(int angle) { m_bRotate = angle; m_bShape = rotateShape(m_bShape, m_bRotate); }
	
	std::vector<std::vector<int>> setRandom() {																				// 랜덤 블럭 설정
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, tetromino_shape.size() - 1);
		std::uniform_int_distribution<int> dis2(0, 3);
		setShape(tetromino_shape[dis(gen)]);
		setRotate(dis2(gen));
		return m_bShape;
	}
	inline void moveBlock(int move_x, int move_y) {														// 블럭 이동
		if (isMoveAvailable(move_x, move_y)) {
			m_xPos += move_x;
			m_yPos += move_y;
		}
	}

	std::vector<std::vector<int>> L_rotate(const std::vector<std::vector<int>>& shape) {				//반시계 방향으로 회전

		size_t n = shape.size();
		size_t m = shape[0].size();

		std::vector<std::vector<int>> Lrotated(m, std::vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				Lrotated[m - j - 1][i] = shape[i][j];
			}
		}
		return Lrotated;
	}
	
	std::vector<std::vector<int>> R_rotate(const std::vector<std::vector<int>>& shape) {				//시계 방향으로 회전
		size_t n = shape.size();
		size_t m = shape[0].size();

		std::vector<std::vector<int>> R_rotated(m, std::vector<int>(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				R_rotated[j][n - i - 1] = shape[i][j];
			}
		}
		return R_rotated;
	}

	std::vector<std::vector<int>> rotateShape(const std::vector<std::vector<int>>& shape, int rotate) {	//m_bRotate만큼 시계 방향으로 회전
		std::vector<std::vector<int>> rotatedShape = shape;
		while (rotate < 0) rotate += 4;
		rotate %= 4;
		for (int i = 0; i < rotate; i++) {
			rotatedShape = R_rotate(rotatedShape);
		}
		return rotatedShape;
	}

	bool isCollision() {																				// 충돌 검사
		for (int y = 0; y < getYsize(); y++) {
			for (int x = 0; x < getXsize(); x++) {
				if (m_bShape[y][x] == 2 && CURRENT_MAP[m_yPos + y][m_xPos + x] == 1)	// 맵 벽에 충돌하는 경우
					return true;
				if (m_bShape[y][x] == 2 && CURRENT_MAP[m_yPos + y][m_xPos + x] == 2)	// 다른 블럭과 충돌하는 경우
					return true;
			}
		}
		return false;
	}

	bool isMoveAvailable(int move_x, int move_y) {														// 이동 가능 여부
		int originalX = m_xPos;
		int originalY = m_yPos;
		m_xPos += move_x;
		m_yPos += move_y;

		bool collision = isCollision();
		m_xPos = originalX;
		m_yPos = originalY;
		return !collision;
	}

	bool isR_rotateAvailable() {																		// 시계 방향으로 회전 가능 여부
		std::vector<std::vector<int>> originalShape = m_bShape;
		int originalRotate = m_bRotate;
		m_bRotate = originalRotate + 1;
		m_bShape = rotateShape(m_bShape, m_bRotate);

		bool collision = isCollision();
		m_bRotate = originalRotate;
		m_bShape = originalShape;
		return !collision;
	}

	bool isL_rotateAvailable() {																		// 반시계 방향으로 회전 가능 여부
		std::vector<std::vector<int>> originalShape = m_bShape;
		int originalRotate = m_bRotate;
		m_bRotate = originalRotate - 1;
		m_bShape = rotateShape(m_bShape, m_bRotate);

		bool collision = isCollision();
		m_bRotate = originalRotate;
		m_bShape = originalShape;
		return !collision;
	}

	void checkBottom() {																				// 바닥에 닿았는지 확인
		if (isMoveAvailable(0, 1))
			moveBlock(0, 1);
		else {
			saveMap();
			setPosition(START_X, START_Y);	// 다음 나올 블럭 위치로 초기화
			setRandom();	// 다음 나올 블럭 설정
			if (isCollision()) {	// 다음 나올 블럭이 이미 충돌하는 경우
				// 게임 오버
			}
		}
	}

	void checkUntillBottom() {																			// 바닥에 닿을 때까지 블럭 이동
		while (isMoveAvailable(0, 1)) {
			moveBlock(0, 1);
		}
		saveMap();
		setPosition(START_X, START_Y);	// 다음 나올 블럭 위치로 초기화
		setRandom();	// 다음 나올 블럭 설정
		if (isCollision()) {	// 다음 나올 블럭이 이미 충돌하는 경우
			// 게임 오버
		}
	}

	void saveMap() {																					// 블럭을 CURRENT_MAP에 고정
		for (int y = 0; y < getYsize(); y++) {
			for (int x = 0; x < getXsize(); x++) {
				if (m_bShape[y][x] == 2) {
					CURRENT_MAP[m_yPos + y][m_xPos + x] = 2;
				}
			}
		}
	}
};
