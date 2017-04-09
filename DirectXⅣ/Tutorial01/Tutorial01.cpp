/*!
 *@brief	DirectX11�`���[�g���A��01
 */
#include "stdafx.h"
#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/tkEngine.h"

using namespace tkEngine2;

class CComputeTest : public IGameObject {
	struct BufType
	{
		int i;
		float f;
	};
	CShader m_csShader;
	CStructuredBuffer m_inputBuffer_0;	//!<���͗pGPU�o�b�t�@0�B
	CStructuredBuffer m_inputBuffer_1;	//!<���͗pGPU�o�b�t�@1�B
	CStructuredBuffer m_outputBuffer;	//!<�o�͗pGPU�o�b�t�@�B
	static const UINT NUM_ELEMENTS = 1024;
	BufType g_vBuf0[NUM_ELEMENTS];		//!<���̓f�[�^0�B
	BufType g_vBuf1[NUM_ELEMENTS];		//!<���̓f�[�^1�B
	CShaderResourceView m_inputSRV_0;	//!<����SRV0�B
	CShaderResourceView m_inputSRV_1;	//!<����SRV1�B
	CUnorderedAccessView m_outputUAV;	//!<�o��UAV�B
public:
	CComputeTest()
	{

	}
	~CComputeTest()
	{

	}
	bool Start() override
	{
		//�R���s���[�g�V�F�[�_�[�����[�h�B
		TK_ASSERT(m_csShader.Load("Assets/shader/BasicCompute11.fx", "CSMain", CShader::EnType::CS), "Failed");
		//���͗p��StructuredBuffer���쐬�B
		TK_ASSERT(m_inputBuffer_0.Create(NUM_ELEMENTS, sizeof(BufType), g_vBuf0), "Failed");
		TK_ASSERT(m_inputBuffer_1.Create(NUM_ELEMENTS, sizeof(BufType), g_vBuf1), "Failed");
		//�o�͗p��StructuredBuffer���쐬�B
		TK_ASSERT(m_outputBuffer.Create(NUM_ELEMENTS, sizeof(BufType), NULL), "Failed");

		//SRV���쐬�B
		TK_ASSERT(m_inputSRV_0.Create(m_inputBuffer_0), "Failed");
		TK_ASSERT(m_inputSRV_1.Create(m_inputBuffer_1), "Failed");
		//UAV���쐬�B
		TK_ASSERT(m_outputUAV.Create(m_outputBuffer), "Failed");
		return true;
	}
	void Update() override
	{

	}
	void Render(CRenderContext& renderContext)
	{
		//�R���s���[�g�V�F�[�_�[��ݒ�B
		renderContext.CSSetShader(m_csShader);
		//SRV��ݒ�B
		renderContext.CSSetShaderResource(0, m_inputSRV_0);
		renderContext.CSSetShaderResource(1, m_inputSRV_1);
		//UAV��ݒ�B
		renderContext.CSSetUnorderedAccessView(0, m_outputUAV);

	}
};

class CTriangleDraw : public IGameObject {
	
	CShader m_vsShader;
	CShader m_psShader;
	
	
	CVertexBuffer m_vertexBuffer;
	struct SSimpleVertex {
		CVector3 pos;
	};
public:
	bool Start() override
	{
		m_vsShader.Load("Assets/shader/Tutorial02.fx", "VS", CShader::EnType::VS);
		m_psShader.Load("Assets/shader/Tutorial02.fx", "PS", CShader::EnType::PS);
		
		SSimpleVertex vertices[] =
		{
			CVector3(0.0f, 0.5f, 0.5f),
			CVector3(0.5f, -0.5f, 0.5f),
			CVector3(-0.5f, -0.5f, 0.5f),
		};
		m_vertexBuffer.Create(3, sizeof(SSimpleVertex), vertices);
		return true;
	}
	void Update() override
	{

	}
	void Render(CRenderContext& renderContext) override
	{
		renderContext.SetVertexBuffer(m_vertexBuffer);
		renderContext.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		renderContext.VSSetShader(m_vsShader);
		renderContext.PSSetShader(m_psShader);
		renderContext.SetInputLayout(m_vsShader.GetInputLayout());
		renderContext.Draw(3,0);
	}
};

/*!
 *@brief	���C���֐��B
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    //tkEngine2�̏������p�����[�^��ݒ肷��B
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//�G���W�����������B
	if (Engine().Init(initParam) == true) {
		
		NewGO<CTriangleDraw>(0);
		NewGO<CComputeTest>(0);
		//�������ɐ����B
		//�Q�[�����[�v�����s�B
		Engine().RunGameLoop();
	}
	//�G���W���̏I�������B
	Engine().Final();
	
    return 0;
}

