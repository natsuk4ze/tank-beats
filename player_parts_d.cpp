//=============================================================================
//
// �v���C���[�p�[�cd���� [player_parts_d.cpp]
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
#include "particle.h"
#include "player.h"
#include "target.h"
#include "enemy.h"
#include "sound.h"
#include "circle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_GAME_PLAYER_PARTS_D "data/MODEL/tank002/tank002_d.x"
#define TEXTURE_FILENAME	"data/TEXTURE/tank_skin002.jpg"

#define	VALUE_MOVE		(5.0f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void FireEffect(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_Parts_d;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshPlayer_Parts_d;			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_Parts_d;		// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatPlayer_Parts_d;			// �}�e���A�����̐�
static	D3DXMATRIX	g_mtxWorld_d;						// ���[���h�}�g���b�N�X

PLAYER_PARTS_D		player_parts_dWk[PLAYER_PARTS_D_MAX];	// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer_Parts_d(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER_PARTS_D *player_parts_d = &player_parts_dWk[0];

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	player_parts_d->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_d->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player_parts_d->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	player_parts_d->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_pD3DTexturePlayer_Parts_d = NULL;
	g_pD3DXMeshPlayer_Parts_d = NULL;
	g_pD3DXBuffMatPlayer_Parts_d = NULL;
	g_nNumMatPlayer_Parts_d = 0;

	player_parts_d->Angle = 0.0f;

	// �p�[�cb��X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(TEXTURE_GAME_PLAYER_PARTS_D,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&g_pD3DXBuffMatPlayer_Parts_d,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&g_nNumMatPlayer_Parts_d,		// D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshPlayer_Parts_d)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}


#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTexturePlayer_Parts_d);	// �ǂݍ��ރ������[

#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer_Parts_d(void)
{
	if (g_pD3DTexturePlayer_Parts_d != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer_Parts_d->Release();
		g_pD3DTexturePlayer_Parts_d = NULL;
	}

	if (g_pD3DXMeshPlayer_Parts_d != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshPlayer_Parts_d->Release();
		g_pD3DXMeshPlayer_Parts_d = NULL;
	}

	if (g_pD3DXBuffMatPlayer_Parts_d != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatPlayer_Parts_d->Release();
		g_pD3DXBuffMatPlayer_Parts_d = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer_Parts_d(void)
{
	PLAYER_PARTS_D *player_parts_d = &player_parts_dWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);
	TARGET *target = GetTarget(0);
	BULLET *bullet = GetBullet(0);
	ENEMY  *enemy = GetEnemy(0);

	player_parts_d->pos = GetPartPos(player_parts_a->pos, player_parts_a->rot + player_parts_b->rot, D3DXVECTOR3(0.0f, 15.0f, 70.0f));
	player_parts_d->Angle = atan2f((player_parts_d->pos.z - target->pos.z), (player_parts_d->pos.x - target->pos.x))*180.0f / D3DX_PI;				   // �^�[�Q�b�g�ƃp�[�cd�̊p�x
	player_parts_d->targetdistance = hypotf(powf((target->pos.x - player_parts_d->pos.x),2.0f), (powf((target->pos.z - player_parts_d->pos.z),2.0f))); // �^�[�Q�b�g�ƃp�[�cd�̋���

	// �e����
	if (GetKeyboardTrigger(DIK_RETURN)|| IsButtonTriggered(0, BUTTON_B))
	{
		GetParameter();

		if (CanAtack())
		{
			D3DXVECTOR3 pos = player_parts_d->pos;
			SetFire(pos);
			player_parts_d->FireEffectUse = true;
		}
		else
		{

		}
	}

	FireEffect();

	if (target->use == true) 
	{
		//��]
		if (GetKeyboardPress(DIK_Q))
		{
			player_parts_b->rot.y += VALUE_ROTATE_A;
		}

		else if (IsButtonPressed(0, BUTTON_Z))
		{
			player_parts_b->rot.y += VALUE_ROTATE_A;
		}

		if (GetKeyboardPress(DIK_E))
		{
			player_parts_b->rot.y -= VALUE_ROTATE_A;
		}

		else if (IsButtonPressed(0, BUTTON_Y))
		{
			player_parts_b->rot.y -= VALUE_ROTATE_A;
		}

		if (player_parts_d->Angle != player_parts_b->Angle)
		{
			if (player_parts_d->Angle <= player_parts_b->Angle)
			{
				player_parts_b->rot.y += 0.010f*D3DX_PI;
			}
			else
			{
				player_parts_b->rot.y -= 0.010f*D3DX_PI;
			}
		}
	}
}

//=============================================================================
// �p�[�cd�`�揈��
//=============================================================================
void DrawPlayer_Parts_d(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER_PARTS_D *player_parts_d = &player_parts_dWk[0];
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorld_d);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, player_parts_d->scl.x, player_parts_d->scl.y, player_parts_d->scl.z);
	D3DXMatrixMultiply(&g_mtxWorld_d, &g_mtxWorld_d, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&g_mtxWorld_d, &g_mtxWorld_d, &mtxRot);

	// �ړ��𔽉f(��I�u�W�F�N�g����l����)
	D3DXMatrixTranslation(&mtxTranslate, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&g_mtxWorld_d, &g_mtxWorld_d, &mtxTranslate);

	//�e�̃��[���h�}�g���b�N�X�Ɏ����̃��[���h�}�g���b�N�X��������
	D3DXMatrixMultiply(&g_mtxWorld_d, &g_mtxWorld_d, GetPlayer_Parts_bWorldMatrix());

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld_d);

	// ���݂̃}�e���A�����擾(���ɖ߂����߂̃o�b�N�A�b�v)
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_Parts_d->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_Parts_d; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayer_Parts_d);

		// �`��
		g_pD3DXMeshPlayer_Parts_d->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �v���C���[�p�[�cd�擾�֐�
//=============================================================================
PLAYER_PARTS_D *GetPlayer_Parts_d(int no)
{
	return(&player_parts_dWk[no]);
}

//=============================================================================
// ���˃G�t�F�N�g����
//=============================================================================
void FireEffect()
{
	PLAYER_PARTS_D *player_parts_d = &player_parts_dWk[0];
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);
	BULLET *bullet = GetBullet(0);

	if (player_parts_d->FireEffectUse == true)
	{
		player_parts_d->scl.x = sinf(player_parts_d->radian) * 2.0f; // ��C��̊g��

		player_parts_b->move.x = -sinf(player_parts_b->rot.y) *sinf(player_parts_d->radian) * 5.0f; // �����\��
		player_parts_b->move.z = -cosf(player_parts_b->rot.y) *sinf(player_parts_d->radian) * 5.0f; // �����\��

		if (player_parts_d->radian >= D3DX_PI)
		{
			player_parts_d->radian = 0.0f;
			player_parts_d->FireEffectUse = false;
		}

		player_parts_d->radian += 0.20f;
	}

}
