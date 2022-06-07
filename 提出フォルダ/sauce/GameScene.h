#pragma once
#include "BaseScene.h"
#include"../common/Dec.h"
class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
private:
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Game; };    // 自分はゲームシーン
};


