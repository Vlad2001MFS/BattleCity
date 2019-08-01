#pragma once
#include "hg2d/GameState.hpp"
#include "hg2d/GUI.hpp"

class GameState final : public hg2d::AGameState {
public:
    GameState(hg2d::Engine &engine);

    virtual void onInitialize() override;
    virtual void onEvent(const hd::WindowEvent &event) override;
	virtual void onChangeCurrentState(AGameState *lastState) override;

private:

};