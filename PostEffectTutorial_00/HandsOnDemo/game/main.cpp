/*!
 *@brief	ゲームテンプレート。
 */
#include "stdafx.h"
#include "lib/Camera.h"
#include "lib/Light.h"
#include "lib/RenderTarget.h"
#include "lib/tkPrimitive.h"
#include "game.h"

Game* game;
CRenderTarget* mainRenderTarget;	//!<18-2 メインレンダリングターゲット。
CPrimitive*	quadPrimitive;			//!<18-3 四角形の板ポリプリミティブ。
LPD3DXEFFECT copyEffect;			//!<18-3 コピーを行うシェーダー。
LPD3DXEFFECT monochromeEffect;		//!<18-4 モノクロフィルターをかけるシェーダー。

//-----------------------------------------------------------------------------
// Name: 18-2 メインレンダリングターゲットを初期化。
//-----------------------------------------------------------------------------
void InitMainRenderTarget()
{
	// ハンズオン 1
	mainRenderTarget = new CRenderTarget;
	mainRenderTarget->Create(
		FRAME_BUFFER_WITDH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A8R8G8B8,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0
	);
}
//-----------------------------------------------------------------------------
// Name: 18-3 板ポリの初期化。
//-----------------------------------------------------------------------------
void InitQuadPrimitive()
{
	// ハンズオン 2
	quadPrimitive = new CPrimitive;
	//頂点の構造体。
	struct SVertex {
		float pos[4];	//頂点座標。
		float uv[2];		//UV座標。
	};
	//頂点バッファ。
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの。
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
									//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
	);
}
//-----------------------------------------------------------------------------
// Name: 18-3 メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー。
//-----------------------------------------------------------------------------
void CopyMainRTToCurrentRT()
{
	// ハンズオン 3
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
	);

	LPD3DXEFFECT shader = monochromeEffect;			//18-3 コピーを行うシェーダーを使う場合はこちら。
												//LPD3DXEFFECT shader = monochromeEffect;		//18-4 モノクロフィルターをかける場合はこちらを使用する。
												//シェーダーを設定。
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	shader->SetTexture("g_tex", mainRenderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		quadPrimitive->GetNumPolygon()			//プリミティブの数。
	);
	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}
//-----------------------------------------------------------------------------
// Name: シェーダーをロード。
//-----------------------------------------------------------------------------
void LoadShaders()
{
	// ハンズオン 4
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&copyEffect,
		&compileErrorBuffer
	);

	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/MonochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&monochromeEffect,
		&compileErrorBuffer
	);

	
}
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//18-2 メインレンダリングターゲットを作成する。
	InitMainRenderTarget();
	//18-3 四角形の板ポリプリミティブを作成。
	InitQuadPrimitive();
	//18-3、18-4 シェーダーをロード。
	LoadShaders();
	game = new Game;
	game->Start();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//ハンズオン 1-1 レンダリングターゲットの切り替え。
	//後で戻すために、現在のレンダリングターゲットをバックアップ。
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//レンダリングターゲットを切り替える。
	g_pd3dDevice->SetRenderTarget(
		0,									//何番目のレンダリングターゲットを設定するかの引数。今回は0でいい。
		mainRenderTarget->GetRenderTarget()	//変更するレンダリングターゲット。
	);
	// デプスステンシルバッファも変更する。
	g_pd3dDevice->SetDepthStencilSurface(
		mainRenderTarget->GetDepthStencilBuffer()
	);
	// レンダリングターゲットをクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	// ユニティちゃんなどをレンダリング。
	game->Render();
	
	// ハンズオン 1-2 レンダリングターゲットを戻す。
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	frameBufferRT->Release();
	frameBufferDS->Release();

	// 18-3 オフスクリーンレンダリングした絵をフレームバッファに貼り付ける。
	CopyMainRTToCurrentRT();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();

	
	
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	game->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete game;
	delete g_effectManager;
	delete mainRenderTarget;	//18-2
	delete quadPrimitive;		//18-3
	copyEffect->Release();		//18-3
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
