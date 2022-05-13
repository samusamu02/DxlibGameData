#pragma once
#include "BaseScene.h"
#include"../common/Dec.h"
class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
private:
    bool Init(void) override;
    uniqueScene Updata(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;

    Scene GetSceneID(void) override { return Scene::Title; };
    Vector2 titlePos_;
    Vector2 playKeyPicPos_;

    // ‰æ‘œ
    int TitlePic_;
    int PlayKeyPic_;
    int TitleBackGPic_;

    const int titlePicSizeX_ = 640;
    const int titlePicSizeY_ = 320;
    const int playKeyPicSizeX_ = 640;
    const int playKeyPicSizeY_ = 320;

    int count = 0;

    double titleExrate = 0.0;

    double roll_ = 0;
    Vector2 boxpos_;
    Image image_;
    bool rollflg_ = true;
    NowBlock nowBlock_;
};

