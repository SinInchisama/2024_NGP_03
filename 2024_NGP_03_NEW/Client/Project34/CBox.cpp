#include "CBox.h"

void Box::serializeBox(char* buffer) const
{
    // Serialize glm::vec3 Color (3 floats)
    memcpy(buffer, &Color, sizeof(Color));
    buffer += sizeof(Color);

    // Serialize glm::mat4 TR (16 floats)
    memcpy(buffer, &TR, sizeof(TR));
    buffer += sizeof(TR);

    // Serialize glm::vec4 Bounding_box (2 vec4s)
    memcpy(buffer, &Bounding_box, sizeof(Bounding_box));
}

void Box::deserializeBox(const char* buffer)
{
    // Deserialize glm::vec3 Color (3 floats)
    memcpy(&Color, buffer, sizeof(Color));
    buffer += sizeof(Color);

    // Deserialize glm::mat4 TR (16 floats)
    memcpy(&TR, buffer, sizeof(TR));
    buffer += sizeof(TR);

    // Deserialize glm::vec4 Bounding_box (2 vec4s)
    memcpy(&Bounding_box, buffer, sizeof(Bounding_box));
}