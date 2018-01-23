/*!
 *@brief	���_�V�F�[�_�[�̍ł���{�ƂȂ�A�ˉe�ϊ����s���T���v���B
 */

float4x4 g_mWVP;	//���[���h�~�r���[�~�v���W�F�N�V�����s��B
float4 g_color;					//�J���[

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
};

/*!
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	float4 pos; 
	//���_���W��WVP�s��ŕϊ��B
	pos = mul( In.pos, g_mWVP );
	
	Out.pos = pos;
	Out.color = In.color;
	return Out;
}
/*!
 *@brief	���_�V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	return g_color;
}

technique ColorPrim
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}