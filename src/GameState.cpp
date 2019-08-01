#include "GameState.hpp"
#include "hg2d/Core.hpp"

GameState::GameState(hg2d::Engine &engine) : AGameState(engine) {
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
}
