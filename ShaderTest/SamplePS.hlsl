// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 Diffuse			: COLOR0;		// ディフーズカラー
	float4 Specure			: COLOR1;		// スぺキュラカラー
	float2 uv				: TEXCOORD0;		// テクスチャ座標
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 color			: SV_TARGET0;	// 色
};

// 定数バッファ
float threshold : register(c0);

SamplerState sam;		// サンプラ
Texture2D tex : register(t0);			// テクスチャ
Texture2D ptn: register (t1);			// テクスチャ

// 1ピクセル塗りつぶし際の呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output;
	float discVal = ptn.Sample(sam, input.uv).r;
	if (discVal > threshold)
	{
		discard;
	}

	float4 col = tex.Sample(sam, input.uv);//float4(input.uv,0.5, 1);		// 赤を返す
	output.color = col;
	if (col.a == 0.0)
	{
		discard;		// なかったことにする
	}
	output.color.rgb = 1.0 - output.color.rgb;
	return output;
}