// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 Diffuse			: COLOR0;		// �f�B�t�[�Y�J���[
	float4 Specure			: COLOR1;		// �X�؃L�����J���[
	float2 uv				: TEXCOORD0;		// �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 color			: SV_TARGET0;	// �F
};

SamplerState sam;		// �T���v��
Texture2D tex : register(t0);			// �e�N�X�`��
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