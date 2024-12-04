#include "CBox.h"
#include "GameMaanger.h"

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

std::unique_ptr<Parent_Packet> Box::Chage_Color(glm::vec3 v, short index,int i)
{
    if (Color != v) {
        Color = v;
        GameManger::Instance->players[0]->Add_Occupy(1);
        return std::make_unique<Change_floor>(index, Color);
    }
    return nullptr;  // Color가 다르지 않으면 nullptr을 반환
}