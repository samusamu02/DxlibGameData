#pragma once
#include "BaseScene.h"
class TutorialScene :
	public BaseScene
{
public:
    TutorialScene();
    ~TutorialScene();
private:
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Tutorial; };    // 自分はゲームシーン
};