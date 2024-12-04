#include "CItem.h"

Item::Item()
{
	ILocate = glm::vec3(0, 0, 0);

	IScale = { 0.2f, 0.2f, 0.2f };
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), IScale);
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), ILocate);
	TR = Translate * Scale;
	View = false;
}