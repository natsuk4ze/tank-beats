//=============================================================================
//
// �e���� [shadow.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "shadow.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SHADOW_SIZE_X		(50.0f)							// �e�̕�
#define	SHADOW_SIZE_Z		(50.0f)							// �e�̍���

#define	MAX_SHADOW			(128)							// �e�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	bool bUse;				// �g�p���Ă��邩�ǂ���
} SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureShadow = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffShadow = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

SHADOW					g_aShadow[MAX_SHADOW];			// �e���[�N
SHADOW					shadowWk[SHADOW_MAX];		    // �V���h�E�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitShadow(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexShadow(pDevice);

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SHADOW,				  // �t�@�C���̖��O
			&g_pD3DTextureShadow);		  // �ǂݍ��ރ������[
	}


	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	if(g_pD3DTextureShadow != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureShadow->Release();
		g_pD3DTextureShadow = NULL;
	}

	if(g_pD3DVtxBuffShadow != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffShadow->Release();
		g_pD3DVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
#if 0
	D3DXQUATERNION quat;
	D3DXVECTOR3 vecUpObj, vecUpField, outVec;
	float fDotProduct,fRot;
#endif

	// ���Z�����i���F�ɋ߂����Ă����j
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// ���� = �]����(DEST) - �]����(SRC)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//(���ɖ߂��ĂĂ���)

	// Z��r�Ȃ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(g_aShadow[nCntShadow].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

#if 0
			// ��]�𔽉f
			D3DXQuaternionIdentity(&quat);

			vecUpObj = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �I�u�W�F�N�g�̏����
			vecUpField = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �n�ʂ̖@��

			// �I�u�W�F�N�g�̏�����ƒn�ʂ̖@���̊O�ς����]�������߂�
			D3DXVec3Cross(&outVec, &vecUpObj, &vecUpField);

			// �I�u�W�F�N�g�̏�����ƒn�ʂ̖@���̂Ȃ��p�����߂�
			fDotProduct = D3DXVec3Dot(&vecUpObj, &vecUpField);
			fRot = acosf(fDotProduct / (sqrtf(vecUpObj.x * vecUpObj.x + vecUpObj.y * vecUpObj.y + vecUpObj.z * vecUpObj.z)
														* sqrtf(vecUpField.x * vecUpField.x + vecUpField.y * vecUpField.y + vecUpField.z * vecUpField.z)));

			// ��]���ƂȂ��p����N�H�[�^�j�I�������߁A��]�}�g���b�N�X���Z�o
			D3DXQuaternionRotationAxis(&quat, &outVec, fRot);
			D3DXMatrixRotationQuaternion(&mtxRot, &quat);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);
#endif
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aShadow[nCntShadow].pos.x,
													g_aShadow[nCntShadow].pos.y,
													g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld,
										&g_aShadow[nCntShadow].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
			pDevice->SetStreamSource(0, g_pD3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntShadow * 4), NUM_POLYGON);
		}
	}

	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffShadow,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f);
			pVtx[1].diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f);
			pVtx[2].diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f);
			pVtx[3].diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxShadow * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[1].vtx = D3DXVECTOR3(fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[2].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, -fSizeZ / 2);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, 0.0f, -fSizeZ / 2);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorShadow(int nIdxShadow, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxShadow * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// �e�̍쐬
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ)
{
	int nIdxShadow = -1;

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aShadow[nCntShadow].bUse = true;

			SetVertexShadow(nCntShadow, fSizeX, fSizeZ);

			nIdxShadow = nCntShadow;
			break;
		}
	}

	return nIdxShadow;
}

//=============================================================================
// �e�̔j��
//=============================================================================
void ReleaseShadow(int nIdxShadow)
{
	if(nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].bUse = false;
	}
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}

//=============================================================================
// �V���h�E�擾�֐�
//=============================================================================
SHADOW *GetShadow(int no)
{
	return(&shadowWk[no]);
}

