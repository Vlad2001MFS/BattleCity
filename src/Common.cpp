#include "Common.hpp"

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
