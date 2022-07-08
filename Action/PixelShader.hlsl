struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : SV_TARGET0;
};

SamplerState smp : register(s0);

texture2D tex : register(t0);

struct PointLight
{
	float4 color;
	float2 pos;
	float k;
};

cbuffer Light : register(b0)
{
	PointLight lights[2];
};

float4 ColcPointLight(PointLight light, float2 nowPos)
{
	// ライトの座標から距離を得る
	float d = length(nowPos - light.pos);

	// 減衰を計算
	float l = light.k / pow(d, 2);

	return float4(light.color.rgb * saturate(l), 1);
}

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output;


	float4 texColor = tex.Sample(smp, input.uv);
	float2 nowPos = input.pos.xy;

	float4 lightColor;
	for (int i = 0; i < 2; i++)
	{
		lightColor += ColcPointLight(lights[i], nowPos);
	}

	output.color = lightColor + texColor;
	return output;
}