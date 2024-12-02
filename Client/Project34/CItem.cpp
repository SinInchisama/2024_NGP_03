#include "CItem.h"

Item::Item()
{
	ILocate = glm::vec3(0, 0, 0);

	IScale = { 0.5f, 0.5f, 0.5f };
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), IScale);
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), ILocate);
	TR = Translate * Scale;
}