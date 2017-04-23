/*!
 *@brief	DirectX11チュートリアル01
 *@details
 * GPGPU入門。
 */
#include "stdafx.h"
#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/tkEngine.h"

using namespace tkEngine2;

class CTriangleDraw : public IGameObject {
	CShader m_vsShader;					//VSシェーダー。
	CShader m_psShader;					//PSシェーダー。
	CVertexBuffer m_vertexBuffer;		//頂点バッファ。
	CConstantBuffer	m_constantBuffer;	//定数バッファ。
	struct SSimpleVertex {
		CVector4 pos;
		
	};
	public:
		bool Start() override
		{
			//頂点シェーダーをロード。
			m_vsShader.Load("Assets/shader/Tutorial.fx", "VS", CShader::EnType::VS);
			//ピクセルシェーダーをロード。
			m_psShader.Load("Assets/shader/Tutorial.fx", "PS", CShader::EnType::PS);
			//頂点バッファのソースデータ。
			SSimpleVertex vertices[] =
			{
				CVector4(0.0f, 0.5f, 0.5f, 1.0f),
				CVector4(0.5f, -0.5f, 0.5f, 1.0f),
				CVector4(-0.5f, -0.5f, 0.5f, 1.0f),
			};
			//頂点バッファを作成。
			m_vertexBuffer.Create(3, sizeof(SSimpleVertex), vertices);
			//定数バッファを作る。
			m_constantBuffer.Create(NULL, sizeof(CVector4));
			return true;
		}
		void Update() override
		{
		
		}
		void Render(CRenderContext& renderContext) override
		 {
			//頂点バッファを設定。
			renderContext.SetVertexBuffer(m_vertexBuffer);
			//プリミティブのトポロジーを設定。
			renderContext.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//頂点シェーダーを設定。
			renderContext.VSSetShader(m_vsShader);
			//ピクセルシェーダーを設定。
			renderContext.PSSetShader(m_psShader);
			//入力レイアウトを設定。
			renderContext.SetInputLayout(m_vsShader.GetInputLayout());
			CVector4 color;
			color.x = 1.0f;
			color.y = 0.0f;
			color.z = 0.0f;
			color.w = 1.0f;
			//定数バッファの内容を更新。
			renderContext.UpdateSubresource(m_constantBuffer, color);
			//定数バッファをPSステージに設定。
			renderContext.PSSetConstantBuffer(0, m_constantBuffer);
			//描画。
			renderContext.Draw(3, 0);
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

