#pragma once
#include "BaseScene.h"
class GameOverScene :
	public BaseScene
{
public:
    GameOverScene();
    ~GameOverScene();
private:
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::GameOver; };    // 自分はゲームシーン

};

