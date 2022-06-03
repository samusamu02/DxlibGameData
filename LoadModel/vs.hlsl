struct VT_INPUT
{
	float3 pos : POTISION;	// 座標
	float3 norm : NORMAL;	// 法線
	float4 diffuse : COLOR0;	// ディユーズカラー
	float4 specular : COLOR1;	// スぺキュラカラー
	float4 uv0 : TEXCOORD0;		//
	float4 uv1 : TEXCOORD1;
};

cbuffer BaseCBuffer : register(b1)
{
	float4 AntiViewportM[4];	// 4x4
	matrix ProjectionM[4];	// 4x4
	float4 ViewM[3];	// 4x3(カメラ）
	float4 localM[3];	// 4x3(回転拡縮平行移動
	float4 ToonQueSize;
	float DiffuseSource;
	float SpeculerSource;
	float MulSpeclarColor;
	float Padding;
}

struct VSoutput {
	float4 svpos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:NORMAL;
	float2 uv:TEXCOORD0;
};

float4 main(VT_INPUT input)
{
	VSoutput ret;
	float4 pos = float4(input.pos,1);

	pos.x = dot(pos, localM[0]);
	pos.y = dot(pos, localM[1]);
	pos.z = dot(pos, localM[2]);

	pos.x = dot(pos, ViewM[0]);
	pos.y = dot(pos, ViewM[1]);
	pos.z = dot(pos, ViewM[2]);

	pos.x = dot(pos, ProjectionM[0]);
	pos.y = dot(pos, ProjectionM[1]);
	pos.z = dot(pos, ProjectionM[2]);
	pos.w = dot(pos, ProjectionM[3]);

	ret.svpos = pos;
	ret.pos = input.pos;
	ret.uv = input.uv0.xy;
	re.norm = input.norm;
	return ret;
}