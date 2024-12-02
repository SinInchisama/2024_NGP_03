#include "CItem.h"

void Item::serializeItem(char* buffer) const
{
    // Serialize glm::vec3 IColor (3 floats)
    memcpy(buffer, &IColor, sizeof(IColor));
    buffer += sizeof(IColor);

    // Serialize glm::vec3 ILocate
    memcpy(buffer, &ILocate, sizeof(ILocate));
    buffer += sizeof(ILocate);

    // Serialize glm::mat4 TR (16 floats)
    memcpy(buffer, &TR, sizeof(TR));
    buffer += sizeof(TR);

    // Serialize glm::vec4 Bounding_box (2 vec4s)
    memcpy(buffer, &Bounding_box, sizeof(Bounding_box));
}

void Item::deserializeItem(const char* buffer)
{
    // Deserialize glm::vec3 Color (3 floats)
    memcpy(&IColor, buffer, sizeof(IColor));
    buffer += sizeof(IColor);

    memcpy(&ILocate, buffer, sizeof(ILocate));
    buffer += sizeof(ILocate);

    // Deserialize glm::mat4 TR (16 floats)
    memcpy(&TR, buffer, sizeof(TR));
    buffer += sizeof(TR);

    // Deserialize glm::vec4 Bounding_box (2 vec4s)
    memcpy(&Bounding_box, buffer, sizeof(Bounding_box));
}