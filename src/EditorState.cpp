#include "EditorState.hpp"
#include "hg2d/GameState/GameStateSystem.hpp"
#include "hg2d/Renderer/RenderSystem.hpp"
#include "hg2d/GUI/GUISystem.hpp"
#include "hg2d/Scene/SceneSystem.hpp"
#include "hg2d/Scene/SpriteSystem.hpp"
#include "hg2d/Scene/BodySystem.hpp"
#include "hg2d/Cache/CacheSystem.hpp"
#include "hd/Core/hdStringUtils.hpp"

EditorState::EditorState(hg2d::Engine &engine) : AGameState(engine), mBuildCellPos(0, 0), mBlockTextures{nullptr} {
	mEditorFrame = nullptr;
    mEmptyCellTex = nullptr;
    mBuildCellTex = nullptr;
    mBackgroundTex = nullptr;
    mCurrentBlock = BlockType::Empty;
}

void EditorState::onInitialize() {
    mInitializeEditorFrame();

    mEmptyCellTex = mCacheSystem.loadTexture("editor/emptyCell.png");
    mBuildCellTex = mCacheSystem.loadTexture("editor/buildCell.png");
    mBackgroundTex = mCacheSystem.loadTexture(hd::Color4(127, 127, 127, 255));

    for (size_t i = 0; i < static_cast<size_t>(BlockType::Count); i++) {
        mBlockTextures[i] = mCacheSystem.loadTexture(getBlockTexturePath(static_cast<BlockType>(i)));
    }
    mSetCurrentBlock(BlockType::Empty);
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

            case hd::KeyCode::Num1: {
                mSetCurrentBlock(BlockType::Empty);
                break;
            }
            case hd::KeyCode::Num2: {
                mSetCurrentBlock(BlockType::Base);
                break;
            }
            case hd::KeyCode::Num3: {
                mSetCurrentBlock(BlockType::Bricks);
                break;
            }
            case hd::KeyCode::Num4: {
                mSetCurrentBlock(BlockType::Concrete);
                break;
            }
            case hd::KeyCode::Num5: {
                mSetCurrentBlock(BlockType::Forest);
                break;
            }
            case hd::KeyCode::Num6: {
                mSetCurrentBlock(BlockType::Road);
                break;
            }
            case hd::KeyCode::Num7: {
                mSetCurrentBlock(BlockType::Water);
                break;
            }

            case hd::KeyCode::Numpad0: {
                if (mCurrentBlock == BlockType::Empty) {
                    if (!mDestroyBlock(mBuildCellPos)) {
                        mDestroyBlock(mBuildCellPos + glm::vec2(-gBlockHalfSize.x, -gBlockHalfSize.y));
                        mDestroyBlock(mBuildCellPos + glm::vec2(-gBlockHalfSize.x, gBlockHalfSize.y));
                        mDestroyBlock(mBuildCellPos + glm::vec2(gBlockHalfSize.x, gBlockHalfSize.y));
                        mDestroyBlock(mBuildCellPos + glm::vec2(gBlockHalfSize.x, -gBlockHalfSize.y));
                    }
                }
                else {
                    if (mCurrentBlock == BlockType::Base) {
                        mCreateBlock(mCurrentBlock, mBuildCellPos, gBlockSize);
                    }
                    else {
                        mCreateBlock(mCurrentBlock, mBuildCellPos + glm::vec2(-gBlockHalfSize.x, -gBlockHalfSize.y), gBlockHalfSize);
                        mCreateBlock(mCurrentBlock, mBuildCellPos + glm::vec2(-gBlockHalfSize.x, gBlockHalfSize.y), gBlockHalfSize);
                        mCreateBlock(mCurrentBlock, mBuildCellPos + glm::vec2(gBlockHalfSize.x, gBlockHalfSize.y), gBlockHalfSize);
                        mCreateBlock(mCurrentBlock, mBuildCellPos + glm::vec2(gBlockHalfSize.x, -gBlockHalfSize.y), gBlockHalfSize);
                    }
                }
                break;
            }
            case hd::KeyCode::Numpad4: {
                mProcessMiniBlock(mCurrentBlock, mBuildCellPos + glm::vec2(-gBlockHalfSize.x, gBlockHalfSize.y));
                break;
            }
            case hd::KeyCode::Numpad5: {
                mProcessMiniBlock(mCurrentBlock, mBuildCellPos + glm::vec2(gBlockHalfSize.x, gBlockHalfSize.y));
                break;
            }
            case hd::KeyCode::Numpad1: {
                mProcessMiniBlock(mCurrentBlock, mBuildCellPos + glm::vec2(-gBlockHalfSize.x, -gBlockHalfSize.y));
                break;
            }
            case hd::KeyCode::Numpad2: {
                mProcessMiniBlock(mCurrentBlock, mBuildCellPos + glm::vec2(gBlockHalfSize.x, -gBlockHalfSize.y));
                break;
            }

            case hd::KeyCode::F1: {
                mSceneSystem.save("editor.json");
                break;
            }
            case hd::KeyCode::F2: {
                mSceneSystem.load("editor.json");
                break;
            }
        }
    }

    mCurrentBuildCellPosLabel->setText(hd::StringUtils::format("Position: %d %d", static_cast<int>(mBuildCellPos.x), static_cast<int>(mBuildCellPos.y)));
}

void EditorState::onChangeCurrentState(AGameState *lastState) {
	mGUISystem.setFrame("editor");
    if (lastState == mGameStateSystem.getState("menu")) {
        hg2d::HEntity entity = mSceneSystem.createEntity();
        hg2d::TransformComponent *transform = mSceneSystem.createComponent<hg2d::TransformComponent>(entity);
        hg2d::CameraComponent *camera = mSceneSystem.createComponent<hg2d::CameraComponent>(entity);
        camera->setZoom(gCameraZoom);
        mSceneSystem.getSystem<hg2d::SpriteSystem>()->setCameraEntity(entity);
    }
}

void EditorState::onDraw() {
    hg2d::RenderOp backgroundRop;
    backgroundRop.camPos.z = gCameraZoom;
    backgroundRop.texture = mBackgroundTex;

    backgroundRop.pos = glm::vec2(-38.5, 0);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(38.5, 0);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(0, 38.5);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    backgroundRop.pos = glm::vec2(0, -38.5);
    backgroundRop.size = glm::vec2(32, 32);
    mRenderSystem.addRenderOp(backgroundRop);

    for (int y = -6; y <= 6; y++) {
        for (int x = -6; x <= 6; x++) {
            hg2d::RenderOp rop;
            rop.camPos.z = gCameraZoom;
            rop.pos = glm::vec2(x, y);
            rop.size = gBlockSize;
            rop.texture = mEmptyCellTex;
            mRenderSystem.addRenderOp(rop);
        }
    }

    hg2d::RenderOp buildCellRop;
    buildCellRop.camPos.z = gCameraZoom;
    buildCellRop.pos = mBuildCellPos;
    buildCellRop.size = gBlockSize;
    buildCellRop.texture = mBuildCellTex;
    mRenderSystem.addRenderOp(buildCellRop);
}

void EditorState::mInitializeEditorFrame() {
    mEditorFrame = mGUISystem.createFrame<hg2d::AGUIWidget>("editor");

    hg2d::GUIImage *currentBlockBackgroundImage = mEditorFrame->createChild<hg2d::GUIImage>();
    currentBlockBackgroundImage->setAlign(hg2d::GUIHAlign::Left, hg2d::GUIVAlign::Top);
    currentBlockBackgroundImage->setSize(40, 40);
    currentBlockBackgroundImage->setTexture(mRenderSystem.createTextureFromColor(hd::Color4::Black));
    mCurrentBlockImage = currentBlockBackgroundImage->createChild<hg2d::GUIImage>();
    mCurrentBlockImage->setAlign(hg2d::GUIHAlign::Center, hg2d::GUIVAlign::Center);
    mCurrentBlockImage->setSize(32, 32);

    mCurrentBuildCellPosLabel = mEditorFrame->createChild<hg2d::GUILabel>();
    mCurrentBuildCellPosLabel->setAlign(hg2d::GUIHAlign::Left, hg2d::GUIVAlign::Top);
}

void EditorState::mSetCurrentBlock(BlockType type) {
    mCurrentBlock = type;
    mCurrentBlockImage->setTexture(mBlockTextures[static_cast<size_t>(type)]);
}

void EditorState::mCreateBlock(BlockType type, const glm::vec2 &pos, const glm::vec2 &size) {
    const std::vector<hg2d::TransformComponent*> &transforms = mSceneSystem.getComponents<hg2d::TransformComponent>();
    auto it = std::find_if(transforms.begin(), transforms.end(), [&](const hg2d::TransformComponent *transform) {
        return transform && transform->getPosition() == pos; 
    });
    if (it == transforms.end()) {
        hg2d::HEntity entity = mSceneSystem.createEntity();
        hg2d::TransformComponent *transform = mSceneSystem.createComponent<hg2d::TransformComponent>(entity);
        hg2d::SpriteComponent *sprite = mSceneSystem.createComponent<hg2d::SpriteComponent>(entity);
        sprite->setTexture(mBlockTextures[static_cast<size_t>(type)]);
        hg2d::BodyComponent *body = mSceneSystem.createComponent<hg2d::BodyComponent>(entity);
        body->setType(hg2d::BodyType::Static);
        body->setPosition(pos);
        body->setBoxShapeSize(size);
    }
}

bool EditorState::mDestroyBlock(const glm::vec2 &pos) {
    const std::vector<hg2d::TransformComponent*> &transforms = mSceneSystem.getComponents<hg2d::TransformComponent>();
    for (size_t i = 0; i < transforms.size(); i++) {
        if (transforms[i] && transforms[i]->getPosition() == pos) {
            hg2d::HEntity entity(i);
            mSceneSystem.destroyEntity(entity);
            return true;
        }
    }
    return false;
}

void EditorState::mProcessMiniBlock(BlockType type, const glm::vec2 &pos) {
    if (type == BlockType::Empty) {
        mDestroyBlock(pos);
    }
    else {
        mCreateBlock(type, pos, gBlockHalfSize);
    }
}
