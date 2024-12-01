#include "CBullet.h"
#include "CPlayer.h"

void Bullet::InitBullet(Player& p)
{
	Blocate = p.Get_Plocate() + p.Get_Move();
	Bscale = glm::vec3{ 0.3f,0.3f,0.3f };

	glm::mat4 TR1 = glm::mat4(1.0f);
	glm::mat4 Tx = glm::mat4(1.0f);
	glm::mat4 Scale = glm::mat4(1.0f);

	Scale = glm::scale(Scale, glm::vec3(Bscale));
	Tx = glm::translate(Tx, Blocate);

	TR = Tx * Scale * TR1;

	glm::vec3 bound_scale = { 0.3f / 2, 0.3f / 2, 0.3f / 2 };

	Bounding_box[0] = { (Blocate - bound_scale), 1.f };
	Bounding_box[1] = { (Blocate + bound_scale), 1.f };

	x_dir = 0;
	z_dir = 0;

	speed = 0.15f;

	View = false;
}