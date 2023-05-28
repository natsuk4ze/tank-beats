//=============================================================================
//
// �v���C���[�p�[�ca���� [player_parts_a.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "player_parts_a.h"
#include "player_parts_b.h"
#include "player_parts_d.h"
#include "bullet.h"
#include "input.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "particle.h"
#include "input.h"
#include "enemy.h"
#include "barrier.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME_PLAYER_PARTS_A	  "data/MODEL/tank002/tank002_a.x"	// �ǂݍ��ރ��f����
#define TEXTURE_FILENAME	"data/TEXTURE/tank_skin002.jpg"

#define	VALUE_MOVE		    (5.0f)										// �ړ���
#define	RATE_MOVE_MODEL		(0.20f)										// �ړ������W��
#define	RATE_ROTATE_PLAYER	(0.10f)										// ��]�����W��
#define VALUE_MOVE_PLAYER	(0.050f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePayer_Parts_a;				// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshPayer_Parts_a;				// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPayer_Parts_a;			// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatPayer_Parts_a;					// �}�e���A�����̐�
static  D3DXMATRIX	g_mtxWorld;								// ���[���h�}�g���b�N�X
PLAYER_PARTS_A		player_parts_aWk[PLAYER_PARTS_A_MAX];	// �v���C���[�\����

static	int			g_nIdxShadow;							// �eID
static	float		g_fSizeShadow;							// �e�̃T�C�Y
static	D3DXCOLOR	g_colShadow;							// �e�̐F

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer_Parts_a(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_PARTS_A *player_parts_a = &player_parts_aWk[0];

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	player_parts_a->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	player_parts_a->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_a->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	player_parts_a->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_a->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_pD3DTexturePayer_Parts_a = NULL;
	g_pD3DXMeshPayer_Parts_a = NULL;
	g_pD3DXBuffMatPayer_Parts_a = NULL;
	g_nNumMatPayer_Parts_a = 0;

	// �p�[�ca��X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_GAME_PLAYER_PARTS_A,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&g_pD3DXBuffMatPayer_Parts_a,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&g_nNumMatPayer_Parts_a,		// D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshPayer_Parts_a)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}


#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTexturePayer_Parts_a);	// �ǂݍ��ރ������[


#endif

									// �e�̐���
	g_nIdxShadow = CreateShadow(player_parts_a->pos, 25.0f, 25.0f);

	g_fSizeShadow = 25.0f;
	g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	player_parts_a->use = true;
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
	player_parts_a->Radius = D3DXVec2Length(&temp);										// �v���C���[�̔��a��������
	player_parts_a->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer_Parts_a(void)
{
	if (g_pD3DTexturePayer_Parts_a != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePayer_Parts_a->Release();
		g_pD3DTexturePayer_Parts_a = NULL;
	}

	if (g_pD3DXMeshPayer_Parts_a != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPayer_Parts_a->Release();
		g_pD3DXMeshPayer_Parts_a = NULL;
	}

	if (g_pD3DXBuffMatPayer_Parts_a != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPayer_Parts_a->Release();
		g_pD3DXBuffMatPayer_Parts_a = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer_Parts_a(void)
{
	D3DXVECTOR3 rotCamera;

	// �J�����̌����擾
	rotCamera = GetRotCamera();

	PLAYER_PARTS_A *player_parts_a = &player_parts_aWk[0];
	ENEMY  *enemy = GetEnemy(0);
	BARRIER *barrier = GetBarrier(0);


	if (player_parts_a->use == true)
	{
		//�����Ă�������Ɉړ�
		if (GetKeyboardPress(DIK_W))
		{
			player_parts_a->pos.x += sinf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
			player_parts_a->pos.z += cosf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
		}

		if (IsButtonPressed(0, BUTTON_DOWN))
		{
			player_parts_a->pos.x += sinf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
			player_parts_a->pos.z += cosf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
		}

		if (GetKeyboardPress(DIK_S))
		{
			player_parts_a->pos.x -= sinf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
			player_parts_a->pos.z -= cosf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
		}

		else if (IsButtonPressed(0, BUTTON_UP))
		{
			player_parts_a->pos.x -= sinf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
			player_parts_a->pos.z -= cosf(player_parts_a->rot.y) * PLAYER_PARTS_A_MOVE;
		}

		//��]
		if (GetKeyboardPress(DIK_Q))
		{
			player_parts_a->rot.y -= VALUE_ROTATE_A;
		}

		else if (IsButtonPressed(0, BUTTON_LEFT))
		{
			player_parts_a->rot.y -= VALUE_ROTATE_A;
		}

		if (GetKeyboardPress(DIK_E))
		{
			player_parts_a->rot.y += VALUE_ROTATE_A;
		}

		else if (IsButtonPressed(0, BUTTON_RIGHT))
		{
			player_parts_a->rot.y += VALUE_ROTATE_A;
		}

		if (player_parts_a->pos.x >= FIELD_SCL-30)
		{
			player_parts_a->pos.x = FIELD_SCL - 30;
		}

		if (player_parts_a->pos.z >= FIELD_SCL - 30)
		{
			player_parts_a->pos.z = FIELD_SCL - 30;
		}

		if (player_parts_a->pos.x <= -FIELD_SCL+ 30)
		{
			player_parts_a->pos.x = -FIELD_SCL + 30;
		}

		if (player_parts_a->pos.z <= -FIELD_SCL + 30)
		{
			player_parts_a->pos.z = -FIELD_SCL + 30;
		}

		// �e�̈ʒu�ݒ�
		SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(player_parts_a->pos.x, 0.1f, player_parts_a->pos.z));

		SetVertexShadow(g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
		SetColorShadow(g_nIdxShadow, g_colShadow);
	}
}

//=============================================================================
// �p�[�ca�`�揈��
//=============================================================================
void DrawPlayer_Parts_a(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER_PARTS_A *player_parts_a = &player_parts_aWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, player_parts_a->scl.x, player_parts_a->scl.y, player_parts_a->scl.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player_parts_a->rot.y, player_parts_a->rot.x, player_parts_a->rot.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, player_parts_a->pos.x, player_parts_a->pos.y, player_parts_a->pos.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	// ���݂̃}�e���A�����擾(���ɖ߂����߂̃o�b�N�A�b�v)
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPayer_Parts_a->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPayer_Parts_a; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePayer_Parts_a);

		// �`��
		g_pD3DXMeshPayer_Parts_a->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �v���C���[�p�[�ca�擾�֐�
//=============================================================================
PLAYER_PARTS_A *GetPlayer_Parts_a(int no)
{
	return(&player_parts_aWk[no]);
}

//=============================================================================
// �}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX *GetPlayer_Parts_aWorldMatrix(void)
{
	return(&g_mtxWorld);
}
