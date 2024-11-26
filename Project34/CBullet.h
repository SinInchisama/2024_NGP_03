#pragma once
#include "include/glm/glm.hpp"

class Bullet {
private:
	int dir_x, dir_y;
	float speed;

public:
	glm::vec3 Iscale;
	glm::vec3 Ilocate;
	glm::vec3 Icolor;
	//glm::mat4 TR;

	int x, y, z;
	bool enable{ false };

	glm::vec4 Bounding_box[2];

	bool View;

	void set_dir(int _dir_x, int _dir_y) 
	{
		dir_x = _dir_x;
		dir_y = _dir_y;
	}

	void set_speed(float _speed) 
	{
		speed = _speed;
	}

	void move() 
	{
		x += speed * dir_x;
		y += speed * dir_y;
	}
};
// 소스.cpp 파일에 플레이어 별 배열 생성
// 배열의 인덱스로 총알을 구분 (플레이어에 남은 총알 개수 변수 추가 필요?)
// 최초 활성화 시에 방향과 속력을 지정해준 뒤 활성화 (만약 총알의 속력이 고정되어 있다면, 생성과 함께 초기화하도록 변경)
// 총알이 범위 밖으로 나가 삭제되는 과정 개발 필요