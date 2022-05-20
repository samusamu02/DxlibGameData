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

// �萔�o�b�t�@
float threshold : register(c0);

SamplerState sam;		// �T���v��
Texture2D tex : register(t0);			// �e�N�X�`��
Texture2D ptn: register (t1);			// �e�N�X�`��

// 1�s�N�Z���h��Ԃ��ۂ̌Ă΂��
PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output;
	float discVal = ptn.Sample(sam, input.uv).r;
	if (discVal > threshold)
	{
		discard;
	}

	float4 col = tex.Sample(sam, input.uv);//float4(input.uv,0.5, 1);		// �Ԃ�Ԃ�
	output.color = col;
	if (col.a == 0.0)
	{
		discard;		// �Ȃ��������Ƃɂ���
	}
	output.color.rgb = 1.0 - output.color.rgb;
	return output;
}