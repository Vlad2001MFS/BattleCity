#pragma once
#include "hg2d/GameState.hpp"
#include "hg2d/GUI.hpp"

class EditorState final : public hg2d::AGameState {
public:
    EditorState(hg2d::Engine &engine);

    virtual void onInitialize() override;
    virtual void onEvent(const hd::WindowEvent &event) override;
	virtual void onChangeCurrentState(AGameState *lastState) override;
	virtual void onDraw() override;

private:
    void mInitializeEditorFrame();

    hg2d::AGUIWidget *mEditorFrame;

    hg2d::Texture *mEmptyCellTex;
    hg2d::Texture *mBuildCellTex;
    hg2d::Texture *mBackgroundTex;
    glm::vec2 mBuildCellPos;
    
    static const float mCameraZoom;
};