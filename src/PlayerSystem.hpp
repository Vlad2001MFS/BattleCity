#pragma once
#include "hg2d/Scene/SceneSystem.hpp"

class PlayerComponent : public hg2d::AECSComponent {
public:
    PlayerComponent(hg2d::Engine &engine);
};

class PlayerSystem : public hg2d::AECSSystem {
public:
    PlayerSystem(hg2d::Engine &engine);

    virtual void onInitialize() override;
    virtual void onFixedUpdate() override;
};