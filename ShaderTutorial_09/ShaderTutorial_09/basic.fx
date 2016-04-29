/*!
 *@brief	���_�V�F�[�_�[�̍ł���{�ƂȂ�A�ˉe�ϊ����s���T���v���B
 */


float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix;			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4 g_rotationMatrix;		//!<��]�s��B

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B

float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B

struct VS_INPUT{
	float4	pos				: POSITION;
	float4	color			: COLOR0;
	float3	normal			: NORMAL;		//�@���B
	float3	tangentNormal	: TANGENT;		//�ڃx�N�g��
	float2	uv				: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal			: TEXCOORD1;		//�@���B
	float3	tangentNormal	: TEXCOORD2;		//�ڃx�N�g��
};

texture g_diffuseMap;		//�f�B�t���[�Y�}�b�v
sampler g_diffuseMapSampler = 
sampler_state
{
	Texture = <g_diffuseMap>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_normalMap;		//�@���}�b�v
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalMap>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};


/*!
 * @brief	���C�g���v�Z�B
 */
float4 CalcLight( float3 normal )
{
	float4 lig = 0.0f;
	{
		for( int i = 0; i < DIFFUSE_LIGHT_NUM; i++ ){
			lig.xyz += max( 0.0f, dot(normal, -g_diffuseLightDirection[i].xyz) ) 
					* g_diffuseLightColor[i].xyz;
		}
		lig += g_ambientLight;
	}
	return lig;
}
/*!
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	float4 pos; 
	pos = mul( In.pos, g_worldMatrix );		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul( pos, g_viewMatrix );			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul( pos, g_projectionMatrix );	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	Out.color = In.color;
	Out.uv = In.uv;
	//�@������]�B
	Out.normal = mul(In.normal, g_rotationMatrix);
	Out.tangentNormal = mul(In.tangentNormal, g_rotationMatrix);
	return Out;
}
/*!
 *@brief	���_�V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float3 normal = tex2D( g_normalMapSampler, In.uv );
	float4x4 tangentSpaceMatrix;
	float3 biNormal = normalize( cross( In.tangentNormal, In.normal) );
	tangentSpaceMatrix[0] = float4( In.tangentNormal, 0.0f);
	tangentSpaceMatrix[1] = float4( biNormal, 0.0f);
	tangentSpaceMatrix[2] = float4( In.normal, 0.0f);
	tangentSpaceMatrix[3] = float4( 0.0f, 0.0f, 0.0f, 1.0f );
	//-1.0�`1.0�͈̔͂Ƀ}�b�s���O����B
	normal = (normal * 2.0f)- 1.0f;
	normal = tangentSpaceMatrix[0] * normal.x + tangentSpaceMatrix[1] * normal.y + tangentSpaceMatrix[2] * normal.z; 
	float4 lig = CalcLight(normal);
	float4 diff = tex2D( g_diffuseMapSampler, In.uv );
	float4 color = diff* lig;
	return float4( color.xyz, 1.0f);
//	return float4(normal.xyz, 1.0f);
}

technique ColorPrim
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}