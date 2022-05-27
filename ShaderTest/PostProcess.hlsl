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

SamplerState sam;		// サンプラ
Texture2D tex : register(t0);			// テクスチャ
Texture2D norm : register(t1);

cbuffer ConstantBuffer : register(b0) {
	float threshold;
	float angle;
}

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output;
	float2 n = norm.Sample(sam, input.uv).xy;
	n = n * 2 - 1;

	float2 dist = n.xy * 0.05;
	dist = float2(cos(angle) * dist.x + sin(angle) * dist.y, 
		-sin(angle) * dist.x + cos(angle) * dist.y);
	output.color = tex.Sample(sam,input.uv+n.xy + dist);
	return output;
}