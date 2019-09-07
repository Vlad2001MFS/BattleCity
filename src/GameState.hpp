#pragma once
#include "Common.hpp"
#include "hg2d/GameState/AGameState.hpp"
#include "hg2d/Renderer/RenderSystem.hpp"
#include "hg2d/GUI/AGUIWidget.hpp"

class GameState final : public hg2d::AGameState {
public:
    GameState(hg2d::Engine &engine);

    virtual void onInitialize() override;
    virtual void onEvent(const hd::WindowEvent &event) override;
	virtual void onChangeCurrentState(AGameState *lastState) override;
	virtual void onDraw() override;

private:
    void mSetLevel(int level);

    hg2d::Texture *mBackgroundTex;

    int mCurrentLevel;

    static const int mLevelsCount;
};