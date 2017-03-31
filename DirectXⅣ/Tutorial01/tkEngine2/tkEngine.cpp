/*!
 *@brief	エンジン
 */
#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/tkEngine.h"

namespace tkEngine2 {
	CEngine::CEngine()
	{

	}
	CEngine::~CEngine()
	{

	}
	bool CEngine::Init( const SInitParam& initParam )
	{
		//ウィンドウ初期化。
		if(!InitWindow(initParam)){
			return false;
		}
		//DirectX初期化。
		if(InitDirectX(initParam)){
			return false;
		}
		return true;
	}
	bool CEngine::InitWindow( const SInitParam& initParam )
	{
		TK_ASSERT(initParam.screenHeight != 0, "screenHeight is zero");
		TK_ASSERT(initParam.screenWidth != 0, "screenWidth is zero");
		
		m_screenHeight = initParam.screenHeight;
		m_screenWidth = initParam.screenWidth;
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			TEXT("D3D Tutorial"), nullptr
		};
		RegisterClassEx(&wc);
		// Create the application's window
		m_hWnd = CreateWindow(TEXT("D3D Tutorial"), TEXT("D3D Tutorial 06: Meshes"),
			WS_OVERLAPPEDWINDOW, 0, 0, m_screenWidth, m_screenHeight,
			nullptr, nullptr, wc.hInstance, nullptr);

		return m_hWnd != nullptr;
	}
	bool CEngine::InitDirectX( const SInitParam& initParam )
	{
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
   		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_DRIVER_TYPE driverTypes[] =
	    {
	        D3D_DRIVER_TYPE_HARDWARE,
	        D3D_DRIVER_TYPE_WARP,
	        D3D_DRIVER_TYPE_REFERENCE,
	    };

	    D3D_FEATURE_LEVEL featureLevels[] =
	    {
	        D3D_FEATURE_LEVEL_11_0,
	        D3D_FEATURE_LEVEL_10_1,
	        D3D_FEATURE_LEVEL_10_0,
	    };
		UINT numFeatureLevels = ARRAYSIZE( featureLevels );
		
		m_frameBufferWidth = initParam.frameBufferWidth;
		m_frameBufferHeight = initParam.frameBufferHeight;
		//スワップチェインを作成。
		DXGI_SWAP_CHAIN_DESC sd;
	    ZeroMemory( &sd, sizeof( sd ) );
	    sd.BufferCount = 1;							//スワップチェインのバッファ数。通常は１。
	    sd.BufferDesc.Width = m_frameBufferWidth;	//フレームバッファの幅。
	    sd.BufferDesc.Height = m_frameBufferHeight;	//フレームバッファの高さ。
	    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//フレームバッファのフォーマット。R8G8B8A8の32bit。
	    sd.BufferDesc.RefreshRate.Numerator = 60;			//モニタのリフレッシュレート。(バックバッファとフロントバッファを入れ替えるタイミングとなる。)
	    sd.BufferDesc.RefreshRate.Denominator = 1;			//@todo なんやろこれ？たぶん２にしたら30fpsになる。あとで試す。
	    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//サーフェスまたはリソースを出力レンダー ターゲットとして使用します。
	    sd.OutputWindow = m_hWnd;
	    sd.SampleDesc.Count = 1;							//ピクセル単位のマルチサンプリングの数。MSAAはなし。
		sd.SampleDesc.Quality = 0;							//MSAAなし。

		//すべてのドライバタイプでスワップチェインの作成を試す。
		HRESULT hr = E_FAIL;
		for (auto driverType : driverTypes) {
			m_driverType = driverType;
			hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
			if (SUCCEEDED(hr)) {
				//スワップチェインを作成できたのでループを抜ける。
				break;
			}
		}
		if (FAILED(hr)) {
			//スワップチェインを作成できなかった。
			return false;
		}
		//書き込み先になるレンダリングターゲットを作成。
		ID3D11Texture2D* pBackBuffer = NULL;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}

		hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		if (FAILED(hr)) {
			return false;
		}

		m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

		//ビューポートを設定。
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)m_frameBufferWidth;
		vp.Height = (FLOAT)m_frameBufferHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pImmediateContext->RSSetViewports(1, &vp);

		return true;
	}
	void CEngine::Final()
	{
	}
	void CEngine::RunGameLoop()
	{
	}
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return E_FAIL;
	}
}