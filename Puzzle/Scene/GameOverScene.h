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
    void DrawOwnScreen(double delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::GameOver; };    // �����̓Q�[���V�[��

};

