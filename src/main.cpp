#include "hg2d/HgEngine2D.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "GameState.hpp"
#include "EditorState.hpp"

int main() {
    hg2d::EngineCreateInfo createInfo;
    hg2d::Engine engine(createInfo);

    engine.getGameStateSystem().createState<MenuState>("menu");
    engine.getGameStateSystem().createState<PauseState>("pause");
    engine.getGameStateSystem().createState<GameState>("game");
    engine.getGameStateSystem().createState<EditorState>("editor");
    engine.getGameStateSystem().setState("menu");

    engine.run();
    return 0;
}