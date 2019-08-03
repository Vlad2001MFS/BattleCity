#pragma once
#include <string>

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