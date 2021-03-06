#include "GameState.hpp"
#include "PlayerSystem.hpp"
#include "hg2d/GameState/GameStateSystem.hpp"
#include "hg2d/Renderer/RenderSystem.hpp"
#include "hg2d/GUI/GUISystem.hpp"
#include "hg2d/Scene/SceneSystem.hpp"
#include "hg2d/Scene/SpriteSystem.hpp"
#include "hg2d/Scene/BodySystem.hpp"
#include "hg2d/Cache/CacheSystem.hpp"

const int GameState::mLevelsCount = 1;

GameState::GameState(hg2d::Engine &engine) : AGameState(engine) {
    mCurrentLevel = -1;
    mBackgroundTex = nullptr;
}

void GameState::onInitialize() {
    mSceneSystem.createSystem<PlayerSystem>();

    mBackgroundTex = mCacheSystem.loadTexture(hd::Color4(127, 127, 127, 255));
}

void GameState::onEvent(const hd::WindowEvent &event) {
    if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released) {
        switch (event.key.code) {
            case hd::KeyCode::Escape: {
                mGameStateSystem.setState("pause");
                break;
            }
        }
    }
}

void GameState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("");
    if (lastState != mGameStateSystem.getState("pause")) {
        mSetLevel(0);
    }
}

void GameState::onDraw() {
    hg2d::RenderOp backgroundRop;
    backgroundRop.camPos.z = gCameraZoom;
    backgroundRop.texture = mBackgroundTex;

    backgroundRop.pos = glm::vec2(-38.5, 0);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(38.5, 0);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(0, 38.5);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(0, -38.5);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);
}

void GameState::mSetLevel(int level) {
    if (level != mCurrentLevel && level >= 0 && level < mLevelsCount) {
        mCurrentLevel = level;
        mSceneSystem.load("level" + std::to_string(mCurrentLevel) + ".json");

        hg2d::HEntity entity = mSceneSystem.createEntity();
        hg2d::TransformComponent *transform = mSceneSystem.createComponent<hg2d::TransformComponent>(entity);
        hg2d::SpriteComponent *sprite = mSceneSystem.createComponent<hg2d::SpriteComponent>(entity);
        sprite->setTexture(mCacheSystem.loadTexture("player/tank0.png"));
        hg2d::BodyComponent *body = mSceneSystem.createComponent<hg2d::BodyComponent>(entity);
        body->setType(hg2d::BodyType::Dynamic);
        body->setPosition(glm::vec2(-2, -6));
        body->setLinearDamping(gPlayerSpeed*5.0f);
        body->setBoxShapeSize(gTankSize);
        PlayerComponent *player = mSceneSystem.createComponent<PlayerComponent>(entity);
    }
}
