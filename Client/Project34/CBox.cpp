#include "CBox.h"

void Box::serializeBox(char* buffer) const
{
    int offset = 0;

    // �� ��� ������ buffer�� ����
    memcpy(buffer + offset, &Bcolor, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
}

void Box::deserializeBox(const char* buffer)
{
    int offset = 0;

    memcpy(&Bcolor, buffer + offset, sizeof(glm::vec3)); offset += sizeof(glm::vec3);
}