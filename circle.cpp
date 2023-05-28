//=============================================================================
//
// サークル処理 [circle.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "circle.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "main.h"
#include "player_parts_a.h"
#include "player_parts_b.h"
#include "player_parts_d.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CIRCLE		"data/TEXTURE/circle000.png"	// 読み込むテクスチャファイル名
#define	CIRCLE_SIZE_X		(100.0f)						// ビルボードの幅
#define	CIRCLE_SIZE_Y		(100.0f)						// ビルボードの高さ
#define	VALUE_ROTATE_CIRCLE	(0.05f)							// 移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCircle(LPDIRECT3DDEVICE9 pDevice);
BOOL Init(void);
void Proc(void);
void Gettime(void);
void SetVertexCircle(float fSizeX, float fSizeY);
static	void Bound(void);
static	float radian;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCircle = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCircle = NULL;	// 頂点バッファインターフェースへのポインタ
D3DXMATRIX				g_mtxWorldCircle;			// ワールドマトリックス
CIRCLE				    circleWk[CIRCLE_MAX];		// サークル構造体
float parameter;
float circlesize_max;
float circlesize_min;
float radian_max;
float radian_min;
float DistanceBetweenCirclesize_maxAndCirclesize_min;
float DistanceBetweenCircleradian_maxAndCircleradian_min;
float DownSizeSpeedCircle;

// 時間計測用
DWORD ExecLastTime;
DWORD LastTime;
DWORD CurrentTime;
BOOL bPerf;                 // 高解像度カウンターに対応しているか
LARGE_INTEGER mFreq;        // 1秒間のカウント数
							// マシンの周波数を取得

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCircle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CIRCLE *circle = &circleWk[0];

	// 頂点情報の作成
	MakeVertexCircle(pDevice);

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_CIRCLE,			// ファイルの名前
			&g_pD3DTextureCircle);	// 読み込むメモリー
	}

	circle->Size = 0.0f;
	radian = 35.0f*D3DX_PI/180.0f;

	circle->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	circle->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	circle->rot = D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f);
	circle->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	circle->use = false;
	parameter = 0.0f;

	circlesize_max = sinf(90.0f*D3DX_PI / 180.0f)*2;
	circlesize_min = sinf(35.0f*D3DX_PI / 180.0f)*2;
	radian_max = 145.0f*D3DX_PI / 180.0f;
	radian_min = 35.0f*D3DX_PI / 180.0f;
	DistanceBetweenCircleradian_maxAndCircleradian_min = radian_max - radian_min;
	DistanceBetweenCirclesize_maxAndCirclesize_min = circlesize_max - circlesize_min;
	DownSizeSpeedCircle = DistanceBetweenCircleradian_maxAndCircleradian_min*(145/60);
	
	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	ExecLastTime =
	LastTime = timeGetTime();
	CurrentTime = 0;

	Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCircle(void)
{
	if(g_pD3DTextureCircle != NULL)
	{// テクスチャの開放
		g_pD3DTextureCircle->Release();
		g_pD3DTextureCircle = NULL;
	}

	if(g_pD3DVtxBuffCircle != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffCircle->Release();
		g_pD3DVtxBuffCircle = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCircle(void)
{
	CIRCLE *circle = &circleWk[0];
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);
	circle->scl = D3DXVECTOR3(circle->Size, circle->Size, circle->Size);

	Bound();

	if (circle->use == true)
	{
		circle->rot.y += VALUE_ROTATE_CIRCLE;
	}

	if (GetKeyboardRelease(DIK_RSHIFT))
	{
		circle->use = false;
	}
	
	Proc();
	Gettime();

	PrintDebugProc("[パラメータ  ：(%f :　)]\n", parameter);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxRot, mtxTranslate;
	CIRCLE *circle = &circleWk[0];


	if (circle->use == true)
	{
		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスを取得
		mtxView = GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldCircle);

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, circle->scl.x, circle->scl.y, circle->scl.z);
		D3DXMatrixMultiply(&g_mtxWorldCircle, &g_mtxWorldCircle, &mtxScale);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, circle->rot.y, circle->rot.x, circle->rot.z);
		D3DXMatrixMultiply(&g_mtxWorldCircle, &g_mtxWorldCircle, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, circle->pos.x, circle->pos.y, circle->pos.z);
		D3DXMatrixMultiply(&g_mtxWorldCircle, &g_mtxWorldCircle, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldCircle);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffCircle, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureCircle);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexCircle(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffCircle,	    // 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-CIRCLE_SIZE_X / 2, -CIRCLE_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-CIRCLE_SIZE_X / 2, CIRCLE_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(CIRCLE_SIZE_X / 2, -CIRCLE_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(CIRCLE_SIZE_X / 2, CIRCLE_SIZE_Y / 2, 0.0f);

		//// 法線の設定
		//pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffCircle->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexCircle(float fSizeX, float fSizeY)
{
	{// 頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffCircle->Unlock();
	}
}

//=============================================================================
// サークルの設定
//=============================================================================
void SetCircle(D3DXVECTOR3 pos)
{
	CIRCLE *circle = &circleWk[0];
	
	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		circle->use = true;		// 使用状態へ変更する
		circle->pos = pos;		// 座標をセット
		return;
	}
}

//=============================================================================
// バウンド処理
//=============================================================================
void Bound()
{
	CIRCLE *circle = &circleWk[0];

	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		circle->Size = sinf(radian)*2.0f;

		if (radian >= 145.0f*D3DX_PI / 180.0f)
		{
			radian = 35.0f*D3DX_PI / 180.0f;
		}
	}
}

//=============================================================================
// パラメータ処理
//=============================================================================
void GetParameter()
{
	CIRCLE *circle = &circleWk[0];

	// （キーを押したときのサークルのサイズ）ー（サークルサイズの最小値）
	parameter = circle->Size - circlesize_min;
}

//=============================================================================
// 攻撃できるかのチェック処理
//=============================================================================
bool CanAtack()
{
	bool is_but_position = (circlesize_max - circlesize_min) >= parameter && (parameter > (circlesize_max - circlesize_min) / 2);
	
	return is_but_position == false;
}

//=============================================================================
// 経過時間所得処理
//=============================================================================
void Gettime()
{
	CurrentTime = timeGetTime();
	if ((CurrentTime - LastTime) >= 10)	// 0.01秒ごとに実行
	{
		radian += DownSizeSpeedCircle / 100*2;
		LastTime = CurrentTime;
	}
}

//=============================================================================
// 時間経過処理
//=============================================================================
BOOL Init(void)
{
	LARGE_INTEGER sys;

	bPerf = QueryPerformanceFrequency(&sys);
	if (bPerf)
		return TRUE;

	// 非対応ならtimeGetTime()の精度とする
	sys.QuadPart = 1000;
	return FALSE;
}

void Proc(void)
{
	// 開始時のカウント値を取得
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);

	// 現在のカウント値を取得
	LARGE_INTEGER now;
	if (bPerf) {
		QueryPerformanceCounter(&now);              // 高解像度カウンタに対応している場合
	}
	else {
		now.QuadPart = timeGetTime();               // 高解像度カウンタに対応していない場合
	}

	float time = (float)(now.QuadPart - start.QuadPart) / (float)mFreq.QuadPart;
	PrintDebugProc("経過時間 : %f秒¥n\n", time);
}

//=============================================================================
// サークル取得関数
//=============================================================================
CIRCLE *GetCircle(int no)
{
	return(&circleWk[no]);
}
