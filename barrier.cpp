//=============================================================================
//
// �o���A�|���� [barrier.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "barrier.h"
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
#define	TEXTURE_BARRIER		"data/TEXTURE/barrier000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BARRIER_SIZE_X		(100.0f)						// �o���A�|�̕�
#define	BARRIER_SIZE_Y		(100.0f)						// �o���A�|�̍���
#define	VALUE_ROTATE_BARRIER	(0.05f)						// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBarrier(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBarrier(float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBarrier = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBarrier = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
D3DXMATRIX				g_mtxWorldBarrier;				// ���[���h�}�g���b�N�X
BARRIER				    barrierWk[BARRIER_MAX];			// �o���A�|�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBarrier(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BARRIER *barrier = &barrierWk[0];

	// ���_���̍쐬
	MakeVertexBarrier(pDevice);

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BARRIER,			// �t�@�C���̖��O
			&g_pD3DTextureBarrier);	// �ǂݍ��ރ������[
	}

	barrier->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	barrier->scl = D3DXVECTOR3(1.30f, 1.30f, 1.30f);
	barrier->rot = D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f);
	barrier->use = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBarrier(void)
{
	if (g_pD3DTextureBarrier != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBarrier->Release();
		g_pD3DTextureBarrier = NULL;
	}

	if (g_pD3DVtxBuffBarrier != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBarrier->Release();
		g_pD3DVtxBuffBarrier = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBarrier(void)
{
	BARRIER *barrier = &barrierWk[0];

	for (int nCntBarrier = 0; nCntBarrier < BARRIER_MAX; nCntBarrier++)
	{
		if (barrier->use == true)
		{
			barrier->scl.x = sinf(barrier->radian) * 2.0f; //�o���A�|�̊g��
			barrier->scl.y = sinf(barrier->radian) * 2.0f; //�o���A�|�̊g��
			barrier->scl.z = sinf(barrier->radian) * 2.0f; //�o���A�|�̊g��

			if (barrier->radian >= D3DX_PI)
			{
				barrier->radian = 0.0f;
				barrier->use = false;
			}

			barrier->radian += 0.20f;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxRot, mtxTranslate;
	BARRIER *barrier = &barrierWk[0];


	if (barrier->use == true)
	{
		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �r���[�}�g���b�N�X���擾
		mtxView = GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldBarrier);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, barrier->scl.x, barrier->scl.y, barrier->scl.z);
		D3DXMatrixMultiply(&g_mtxWorldBarrier, &g_mtxWorldBarrier, &mtxScale);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, barrier->rot.y, barrier->rot.x, barrier->rot.z);
		D3DXMatrixMultiply(&g_mtxWorldBarrier, &g_mtxWorldBarrier, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, barrier->pos.x, barrier->pos.y, barrier->pos.z);
		D3DXMatrixMultiply(&g_mtxWorldBarrier, &g_mtxWorldBarrier, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBarrier);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBarrier, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBarrier);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexBarrier(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBarrier,	    // ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-BARRIER_SIZE_X / 2, -BARRIER_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BARRIER_SIZE_X / 2, BARRIER_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BARRIER_SIZE_X / 2, -BARRIER_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BARRIER_SIZE_X / 2, BARRIER_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffBarrier->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBarrier(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBarrier->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBarrier->Unlock();
	}
}

//=============================================================================
// �o���A�|�̐ݒ�
//=============================================================================
void SetBarrier(D3DXVECTOR3 pos)
{
	BARRIER *barrier = &barrierWk[0];


	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		if (barrier->use == false)	// ���g�p��Ԃ̃o���b�g��������
		{
			barrier->use = true;		// �g�p��Ԃ֕ύX����
			barrier->pos = pos;		// ���W���Z�b�g

			return;				    // 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���A�|�擾�֐�
//=============================================================================
BARRIER *GetBarrier(int no)
{
	return(&barrierWk[no]);
}
