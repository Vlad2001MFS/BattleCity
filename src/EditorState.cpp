#include "EditorState.hpp"
#include "hg2d/Core.hpp"
#include "hg2d/Renderer.hpp"

EditorState::EditorState(hg2d::Engine &engine) : AGameState(engine) {
	mEditorFrame = nullptr;
}

void EditorState::onInitialize() {
    mInitializeEditorFrame();
}

void EditorState::onEvent(const hd::WindowEvent &event) {
    if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released && event.key.code == hd::KeyCode::Escape) {
        mGameStateSystem.setState("pause");
    }
}

void EditorState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("editor");
}

void EditorState::onDraw() {

}

void EditorState::mInitializeEditorFrame() {
    mEditorFrame = mGUISystem.createFrame<hg2d::AGUIWidget>("editor");
}
