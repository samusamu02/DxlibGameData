#pragma once

#include "Scene/BaseScene.h"

#define lpSceneMng SceneMag::GetInstance()		// マネージャークラスの呼び出し

class SceneMag
{
public:
	// s_Instanceにアクセスするための関数
	static SceneMag& GetInstance(void)
	{
		static SceneMag s_Instance;
		return s_Instance;
	}

	//static void Create(void)
	//{
	//	if (s_Instance == nullptr)
	//	{
	//		s_Instance = new SceneMag();
	//	}
	//}
	//static void Destroy(void)
	//{
	//	delete s_Instance;
	//	s_Instance = nullptr;
	//}
	void Run(void);
	void Update(void);
	void Draw(void);
private:
	//static SceneMag* s_Instance;
	bool SysInit(void);		// 初期化関数
	bool initFlag_;			// 初期化フラグ


	SceneMag();
	~SceneMag();

	// Scneをunique_ptrで管理を宣言
	uniqueScene scene_;

};

