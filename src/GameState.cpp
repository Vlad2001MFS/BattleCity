#include "GameState.hpp"
#include "hg2d/Core.hpp"
#include "hg2d/Scene.hpp"

const int GameState::mLevelsCount = 1;

GameState::GameState(hg2d::Engine &engine) : AGameState(engine) {
    mCurrentLevel = -1;
}

void GameState::onInitialize() {
}

void GameState::onEvent(const hd::WindowEvent &event) {
    if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape) {
        mGameStateSystem.setState("pause");
    }
}

void GameState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("");
    if (lastState != mGameStateSystem.getState("pause")) {
        mSetLevel(0);
    }
}

void GameState::mSetLevel(int level) {
    if (level != mCurrentLevel && level >= 0 && level < mLevelsCount) {
        mCurrentLevel = level;
        mSceneSystem.load("level" + std::to_string(mCurrentLevel) + ".json");
    }
}
