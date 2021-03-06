/*!
 *@brief	頂点シェーダーの最も基本となる、射影変換を行うサンプル。
 */

float4x4 g_mWVP;	//ワールド×ビュー×プロジェクション行列。
float4 g_color;					//カラー

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
};

/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	float4 pos; 
	//頂点座標をWVP行列で変換。
	pos = mul( In.pos, g_mWVP );
	
	Out.pos = pos;
	Out.color = In.color;
	return Out;
}
/*!
 *@brief	頂点シェーダー。
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