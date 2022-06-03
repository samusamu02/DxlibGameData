struct PSInput {
	float4 svPos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:NORMAL;
	float2 uv:TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
	return float4(input.norm, 1.0f);
}