//=============================================================================
//
// �^�[�Q�b�g���� [target.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "target.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "main.h"
#include "player_parts_a.h"
#include "player_parts_b.h"
#include "player_parts_d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TARGET		"data/TEXTURE/target000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TARGET_SIZE_X		(100.0f)						// �r���{�[�h�̕�
#define	TARGET_SIZE_Y		(100.0f)						// �r���{�[�h�̍���
#define	VALUE_ROTATE_TARGET	(0.05f)							// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTarget(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTarget(float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTarget = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTarget = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
D3DXMATRIX				g_mtxWorldTarget;			// ���[���h�}�g���b�N�X
TARGET				    targetWk[TARGET_MAX];		// �^�[�Q�b�g�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTarget(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[0];

	// ���_���̍쐬
	MakeVertexTarget(pDevice);

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TARGET,			// �t�@�C���̖��O
			&g_pD3DTextureTarget);	// �ǂݍ��ރ������[
	}

	target->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	target->scl = D3DXVECTOR3(1.30f, 1.30f, 1.30f);
	target->rot = D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f);
	target->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	target->use = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTarget(void)
{
	if(g_pD3DTextureTarget != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTarget->Release();
		g_pD3DTextureTarget = NULL;
	}

	if(g_pD3DVtxBuffTarget != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffTarget->Release();
		g_pD3DVtxBuffTarget = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTarget(void)
{
	TARGET *target = &targetWk[0];
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);

	if (target->use == true)
	{
		target->rot.y += VALUE_ROTATE_TARGET;
	}

	if (GetKeyboardRelease(DIK_RSHIFT))
	{
		target->use = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxRot, mtxTranslate;
	TARGET *target = &targetWk[0];


	if (target->use == true)
	{
		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X���擾
		mtxView = GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldTarget);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, target->scl.x, target->scl.y, target->scl.z);
		D3DXMatrixMultiply(&g_mtxWorldTarget, &g_mtxWorldTarget, &mtxScale);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, target->rot.y, target->rot.x, target->rot.z);
		D3DXMatrixMultiply(&g_mtxWorldTarget, &g_mtxWorldTarget, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, target->pos.x, target->pos.y, target->pos.z);
		D3DXMatrixMultiply(&g_mtxWorldTarget, &g_mtxWorldTarget, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTarget);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffTarget, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureTarget);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexTarget(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffTarget,	    // ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTarget->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-TARGET_SIZE_X / 2, -TARGET_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-TARGET_SIZE_X / 2, TARGET_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TARGET_SIZE_X / 2, -TARGET_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TARGET_SIZE_X / 2, TARGET_SIZE_Y / 2, 0.0f);

		//// �@���̐ݒ�
		//pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		g_pD3DVtxBuffTarget->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexTarget(float fSizeX, float fSizeY)
{
	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTarget->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTarget->Unlock();
	}
}

//=============================================================================
// �^�[�Q�b�g�̐ݒ�
//=============================================================================
void SetTarget(D3DXVECTOR3 pos)
{
	TARGET *target = &targetWk[0];

	
	for (int i = 0; i < TARGET_MAX; i++)
	{
		target->use = true;		// �g�p��Ԃ֕ύX����
		target->pos = pos;		// ���W���Z�b�g

		return;
	}
}

//=============================================================================
// �^�[�Q�b�g�擾�֐�
//=============================================================================
TARGET *GetTarget(int no)
{
	return(&targetWk[no]);
}
