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
    void DrawOwnScreen(double delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::Menu; };    // �����̓Q�[���V�[��
};

