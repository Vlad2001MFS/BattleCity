#include "PauseState.hpp"
#include "hg2d/Core.hpp"

PauseState::PauseState(hg2d::Engine &engine) : AGameState(engine) {
	mPauseFrame = nullptr;
}

void PauseState::onInitialize() {
    mInitializePauseFrame();
}

void PauseState::onEvent(const hd::WindowEvent& event) {
	if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape) {
		mGameStateSystem.setState("game");
	}
}

void PauseState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("pause");
}

void PauseState::mInitializePauseFrame() {
    mPauseFrame = mGUISystem.createFrame<hg2d::AGUIWidget>("pause");

    hg2d::GUIButton *continueBtn = mPauseFrame->createChild<hg2d::GUIButton>();
    continueBtn->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    continueBtn->setSize(128, 32);
    continueBtn->setText("Continue");
    continueBtn->onMouseButtonReleased += [&]() {
        mGameStateSystem.setState("game");
    };

    hg2d::GUIButton *endGameBtn = mPauseFrame->createChild<hg2d::GUIButton>();
    endGameBtn->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    endGameBtn->setSize(128, 32);
    endGameBtn->setText("End");
    endGameBtn->onMouseButtonReleased += [&]() {
		mGameStateSystem.setState("menu");
    };
}

