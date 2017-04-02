/*!
 *@brief	DirectX11チュートリアル01
 */
#include "stdafx.h"
#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/tkEngine.h"
#include "tkEngine2\graphics\tkShader.h"
#include "tkEngine2/graphics/GPUPipelineBuffer/tkVertexBuffer.h"

using namespace tkEngine2;

class CTriangleDraw : public IGameObject {
	CShader m_vsShader;
	CShader m_psShader;
	CShader m_csShader;
	CVertexBuffer m_vertexBuffer;
	struct SSimpleVertex {
		CVector3 pos;
	};
public:
	bool Start() override
	{
		m_vsShader.Load("Assets/shader/Tutorial02.fx", "VS", CShader::EnType::VS);
		m_psShader.Load("Assets/shader/Tutorial02.fx", "PS", CShader::EnType::PS);
		m_csShader.Load("Assets/shader/BasicCompute11.fx", "CSMain", CShader::EnType::CS);
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
 *@brief	メイン関数。
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    //tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		
		NewGO<CTriangleDraw>(0);
		//初期化に成功。
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();
	
    return 0;
}

