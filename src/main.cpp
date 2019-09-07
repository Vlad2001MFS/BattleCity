#include "hg2d/Core/Engine.hpp"
#include "hg2d/GameState/GameStateSystem.hpp"
#include "hg2d/Scene/SpriteSystem.hpp"
#include "hg2d/Scene/BodySystem.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "GameState.hpp"
#include "EditorState.hpp"

int main() {
    hg2d::EngineCreateInfo createInfo;
    hg2d::Engine engine(createInfo);

    engine.getSceneSystem().createSystem<hg2d::SpriteSystem>();
    engine.getSceneSystem().createSystem<hg2d::BodySystem>();

    engine.getGameStateSystem().createState<MenuState>("menu");
    engine.getGameStateSystem().createState<PauseState>("pause");
    engine.getGameStateSystem().createState<GameState>("game");
    engine.getGameStateSystem().createState<EditorState>("editor");
    engine.getGameStateSystem().setState("menu");

    engine.run();
    return 0;
}