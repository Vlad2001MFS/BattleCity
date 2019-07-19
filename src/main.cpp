#include "hg2d/HgEngine2D.hpp"

int main() {
    hg2d::EngineCreateInfo createInfo;
    hg2d::Engine engine(createInfo);

    engine.run();
    return 0;
}