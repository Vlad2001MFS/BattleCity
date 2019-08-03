#include "PlayerSystem.hpp"
#include "Common.hpp"
#include "hg2d/Core.hpp"
#include "3rd/include/glm/ext.hpp"

PlayerComponent::PlayerComponent(hg2d::Engine &engine) : AECSComponent(engine) {
}

PlayerSystem::PlayerSystem(hg2d::Engine &engine) : AECSSystem(engine) {
}

void PlayerSystem::onInitialize() {
    mSceneSystem.registerComponentType<PlayerComponent>();
}

void PlayerSystem::onFixedUpdate() {
    const std::vector<hg2d::BodyComponent*> &bodies = mSceneSystem.getComponents<hg2d::BodyComponent>();
    const std::vector<PlayerComponent*> &players = mSceneSystem.getComponents<PlayerComponent>();
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] && bodies[i]) {
            PlayerComponent *player = players[i];
            hg2d::BodyComponent *body = bodies[i];
            if (mEngine.isKeyDown(hd::KeyCode::Up)) {
                body->setAngle(0.0);
                body->setLinearVelocity(glm::vec2(0.0, gPlayerSpeed));
            }
            if (mEngine.isKeyDown(hd::KeyCode::Down)) {
                body->setAngle(glm::pi<float>());
                body->setLinearVelocity(glm::vec2(0.0, -gPlayerSpeed));
            }
            if (mEngine.isKeyDown(hd::KeyCode::Left)) {
                body->setAngle(glm::pi<float>() / 2.0);
                body->setLinearVelocity(glm::vec2(-gPlayerSpeed, 0.0));
            }
            if (mEngine.isKeyDown(hd::KeyCode::Right)) {
                body->setAngle(-glm::pi<float>() / 2.0);
                body->setLinearVelocity(glm::vec2(gPlayerSpeed, 0.0));
            }
        }
    }
}