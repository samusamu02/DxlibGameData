#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::SetCameraPositionAndTargetAndUpVec(VGet(0, 0, -400), VGet(0, 0, 0), VGet(0, 1, 0));
	int model = MV1LoadModel(L"ModelData/sphere.mqo");
	int pso = LoadPixelShader(L"ps.hlsl");
	int vso = LoadVertexShader(L"vs.hlsl");
	auto tlNum = MV1GetTriangleListNum(model);
	int tilVertType = -1;
	for (int i = 0; i < tlNum; ++i)
	{
		tilVertType = MV1GetTriangleListVertexType(model, i);
		break;
	}

	MV1SetPosition(model, VGet(0, 0, 0));
	float angle = 0.0f;
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		if (tilVertType == DX_MV1_VERTEX_TYPE_1FRAME)
		{
			DrawString(10, 10, L"not normal not skinning", 0xfffffff);
		}
		angle+=0.01;

		DxLib::SetUseZBufferFlag(true);
		DxLib::SetWriteZBuffer3D(true);
		DxLib::SetUseZBufferFlag(true);

		MV1SetUseOrigShader(true);
		DxLib::SetUsePixelShader(pso);
		DxLib::SetUseVertexShader(vso);
		MV1SetRotationXYZ(model, VGet(0, angle, 0));

		MV1DrawModel(model);
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}