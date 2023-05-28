//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "billboard.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "main.h"
#include "player_parts_a.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BILLBOARD		"data/TEXTURE/billboard003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BILLBOARD_SIZE_X		(20.0f)							// �r���{�[�h�̕�
#define	BILLBOARD_SIZE_Y		(20.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBillboard(float fSizeX, float fSizeY);
static	void Bound(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBillboard = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBillboard = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldBillboard;			// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posBillboard;					// �ʒu
D3DXVECTOR3				g_sclBillboard;					// �X�P�[��
D3DXVECTOR3				g_moveBillboard;				// �ړ���
int						g_nIdxShadowBillboard;			// �eID
bool					g_bEnableGravity = false;		// �d�͂�L���ɂ��邩�ǂ���
float bound;
float radian;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBillboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexBillboard(pDevice);

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BILLBOARD,			// �t�@�C���̖��O
			&g_pD3DTextureBillboard);	// �ǂݍ��ރ������[
	}


	g_posBillboard = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_sclBillboard = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_moveBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_bEnableGravity = false;
	bound = 0;
	radian = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	if(g_pD3DTextureBillboard != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBillboard->Release();
		g_pD3DTextureBillboard = NULL;
	}

	if(g_pD3DVtxBuffBillboard != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBillboard->Release();
		g_pD3DVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	if (player_parts_a->use == true)
	{
		g_posBillboard = D3DXVECTOR3(player_parts_a->pos.x, g_posBillboard.y + g_moveBillboard.y, player_parts_a->pos.z);

		Bound();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);


	if (player_parts_a->use == true)
	{
		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X���擾
		mtxView = GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldBillboard);

		// �|���S���𐳖ʂɌ�����
		g_mtxWorldBillboard._11 = mtxView._11;
		g_mtxWorldBillboard._12 = mtxView._21;
		g_mtxWorldBillboard._13 = mtxView._31;
		g_mtxWorldBillboard._21 = mtxView._12;
		g_mtxWorldBillboard._22 = mtxView._22;
		g_mtxWorldBillboard._23 = mtxView._32;
		g_mtxWorldBillboard._31 = mtxView._13;
		g_mtxWorldBillboard._32 = mtxView._23;
		g_mtxWorldBillboard._33 = mtxView._33;

		//D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);	//�t�s����쐬
		//g_mtxWorldBillboard._41 = 0.0f;
		//g_mtxWorldBillboard._42 = 0.0f;
		//g_mtxWorldBillboard._43 = 0.0f;

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, g_sclBillboard.x,
			g_sclBillboard.y,
			g_sclBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard,
			&g_mtxWorldBillboard, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_posBillboard.x,
			g_posBillboard.y,
			g_posBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard,
			&g_mtxWorldBillboard, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBillboard);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffBillboard,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBillboard(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBillboard->Unlock();
	}
}

//=============================================================================
// �o�E���h����
//=============================================================================
void Bound()
{
	for (int i = 0; i < BILLBOARD_MAX; i++)
	{
		g_moveBillboard.y = sinf(radian)*0.30f;

		// ���n�Ō���
		if (radian >= 360.0f)
		{
			radian = 0.0f;
		}

	}

	radian += 0.10f;
}
