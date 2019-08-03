#pragma once
#include "3rd/include/glm/glm.hpp"
#include <string>
    
extern const float gCameraZoom;
extern const glm::vec2 gBlockSize;
extern const glm::vec2 gBlockHalfSize;
extern const glm::vec2 gTankSize;
extern const float gPlayerSpeed;

enum class BlockType {
    Empty,
    Base,
    Bricks,
    Concrete,
    Forest,
    Road,
    Water,
    Count
};

const std::string &getBlockTexturePath(BlockType type);