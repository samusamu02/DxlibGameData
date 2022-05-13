#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    int ModelHandle, AttachIndex;
    float TotalTime, PlayTime;

    // ３Ｄモデルの読み込み
    ModelHandle = MV1LoadModel("ModelData/TokinoSora.pmx");

    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 1000.0f);

    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));

    // ３Ｄモデルの1番目のアニメーションをアタッチする
    AttachIndex = MV1AttachAnim(ModelHandle, 1, -1, FALSE);

    // アタッチしたアニメーションの総再生時間を取得する
    TotalTime = MV1GetAttachAnimTotalTime(ModelHandle, AttachIndex);

    // 再生時間の初期化
    PlayTime = 0.0f;


    int MaterialNum = DxLib::MV1GetMaterialNum(ModelHandle);
    for (int i = 0; i < MaterialNum; i++)
    {
        // マテリアルの輪郭線の太さを取得 
        float dotwidth = DxLib::MV1GetMaterialOutLineDotWidth(ModelHandle, i);
        // マテリアルの輪郭線の太さを拡大した分小さくする 
        DxLib::MV1SetMaterialOutLineDotWidth(ModelHandle, i, dotwidth / ModelHandle);
    }


    // 何かキーが押されるかウインドウが閉じられるまでループ
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

        // 再生時間を進める
        PlayTime += 0.2f;

        // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
        if (PlayTime >= TotalTime) {
            PlayTime = 0.0f;
        }

        // 再生時間をセットする
        MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);

        // ３Ｄモデルの描画
        MV1DrawModel(ModelHandle);
    }

    // ＤＸライブラリの後始末
    DxLib_End();
}

    // ソフトの終了
