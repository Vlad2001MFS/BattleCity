#pragma once
#include "hg2d/GameState/AGameState.hpp"
#include "hg2d/GUI/AGUIWidget.hpp"

class MenuState final : public hg2d::AGameState {
public:
    MenuState(hg2d::Engine &engine);

    virtual void onInitialize() override;
	virtual void onEvent(const hd::WindowEvent& event) override;
	virtual void onChangeCurrentState(AGameState *lastState) override;

private:
    void mInitializeMenuFrame();

    hg2d::AGUIWidget *mMenuFrame;
};