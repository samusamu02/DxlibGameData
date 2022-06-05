#pragma once
#include<memory>
#include"../common/Vector2.h"
#include "../Blcok/Block.h"
class BaseScene;
// usingで短く
using uniqueScene = std::unique_ptr<BaseScene>;

enum class Scene
{
	Title,
	Menu,
	Tutorial,
	Game,
	GameClear,
	GameOver,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual bool Init(void) = 0;
	virtual uniqueScene Updata(double delta, uniqueScene ownScene) = 0;
	virtual void Draw(double delta);
	virtual void DrawOwnScreen(double delta) = 0;
	virtual Scene GetSceneID(void) = 0;		// 今どのシーンなのか
private:
protected:
	int screenID_;		// データの格納

	int nowScore = 0;

	Vector2 screenSize_;		// 描画先のサイズ
	Key key_;		// キーの情報取得
	Block* block_;
};

