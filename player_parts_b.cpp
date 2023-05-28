//=============================================================================
//
// �v���C���[�p�[�cb���� [player_parts_b.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "player_parts_b.h"
#include "player_parts_a.h"
#include "player_parts_d.h"
#include "bullet.h"
#include "input.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "particle.h"
#include "player.h"
#include "target.h"
#include "enemy.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME_PLAYER_PARTS_B "data/MODEL/tank002/tank002_b.x"
#define TEXTURE_FILENAME	"data/TEXTURE/tank_skin002.jpg"

#define	VALUE_MOVE		(5.0f)							// �ړ���
#define	VALUE_ROTATE_A	(D3DX_PI * 0.01f)				// �e�̉�]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_Parts_b;			// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshPlayer_Parts_b;				// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_Parts_b;			// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatPlayer_Parts_b;				// �}�e���A�����̐�

static D3DXMATRIX	g_mtxWorld_b;							// ���[���h�}�g���b�N�X

PLAYER_PARTS_B		player_parts_bWk[PLAYER_PARTS_B_MAX];	// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer_Parts_b(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_PARTS_B *player_parts_b = &player_parts_bWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	player_parts_b->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_b->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	player_parts_b->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	player_parts_b->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_pD3DTexturePlayer_Parts_b = NULL;
	g_pD3DXMeshPlayer_Parts_b = NULL;
	g_pD3DXBuffMatPlayer_Parts_b = NULL;
	g_nNumMatPlayer_Parts_b = 0;

	player_parts_b->Angle = 0;

	// �p�[�cb��X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_GAME_PLAYER_PARTS_B,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&g_pD3DXBuffMatPlayer_Parts_b,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&g_nNumMatPlayer_Parts_b,		// D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshPlayer_Parts_b)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}


#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTexturePlayer_Parts_b);	// �ǂݍ��ރ������[


#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer_Parts_b(void)
{
	if (g_pD3DTexturePlayer_Parts_b != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_Parts_b->Release();
		g_pD3DTexturePlayer_Parts_b = NULL;
	}

	if (g_pD3DXMeshPlayer_Parts_b != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_Parts_b->Release();
		g_pD3DXMeshPlayer_Parts_b = NULL;
	}

	if (g_pD3DXBuffMatPlayer_Parts_b != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_Parts_b->Release();
		g_pD3DXBuffMatPlayer_Parts_b = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer_Parts_b(void)
{
	PLAYER_PARTS_B *player_parts_b = &player_parts_bWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);
	TARGET *target = GetTarget(0);
	ENEMY  *enemy = GetEnemy(0);

	player_parts_b->pos = GetPartPos(player_parts_a->pos + player_parts_b->move, player_parts_a->rot, D3DXVECTOR3(0.0f, 15.0f, 0.0f));
	player_parts_b->Angle = atan2f((player_parts_b->pos.z - target->pos.z), (player_parts_b->pos.x - target->pos.x))*180.0f / D3DX_PI;
	player_parts_b->targetdistance = hypotf(powf((target->pos.x - player_parts_b->pos.x), 2.0f), (powf((target->pos.z - player_parts_b->pos.z), 2.0f)));

	//��]
	if (GetKeyboardPress(DIK_RIGHT))
	{
		player_parts_b->rot.y += VALUE_ROTATE_B;
	}

	else if (IsButtonPressed(0, BUTTON_START))
	{
		player_parts_b->rot.y += VALUE_ROTATE_B;
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		player_parts_b->rot.y -= VALUE_ROTATE_B;
	}

	else if (IsButtonPressed(0, BUTTON_M))
	{
		player_parts_b->rot.y -= VALUE_ROTATE_B;
	}
}

//=============================================================================
// �p�[�cb�`�揈��
//=============================================================================
void DrawPlayer_Parts_b(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate,test;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER_PARTS_B *player_parts_b = &player_parts_bWk[0];
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorld_b);
	D3DXMatrixIdentity(&test);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&g_mtxWorld_b, &g_mtxWorld_b, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player_parts_b->rot.y, player_parts_b->rot.x, player_parts_b->rot.z);
	D3DXMatrixMultiply(&g_mtxWorld_b, &g_mtxWorld_b, &mtxRot);

	// �ړ��𔽉f(��I�u�W�F�N�g����l����)
	D3DXMatrixTranslation(&mtxTranslate, player_parts_b->move.x, player_parts_b->move.y, player_parts_b->move.z);
	D3DXMatrixMultiply(&g_mtxWorld_b, &g_mtxWorld_b, &mtxTranslate);

	//�e�̃��[���h�}�g���b�N�X�Ɏ����̃��[���h�}�g���b�N�X��������
	D3DXMatrixMultiply(&g_mtxWorld_b, &g_mtxWorld_b, GetPlayer_Parts_aWorldMatrix());

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_b);

	// ���݂̃}�e���A�����擾(���ɖ߂����߂̃o�b�N�A�b�v)
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_Parts_b->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_Parts_b; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayer_Parts_b);

		// �`��
		g_pD3DXMeshPlayer_Parts_b->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// �v���C���[�p�[�cb�擾�֐�
//=============================================================================
PLAYER_PARTS_B *GetPlayer_Parts_b(int no)
{
	return(&player_parts_bWk[no]);
}

//=============================================================================
// �}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX *GetPlayer_Parts_bWorldMatrix(void)
{
	return(&g_mtxWorld_b);
}
