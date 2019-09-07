#pragma once
#include "Common.hpp"
#include "hg2d/GameState/AGameState.hpp"
#include "hg2d/GUI/AGUIWidget.hpp"
#include "hg2d/GUI/GUIImage.hpp"
#include "hg2d/GUI/GUILabel.hpp"

class EditorState final : public hg2d::AGameState {
public:
    EditorState(hg2d::Engine &engine);

    virtual void onInitialize() override;
    virtual void onEvent(const hd::WindowEvent &event) override;
	virtual void onChangeCurrentState(AGameState *lastState) override;
	virtual void onDraw() override;

private:
    void mInitializeEditorFrame();
    void mSetCurrentBlock(BlockType type);
    void mCreateBlock(BlockType type, const glm::vec2 &pos, const glm::vec2 &size);
    bool mDestroyBlock(const glm::vec2 &pos);
    void mProcessMiniBlock(BlockType type, const glm::vec2 &pos);

    hg2d::AGUIWidget *mEditorFrame;
    hg2d::GUIImage *mCurrentBlockImage;
    hg2d::GUILabel *mCurrentBuildCellPosLabel;

    hg2d::Texture *mEmptyCellTex;
    hg2d::Texture *mBuildCellTex;
    hg2d::Texture *mBackgroundTex;
    glm::vec2 mBuildCellPos;

    hg2d::Texture *mBlockTextures[static_cast<size_t>(BlockType::Count)];
    BlockType mCurrentBlock;
};