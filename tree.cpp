//=============================================================================
//
// �؏��� [tree.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "tree.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TREE		"data/TEXTURE/tree000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TREE_WIDTH			(50.0f)							// �e�̔��a��
#define	TREE_HEIGHT			(80.0f)							// �e�̔��a��
#define	VALUE_MOVE_TREE		(3.00f)							// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTree(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTree(int nIdxTree, float fWidth, float fHeight);
void SetColorTree(int nIdxTree, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureTree[5] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTree = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

TREE					g_aTree[MAX_TREE];				// �؃��[�N
bool					g_bAlpaTest;					// �A���t�@�e�X�gON/OFF
int						g_nAlpha;						// �A���t�@�e�X�g��臒l

const char *g_aFileName[] =
{
	"data/TEXTURE/tree001.png",
	"data/TEXTURE/tree002.png",
	"data/TEXTURE/tree003.png",
	"data/TEXTURE/tree004.png",
	"data/TEXTURE/tree005.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTree(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexTree(pDevice);

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		for (int nCntTex = 0; nCntTex < 5; nCntTex++)
		{
			D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
				g_aFileName[nCntTex],			// �t�@�C���̖��O
				&g_apD3DTextureTree[nCntTex]);	// �ǂݍ��ރ������[
		}
	}


	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		g_aTree[nCntTree].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTree[nCntTree].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aTree[nCntTree].fWidth = TREE_WIDTH;
		g_aTree[nCntTree].fHeight = TREE_HEIGHT;
		g_aTree[nCntTree].bUse = false;
	}

	g_bAlpaTest = true;
	g_nAlpha = 0x0;

	// �؂̐ݒ�
	SetTree(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(200.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(0.0f, 0.0f, -200.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTree(void)
{
	for(int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if(g_apD3DTextureTree[nCntTex] != NULL)
		{// �e�N�X�`���̊J��
			g_apD3DTextureTree[nCntTex]->Release();
			g_apD3DTextureTree[nCntTex] = NULL;
		}
	}

	if(g_pD3DVtxBuffTree != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffTree->Release();
		g_pD3DVtxBuffTree = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTree(void)
{

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(g_aTree[nCntTree].bUse)
		{
			// �e�̈ʒu�ݒ�
			SetPositionShadow(g_aTree[nCntTree].nIdxShadow, D3DXVECTOR3(g_aTree[nCntTree].pos.x, 0.1f, g_aTree[nCntTree].pos.z));
		}
	}

	// �A���t�@�e�X�gON/OFF
	if(GetKeyboardTrigger(DIK_F1))
	{
		g_bAlpaTest = g_bAlpaTest ? false: true;
	}

	// �A���t�@�e�X�g��臒l�ύX
	if(GetKeyboardPress(DIK_I))
	{
		g_nAlpha--;
		if(g_nAlpha < 0)
		{
			g_nAlpha = 0;
		}
	}

	if(GetKeyboardPress(DIK_K))
	{
		g_nAlpha++;
		if(g_nAlpha > 255)
		{
			g_nAlpha = 255;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTree(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���e�X�g�ݒ�
	if(g_bAlpaTest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, g_nAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(g_aTree[nCntTree].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aTree[nCntTree].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&g_aTree[nCntTree].mtxWorld, NULL, &mtxView);
			g_aTree[nCntTree].mtxWorld._41 = 0.0f;
			g_aTree[nCntTree].mtxWorld._42 = 0.0f;
			g_aTree[nCntTree].mtxWorld._43 = 0.0f;
#else
			g_aTree[nCntTree].mtxWorld._11 = mtxView._11;
			g_aTree[nCntTree].mtxWorld._12 = mtxView._21;
			g_aTree[nCntTree].mtxWorld._13 = mtxView._31;
			g_aTree[nCntTree].mtxWorld._21 = mtxView._12;
			g_aTree[nCntTree].mtxWorld._22 = mtxView._22;
			g_aTree[nCntTree].mtxWorld._23 = mtxView._32;
			g_aTree[nCntTree].mtxWorld._31 = mtxView._13;
			g_aTree[nCntTree].mtxWorld._32 = mtxView._23;
			g_aTree[nCntTree].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aTree[nCntTree].scl.x,
											g_aTree[nCntTree].scl.y,
											g_aTree[nCntTree].scl.z);
			D3DXMatrixMultiply(&g_aTree[nCntTree].mtxWorld, &g_aTree[nCntTree].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aTree[nCntTree].pos.x,
													g_aTree[nCntTree].pos.y,
													g_aTree[nCntTree].pos.z);
			D3DXMatrixMultiply(&g_aTree[nCntTree].mtxWorld, &g_aTree[nCntTree].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aTree[nCntTree].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffTree, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureTree[nCntTree % 5]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntTree * 4), NUM_POLYGON);
		}
	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexTree(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_TREE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffTree,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-TREE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-TREE_WIDTH / 2.0f, TREE_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(TREE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(TREE_WIDTH / 2.0f, TREE_HEIGHT, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTree->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTree(int nIdxTree, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxTree * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTree->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorTree(int nIdxTree, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxTree * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTree->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxTree = -1;

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(!g_aTree[nCntTree].bUse)
		{
			g_aTree[nCntTree].pos = pos;
			g_aTree[nCntTree].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aTree[nCntTree].fWidth = fWidth;
			g_aTree[nCntTree].fHeight = fHeight;
			g_aTree[nCntTree].bUse = true;

			// ���_���W�̐ݒ�
			SetVertexTree(nCntTree, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorTree(nCntTree, col);

			// �e�̐ݒ�
			g_aTree[nCntTree].nIdxShadow = CreateShadow(g_aTree[nCntTree].pos, g_aTree[nCntTree].fWidth, g_aTree[nCntTree].fWidth);

			nIdxTree = nCntTree;

			break;
		}
	}

	return nIdxTree;
}

//=============================================================================
// �؂��擾
//=============================================================================
TREE *GetTree(void)
{
	return &g_aTree[0];
}
