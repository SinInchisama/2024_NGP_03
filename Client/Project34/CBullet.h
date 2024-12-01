#pragma once
#include "include/glm/glm.hpp"
#include "Public.h"

class Bullet {
public:
	glm::vec3 Bscale;
	glm::vec3 Blocate;
	glm::vec3 Bcolor;
	glm::mat4 TR;

	int x, y, z;
	int x_dir;
	int z_dir;
	float speed;

	glm::vec4 Bounding_box[2];

	bool View;
};

<<<<<<< HEAD
void InitBullet(Bullet& bullet)
{
	glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
=======
void InitBullet(Bullet& bullet);

	//glm::vec3 bound_scale = { 0.3f / 2, (float)10 / BOX_Y, 0.3f / 2 };
>>>>>>> ÍπÄÏÑ†Îπà

	int x = rand() % 20;
	int z = rand() % 20;
	// √—æÀ¿« ¡¬«•∏¶ ¿”Ω√∑Œ 0, 0, 0¿∏∑Œ √ ±‚»≠. 
	// √—æÀ¿ª »∞º∫»≠«“ ∂ß √—æÀ¿ª πﬂªÁ«— «√∑π¿ÃæÓ¿« ¿ßƒ°∏¶ ±‚π›¿∏∑Œ πŸ≤„¡‡æﬂ «‘.
	bullet.Blocate = glm::vec3{ 0.0f, 0.0f, 0.0f };
	// ¿œ¥‹ √—æÀ¿« ≈©±‚∏¶ item∞˙ ∞∞∞‘ «ﬂ¿Ω. 
	bullet.Bscale = glm::vec3{ 0.3f,0.3f,0.3f };

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(bullet.Bscale)); //		∞¢ ªÁ∞¢«¸ ≈©±‚ 
	Tx = glm::translate(Tx, bullet.Blocate);

	bullet.TR = Tx * Scale * TR;

	bullet.Bounding_box[0] = { (bullet.Blocate - bound_scale), 1.f };
	bullet.Bounding_box[1] = { (bullet.Blocate + bound_scale), 1.f };

	// √—æÀ¿« πÊ«‚¿ª 0, 0¿∏∑Œ √ ±‚»≠. 
	// √—æÀ¿ª »∞º∫»≠«“ ∂ß √—æÀ¿ª πﬂªÁ«— «√∑π¿ÃæÓ∞° πŸ∂Û∫∏¥¬ πÊ«‚¿ª ±‚π›¿∏∑Œ πŸ≤„¡‡æﬂ «‘. 
	bullet.x_dir = 0;
	bullet.z_dir = 0;

	// ¿œ¥‹ Player¿« 3πË º”µµ∑Œ «ÿ ≥˘¿Ω. « ø‰«œ¥Ÿ∏È ºˆ¡§«“ ∞Õ. 
	bullet.speed = 0.15f;

<<<<<<< HEAD
	bullet.View = false;
}
=======
	//bullet.View = false;
>>>>>>> ÍπÄÏÑ†Îπà
