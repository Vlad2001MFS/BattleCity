#include "Common.hpp"

const float gCameraZoom = -20.0f;
const glm::vec2 gBlockSize = glm::vec2(0.5f, 0.5f);
const glm::vec2 gBlockHalfSize = gBlockSize / 2.0f;
const glm::vec2 gTankSize = gBlockSize*0.8f;
const float gPlayerSpeed = 5.0f;

const std::string &getBlockTexturePath(BlockType type) {
    static const std::string paths[static_cast<size_t>(BlockType::Count)] = {
        "blocks/empty.png",
        "blocks/base.png",
        "blocks/bricks14.png",
        "blocks/concrete.png",
        "blocks/forest.png",
        "blocks/road.png",
        "blocks/water.png",
    };
    return paths[static_cast<size_t>(type)];
}
