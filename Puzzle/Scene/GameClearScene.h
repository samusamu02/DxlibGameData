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
    void DrawOwnScreen(double delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::GameClear; };    // �����̓Q�[���V�[��

    int nowStage_;
};

