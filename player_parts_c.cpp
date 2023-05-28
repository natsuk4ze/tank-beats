//=============================================================================
//
// �v���C���[�p�[�cc���� [player_parts_c.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "player_parts_a.h"
#include "player_parts_c.h"
#include "player_parts_b.h"
#include "input.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME_PLAYER_PARTS_C "data/MODEL/tank002/tank002_c.x"

#define TEXTURE_FILENAME	"data/TEXTURE/tank_skin002.jpg"

#define	VALUE_MOVE		(5.0f)											// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)								// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_Parts_c;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshPlayer_Parts_c;			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_Parts_c;		// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatPlayer_Parts_c;			// �}�e���A�����̐�
static	D3DXMATRIX	g_mtxWorld_c;						// ���[���h�}�g���b�N�X

PLAYER_PARTS_C	    player_parts_cWk[PLAYER_PARTS_C_MAX];	// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer_Parts_c(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_PARTS_C *player_parts_c = &player_parts_cWk[0];

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	player_parts_c->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_c->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_c->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	g_pD3DTexturePlayer_Parts_c = NULL;
	g_pD3DXMeshPlayer_Parts_c = NULL;
	g_pD3DXBuffMatPlayer_Parts_c = NULL;
	g_nNumMatPlayer_Parts_c = 0;


	// �p�[�cb��X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_GAME_PLAYER_PARTS_C,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&g_pD3DXBuffMatPlayer_Parts_c,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&g_nNumMatPlayer_Parts_c,		// D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshPlayer_Parts_c)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}


#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTexturePlayer_Parts_c);	// �ǂݍ��ރ������[


#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer_Parts_c(void)
{
	if (g_pD3DTexturePlayer_Parts_c != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_Parts_c->Release();
		g_pD3DTexturePlayer_Parts_c = NULL;
	}

	if (g_pD3DXMeshPlayer_Parts_c != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_Parts_c->Release();
		g_pD3DXMeshPlayer_Parts_c = NULL;
	}

	if (g_pD3DXBuffMatPlayer_Parts_c != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_Parts_c->Release();
		g_pD3DXBuffMatPlayer_Parts_c = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer_Parts_c(void)
{

}

//=============================================================================
// �p�[�cc�`�揈��
//=============================================================================
void DrawPlayer_Parts_c(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER_PARTS_C *player_parts_c = &player_parts_cWk[0];
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorld_c);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&g_mtxWorld_c, &g_mtxWorld_c, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&g_mtxWorld_c, &g_mtxWorld_c, &mtxRot);

	// �ړ��𔽉f(��I�u�W�F�N�g����l����)
	D3DXMatrixTranslation(&mtxTranslate, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&g_mtxWorld_c, &g_mtxWorld_c, &mtxTranslate);

	//�e�̃��[���h�}�g���b�N�X�Ɏ����̃��[���h�}�g���b�N�X��������
	D3DXMatrixMultiply(&g_mtxWorld_c, &g_mtxWorld_c, GetPlayer_Parts_bWorldMatrix());

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_c);

	// ���݂̃}�e���A�����擾(���ɖ߂����߂̃o�b�N�A�b�v)
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_Parts_c->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_Parts_c; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayer_Parts_c);

		// �`��
		g_pD3DXMeshPlayer_Parts_c->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// �v���C���[�p�[�cc�擾�֐�
//=============================================================================
PLAYER_PARTS_C *GetPlayer_Parts_c(int no)
{
	return(&player_parts_cWk[no]);
}
