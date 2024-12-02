#include "CItem.h"
#include <cstdlib>
#include <ctime>

// ������ ����
Item::Item(int type, const glm::vec3& location)
{
    Item_type = type;
    ILocate = location;

    // type�� ������ ȿ���� ��������� ���
    if (Item_type == 1) {
        IColor = { 0.0f, 1.0f, 0.0f };
    }

    // �⺻ Transform ����
    IScale = { 0.5f, 0.5f, 0.5f };
    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), IScale);
    glm::mat4 Translate = glm::translate(glm::mat4(1.0f), ILocate);
    TR = Translate * Scale;

    // �ٿ�� �ڽ� ����
    glm::vec3 boundScale = IScale * 0.5f;
    Bounding_box[0] = glm::vec4(ILocate - boundScale, 1.0f);
    Bounding_box[1] = glm::vec4(ILocate + boundScale, 1.0f);

    // �� ���� �ʱ�ȭ
    View = true;
}

void Create_Item(std::vector<Item>& items, int gridSize)
{
    // ������ Ÿ�� (0 ~ 2 ����)
    // int randomType = rand() % 3;
    int randomType = 1;

    // ������ ��ġ (���� ��ǥ ����)
    float x = static_cast<float>((rand() % gridSize) - gridSize / 2);
    float y = 0.0f; // ���� Y ��ǥ
    float z = static_cast<float>((rand() % gridSize) - gridSize / 2);
    glm::vec3 randomLocation = glm::vec3(x, y, z);

    // ���ο� ������ ����
    Item newItem(randomType, randomLocation);

    // ����Ʈ�� �߰�
    items.push_back(newItem);

    // Ȯ�ο�
    std::cout << "Item created: Type=" << randomType << ", Location=("
        << x << ", " << y << ", " << z << ")" << std::endl;
}

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

std::unique_ptr<Parent_Packet> Item::Create_item(short index, glm::vec3 color, glm::vec3 locate)
{
    // return std::make_unique<Create_item>(index, color, locate);
}