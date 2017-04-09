/*!
 *@brief	DirectX11チュートリアル01
 *@details
 * GPGPU入門。
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
	CShader m_csShader;						//!<コンピュートシェーダー。
	CStructuredBuffer m_inputBuffer_0;		//!<入力用GPUバッファ0。
	CStructuredBuffer m_inputBuffer_1;		//!<入力用GPUバッファ1。
	CStructuredBuffer m_outputBuffer;		//!<出力用GPUバッファ。
	CStructuredBuffer m_outputBufferCPU;	//!<CPUでコンピュートの結果を受け取るためのバッファ。
	static const UINT NUM_ELEMENTS = 64;
	BufType g_vBuf0[NUM_ELEMENTS];			//!<入力データ0。
	BufType g_vBuf1[NUM_ELEMENTS];			//!<入力データ1。
	CShaderResourceView m_inputSRV_0;		//!<入力SRV0。
	CShaderResourceView m_inputSRV_1;		//!<入力SRV1。
	CUnorderedAccessView m_outputUAV;		//!<出力UAV。
public:
	CComputeTest()
	{

	}
	~CComputeTest()
	{

	}
	bool Start() override
	{
		//コンピュートシェーダーをロード。
		m_csShader.Load("Assets/shader/BasicCompute11.fx", "CSMain", CShader::EnType::CS);
		for (int i = 0; i < NUM_ELEMENTS; i++) {
			g_vBuf0[i].i = i;
			g_vBuf0[i].f = (float)(i * i);
			g_vBuf1[i].i = i;
			g_vBuf1[i].f = (float)(i * i);
		}
		//入力用のStructuredBufferを作成。
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			//SRVとしてバインド可能。
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
			desc.ByteWidth = NUM_ELEMENTS * sizeof(BufType);
			desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			desc.StructureByteStride = sizeof(BufType);
			m_inputBuffer_0.Create(g_vBuf0, desc);
			m_inputBuffer_1.Create(g_vBuf1, desc);
		}
		//出力用のStructuredBufferを作成。
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;	//UAVとしてバインド可能。
			desc.ByteWidth = NUM_ELEMENTS * sizeof(BufType);
			desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			desc.StructureByteStride = sizeof(BufType);
			m_outputBuffer.Create(NULL, desc);
		}
		//出力結果をCPUで見るためのバッファを作成。
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;	//CPUから読み込み可能に設定する。
			desc.Usage = D3D11_USAGE_STAGING;				//GPUからCPUへのデータコピーをサポートする。
			desc.BindFlags = 0;								//どこにもバインドしない。
			desc.MiscFlags = 0;
			desc.ByteWidth = NUM_ELEMENTS * sizeof(BufType);
			desc.StructureByteStride = sizeof(BufType);
			desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			m_outputBufferCPU.Create(NULL, desc);
		}
		//SRVを作成。
		m_inputSRV_0.Create(m_inputBuffer_0);
		m_inputSRV_1.Create(m_inputBuffer_1);
		//UAVを作成。
		m_outputUAV.Create(m_outputBuffer);
		return true;
	}
	void Update() override
	{

	}
	void Render(CRenderContext& renderContext)
	{
		//コンピュートシェーダーを設定。
		renderContext.CSSetShader(m_csShader);
		//SRVを設定。
		renderContext.CSSetShaderResource(0, m_inputSRV_0);
		renderContext.CSSetShaderResource(1, m_inputSRV_1);
		//UAVを設定。
		renderContext.CSSetUnorderedAccessView(0, m_outputUAV);
		//コンピュートシェーダーを実行。
		renderContext.Dispatch(NUM_ELEMENTS, 1, 1);
		//CPUからアクセスできるバッファにコピー。
		renderContext.CopyResource(m_outputBufferCPU, m_outputBuffer);
		//コンピュートシェーダーの結果を取得。
		CMapper<CStructuredBuffer> mapper(renderContext, m_outputBufferCPU);
		BufType* p = (BufType*)mapper.GetData();
		if (p) {
			for (int i = 0; i < NUM_ELEMENTS; i++) {
				TK_LOG("element ID = %d, p->i = %d, p->f = %f\n", i, p[i].i, p[i].f);
			}
		}
		else {
			TK_LOG("p is null");
		}

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
		NewGO<CComputeTest>(0);
		//初期化に成功。
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();
	
    return 0;
}

