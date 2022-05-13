#pragma once
#include "BaseScene.h"
#include "../common/Dec.h"
class GameClearScene :
	public BaseScene
{
public:
    GameClearScene();
    ~GameClearScene();
private:
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::GameClear; };    // 自分はゲームシーン

    int nowStage_;
};

