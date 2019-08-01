#include "EditorState.hpp"
#include "hg2d/Core.hpp"
#include "hg2d/Renderer.hpp"
#include "hg2d/Scene.hpp"
#include "hg2d/Cache.hpp"

EditorState::EditorState(hg2d::Engine &engine) : AGameState(engine), mBuildCellPos(0, 0) {
	mEditorFrame = nullptr;
    mEmptyCellTex = nullptr;
    mBuildCellTex = nullptr;
}

void EditorState::onInitialize() {
    mInitializeEditorFrame();

    mEmptyCellTex = mCacheSystem.loadTexture("editor/emptyCell.png");
    mBuildCellTex = mCacheSystem.loadTexture("editor/buildCell.png");
}

void EditorState::onEvent(const hd::WindowEvent &event) {
    if (event.type == hd::WindowEventType::Key && event.key.state == hd::KeyState::Released) {
        switch (event.key.code) {
            case hd::KeyCode::Escape: {
                mGameStateSystem.setState("pause");
                break;
            }
            case hd::KeyCode::Up: {
                mBuildCellPos.y = glm::clamp(mBuildCellPos.y + 1, -6.0f, 6.0f);
                break;
            }
            case hd::KeyCode::Down: {
                mBuildCellPos.y = glm::clamp(mBuildCellPos.y - 1, -6.0f, 6.0f);
                break;
            }
            case hd::KeyCode::Left: {
                mBuildCellPos.x = glm::clamp(mBuildCellPos.x - 1, -6.0f, 6.0f);
                break;
            }
            case hd::KeyCode::Right: {
                mBuildCellPos.x = glm::clamp(mBuildCellPos.x + 1, -6.0f, 6.0f);
                break;
            }
        }
    }
}

void EditorState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("editor");
    if (lastState == mGameStateSystem.getState("menu")) {
        mSceneSystem.clear();
    }
}

void EditorState::onDraw() {
    for (int y = -6; y <= 6; y++) {
        for (int x = -6; x <= 6; x++) {
            hg2d::RenderOp rop;
            rop.camPos.z = -20.0f;
            rop.pos = glm::vec2(x, y);
            rop.size = glm::vec2(0.5f, 0.5f);
            rop.texture = mEmptyCellTex;
            mRenderSystem.addRenderOp(rop);
        }
    }

    hg2d::RenderOp buildCellRop;
    buildCellRop.camPos.z = -20.0f;
    buildCellRop.pos = mBuildCellPos;
    buildCellRop.size = glm::vec2(0.5f, 0.5f);
    buildCellRop.texture = mBuildCellTex;
    mRenderSystem.addRenderOp(buildCellRop);
}

void EditorState::mInitializeEditorFrame() {
    mEditorFrame = mGUISystem.createFrame<hg2d::AGUIWidget>("editor");
}
