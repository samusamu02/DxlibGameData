#include <DxLib.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "../common/Dec.h"

const static int GAME_Y = 240;    //「ゲーム」文字のy位置
const static int EX_Y = 300;    //「設定」文字のy位置

typedef enum {
    eMenu_Game,        //ゲーム
    eMenu_Ex,

    eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Game;    //現在の選択状態(初期はゲーム選択中)

MenuScene::MenuScene()
{
    Init();
}

MenuScene::~MenuScene()
{
}

bool MenuScene::Init(void)
{


	return true;
}

uniqueScene MenuScene::Updata(double delta, uniqueScene ownScene)
{
    key_.GetKey();

    if (key_.input[KEY_INPUT_DOWN] == 1) {//下キーが押されていたら
        NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
    }
    if (key_.input[KEY_INPUT_UP] == 1) {//上キーが押されていたら
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
    }
    if (key_.input[KEY_INPUT_RETURN] == 1) {//エンターキーが押されたら
        switch (NowSelect) {//現在選択中の状態によって処理を分岐
        case eMenu_Game://設定選択中なら
            return std::make_unique<GameScene>();//シーンを設定画面に変更
            break;
        }
    }

    DrawOwnScreen(delta);		// 自分のスクリーン対して描画情報を与える
    return ownScene;
}

void MenuScene::DrawOwnScreen(double delta)
{
    SetDrawScreen(screenID_);
    ClsDrawScreen();

    DrawString(200, 150, "メニュー画面。", GetColor(255, 255, 255));
    DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "ゲーム", GetColor(255, 255, 255));
    DrawString(280, EX_Y, "エクストラ", GetColor(255, 255, 255));
    int y = 0;
    switch (NowSelect) {//現在の選択状態に従って処理を分岐
    case eMenu_Game://ゲーム選択中なら
        y = GAME_Y;    //ゲームの座標を格納
        break;
    case eMenu_Ex://設定選択中なら
        y = EX_Y;    //設定の座標を格納
        break;
    }
    DrawString(250, y, "■", GetColor(255, 255, 255));
}