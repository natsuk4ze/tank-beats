//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "life.h"
#include "player_parts_a.h"
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/heart000.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME_LIFE	"data/TEXTURE/frame_life.png"	// 読み込むテクスチャファイル名
#define	LIFE_SIZE_X			(35.0f)							// ライフの数字の幅
#define	LIFE_SIZE_Y			(45.0f)							// ライフの数字の高さ
#define	LIFE_INTERVAL_X		(0.0f)							// ライフの数字の表示間隔

#define	NUM_PLACE			(8)								// ライフの桁数

#define	LIFE_POS_X			(20.0f)							// ライフの表示基準位置Ｘ座標
#define	LIFE_POS_Y			(25.0f)							// ライフの表示基準位置Ｙ座標

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
void SetTextureLife(int nIdx);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLife[2] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffLife = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				g_posLife;						// 位置
D3DXVECTOR3				g_rotLife;						// 向き

int						g_nLife;						// ライフ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posLife = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotLife = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ライフの初期化
	g_nLife = NUM_PLACE;

	// 頂点情報の作成
	MakeVertexLife(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_LIFE,			// ファイルの名前
								&g_pD3DTextureLife[0]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME_LIFE,			// ファイルの名前
								&g_pD3DTextureLife[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	if(g_pD3DTextureLife[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureLife[0]->Release();
		g_pD3DTextureLife[0] = NULL;
	}
	if(g_pD3DTextureLife[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureLife[1]->Release();
		g_pD3DTextureLife[1] = NULL;
	}

	if(g_pD3DVtxBuffLife != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffLife->Release();
		g_pD3DVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pD3DVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureLife[0]);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < g_nLife; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureLife[1]);

	//// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_2D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffLife,							// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(LIFE_POS_X + nCntPlace * LIFE_SIZE_X + LIFE_INTERVAL_X, LIFE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LIFE_POS_X + nCntPlace * (LIFE_INTERVAL_X + LIFE_SIZE_X) + LIFE_SIZE_X, LIFE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(LIFE_POS_X + nCntPlace * LIFE_SIZE_X + LIFE_INTERVAL_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LIFE_POS_X + nCntPlace * (LIFE_INTERVAL_X + LIFE_SIZE_X) + LIFE_SIZE_X, LIFE_POS_Y + LIFE_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(LIFE_POS_X - 15, LIFE_POS_Y - 25, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(LIFE_POS_X + (LIFE_INTERVAL_X + LIFE_SIZE_X) * NUM_PLACE + 15, LIFE_POS_Y - 25, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(LIFE_POS_X - 15, LIFE_POS_Y + 55, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(LIFE_POS_X + (LIFE_INTERVAL_X + LIFE_SIZE_X) * NUM_PLACE + 15, LIFE_POS_Y + 55, 0.0f);

		// rhwの設定
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffLife->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureLife(int nIdx)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffLife->Unlock();
}

//=============================================================================
// ライフの変更
//=============================================================================
void ChangeLife(int nValue)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	g_nLife += nValue;

	if (g_nLife == 0)
	{
		player_parts_a->use = false;
	}

	if(g_nLife < 0)
	{
		g_nLife = 0;
	}
}

