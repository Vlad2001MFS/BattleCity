#include "MenuState.hpp"
#include "hg2d/Core.hpp"

MenuState::MenuState(hg2d::Engine &engine) : AGameState(engine) {
	mMenuFrame = nullptr;
}

void MenuState::onInitialize() {
    mInitializeMenuFrame();
}

void MenuState::onEvent(const hd::WindowEvent& event) {
	if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape) {
		mEngine.close();
	}
}

void MenuState::onChangeCurrentState(AGameState* newState) {
	if (newState == this) {
		mGUISystem.setFrame("menu");
	}
}

void MenuState::mInitializeMenuFrame() {
    mMenuFrame = mGUISystem.createFrame<hg2d::AGUIWidget>("menu");

    hg2d::GUIButton *newGameBtn = mMenuFrame->createChild<hg2d::GUIButton>();
    newGameBtn->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    newGameBtn->setSize(128, 32);
    newGameBtn->setText("New game");
    newGameBtn->onMouseButtonReleased += [&]() {
        mGameStateSystem.setState("game");
    };

    hg2d::GUIButton *editorBtn = mMenuFrame->createChild<hg2d::GUIButton>();
    editorBtn->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    editorBtn->setSize(128, 32);
    editorBtn->setText("Editor");
    editorBtn->onMouseButtonReleased += [&]() {
        mGameStateSystem.setState("editor");
    };

    hg2d::GUIButton *quitBtn = mMenuFrame->createChild<hg2d::GUIButton>();
    quitBtn->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    quitBtn->setSize(128, 32);
    quitBtn->setText("Quit");
    quitBtn->onMouseButtonReleased += [&]() {
        mEngine.close();
    };
}

