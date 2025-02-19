#pragma once
#include <vector>
#include <Windows.h>

constexpr int MAP_WIDTH = 12;
constexpr int MAP_HEIGHT = 22;

constexpr int START_X = 4;
constexpr int START_Y = 1;

int CURRENT_MAP[MAP_HEIGHT][MAP_WIDTH];																	// ���������� ����� ��
int PLAYING_MAP[MAP_HEIGHT][MAP_WIDTH];																	// ���� �������� �ִ� ���� ��

void emptyMap() {																						// �� ������ �ʱ�ȭ
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (x == 0 || y == MAP_HEIGHT - 1 || x == MAP_WIDTH - 1) { CURRENT_MAP[y][x] = 1; PLAYING_MAP[y][x] = 1; }
			else if (y == 0) { CURRENT_MAP[y][x] = 3; PLAYING_MAP[y][x] = 3; }
			else { CURRENT_MAP[y][x] = 0; PLAYING_MAP[y][x] = 0; }
		}
	}
}

void initMap() {																						// PLAYING_MAP�� CURRENT_MAP���� �ʱ�ȭ
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			PLAYING_MAP[y][x] = CURRENT_MAP[y][x];
		}
	}
}

std::vector<std::vector<std::vector<int>>> tetromino_shape =							//��Ʈ���� �� ���
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

class Block {																							// ��Ʈ���� �� Ŭ����
private:
	int m_xPos, m_yPos;
	int m_bRotate;	// �� ����
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
	
	std::vector<std::vector<int>> setRandom() {																				// ���� �� ����
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, tetromino_shape.size() - 1);
		std::uniform_int_distribution<int> dis2(0, 3);
		setShape(tetromino_shape[dis(gen)]);
		setRotate(dis2(gen));
		return m_bShape;
	}
	inline void moveBlock(int move_x, int move_y) {														// �� �̵�
		if (isMoveAvailable(move_x, move_y)) {
			m_xPos += move_x;
			m_yPos += move_y;
		}
	}

	std::vector<std::vector<int>> L_rotate(const std::vector<std::vector<int>>& shape) {				//�ݽð� �������� ȸ��

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
	
	std::vector<std::vector<int>> R_rotate(const std::vector<std::vector<int>>& shape) {				//�ð� �������� ȸ��
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

	std::vector<std::vector<int>> rotateShape(const std::vector<std::vector<int>>& shape, int rotate) {	//m_bRotate��ŭ �ð� �������� ȸ��
		std::vector<std::vector<int>> rotatedShape = shape;
		while (rotate < 0) rotate += 4;
		rotate %= 4;
		for (int i = 0; i < rotate; i++) {
			rotatedShape = R_rotate(rotatedShape);
		}
		return rotatedShape;
	}

	bool isCollision() {																				// �浹 �˻�
		for (int y = 0; y < getYsize(); y++) {
			for (int x = 0; x < getXsize(); x++) {
				if (m_bShape[y][x] == 2 && CURRENT_MAP[m_yPos + y][m_xPos + x] == 1)	// �� ���� �浹�ϴ� ���
					return true;
				if (m_bShape[y][x] == 2 && CURRENT_MAP[m_yPos + y][m_xPos + x] == 2)	// �ٸ� ���� �浹�ϴ� ���
					return true;
			}
		}
		return false;
	}

	bool isMoveAvailable(int move_x, int move_y) {														// �̵� ���� ����
		int originalX = m_xPos;
		int originalY = m_yPos;
		m_xPos += move_x;
		m_yPos += move_y;

		bool collision = isCollision();
		m_xPos = originalX;
		m_yPos = originalY;
		return !collision;
	}

	bool isR_rotateAvailable() {																		// �ð� �������� ȸ�� ���� ����
		std::vector<std::vector<int>> originalShape = m_bShape;
		int originalRotate = m_bRotate;
		m_bRotate = originalRotate + 1;
		m_bShape = rotateShape(m_bShape, m_bRotate);

		bool collision = isCollision();
		m_bRotate = originalRotate;
		m_bShape = originalShape;
		return !collision;
	}

	bool isL_rotateAvailable() {																		// �ݽð� �������� ȸ�� ���� ����
		std::vector<std::vector<int>> originalShape = m_bShape;
		int originalRotate = m_bRotate;
		m_bRotate = originalRotate - 1;
		m_bShape = rotateShape(m_bShape, m_bRotate);

		bool collision = isCollision();
		m_bRotate = originalRotate;
		m_bShape = originalShape;
		return !collision;
	}

	void checkBottom() {																				// �ٴڿ� ��Ҵ��� Ȯ��
		if (isMoveAvailable(0, 1))
			moveBlock(0, 1);
		else {
			saveMap();
			setPosition(START_X, START_Y);	// ���� ���� �� ��ġ�� �ʱ�ȭ
			setRandom();	// ���� ���� �� ����
			if (isCollision()) {	// ���� ���� ���� �̹� �浹�ϴ� ���
				// ���� ����
			}
		}
	}

	void checkUntillBottom() {																			// �ٴڿ� ���� ������ �� �̵�
		while (isMoveAvailable(0, 1)) {
			moveBlock(0, 1);
		}
		saveMap();
		setPosition(START_X, START_Y);	// ���� ���� �� ��ġ�� �ʱ�ȭ
		setRandom();	// ���� ���� �� ����
		if (isCollision()) {	// ���� ���� ���� �̹� �浹�ϴ� ���
			// ���� ����
		}
	}

	void saveMap() {																					// ���� CURRENT_MAP�� ����
		for (int y = 0; y < getYsize(); y++) {
			for (int x = 0; x < getXsize(); x++) {
				if (m_bShape[y][x] == 2) {
					CURRENT_MAP[m_yPos + y][m_xPos + x] = 2;
				}
			}
		}
	}
};
