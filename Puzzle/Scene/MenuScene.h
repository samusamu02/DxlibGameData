#pragma once
#include "BaseScene.h"
class MenuScene :
	public BaseScene
{
public:
    MenuScene();
    ~MenuScene();
private:
    Key key_;

    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Menu; };    // 自分はゲームシーン
};

