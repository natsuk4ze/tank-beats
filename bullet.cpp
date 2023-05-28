//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "main.h"
#include <time.h>
#include "player_parts_b.h"
#include "player_parts_d.h"
#include "player_parts_a.h"
#include "debugproc.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BULLET		"data/TEXTURE/ball_g.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BULLET_WIDTH			(1.0f)							// �e�̔��a��
#define	BULLET_HEIGHT			(1.0f)							// �e�̔��a��
#define	VALUE_MOVE_BULLET		(6.0f)							// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBullet(int nIdxBullet, float fWidth, float fHeight);
void SetColorBullet(int nIdxBullet, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureBullet;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBullet = NULL;				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
BULLET					g_aBulletWk[BULLET_MAX];				// �o���b�g���[�N

LPDIRECTSOUNDBUFFER8	g_pSE;									// SE�p�o�b�t�@

static	float			Size;									//�傫��
float					bulletdistance;							//�C���ƒe�̋���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *g_aBullet = &g_aBulletWk[0];	// �o���b�g�̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BULLET, 		// �t�@�C���̖��O
			&g_apD3DTextureBullet);	// �ǂݍ��ރ������[

		g_pSE = LoadSound(SE_00);
		g_pSE->SetVolume(DSBVOLUME_MIN/10);
	}

	// ���_���̍쐬
	MakeVertexBullet(pDevice);

	Size = 1.0f;
	bulletdistance = 0;

	for (int nCntBullet = 0; nCntBullet <BULLET_MAX; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aBullet[nCntBullet].scl.x = Size;
		g_aBullet[nCntBullet].scl.y = Size;
		g_aBullet[nCntBullet].scl.z = Size;

		g_aBullet[nCntBullet].fWidth =BULLET_WIDTH;
		g_aBullet[nCntBullet].fHeight =BULLET_HEIGHT;
		g_aBullet[nCntBullet].use = false;

		//�o���b�g�̐ݒ�
		SetBullet(30.0f, 30.0f, g_aBullet[nCntBullet].col);

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
		g_aBullet[nCntBullet].Radius = D3DXVec2Length(&temp);									// �o���b�g�̔��a��������
		g_aBullet[nCntBullet].BaseAngle = atan2f(TEXTURE_BULLET_SIZE_Y, TEXTURE_BULLET_SIZE_X);	// �o���b�g�̊p�x��������
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if (g_apD3DTextureBullet != NULL)
	{// �e�N�X�`���̊J��
		g_apD3DTextureBullet->Release();
		g_apD3DTextureBullet = NULL;
	}

	if (g_pD3DVtxBuffBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBullet->Release();
		g_pD3DVtxBuffBullet = NULL;
	}

	//if (g_pSE != NULL)
	//{	// �����[�X
	//	g_pSE->Release();
	//	g_pSE = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);			// �p�[�c�̃|�C���^�[��������
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);			// �p�[�c�̃|�C���^�[��������
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);			// �p�[�c�̃|�C���^�[��������

	BULLET *g_aBullet = &g_aBulletWk[0];							// �o���b�g�̃|�C���^�[��������

	for (int nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].use == false)
		{

			g_aBullet[0].Angle = player_parts_b->rot.y + player_parts_a->rot.y;

			g_aBullet[nCntBullet].move.x = g_aBullet[0].Angle;
			g_aBullet[nCntBullet].move.z = g_aBullet[0].Angle;

		}

		if (g_aBullet[nCntBullet].use == true)
		{

			g_aBullet[nCntBullet].pos.x += sinf(g_aBullet[nCntBullet].move.x) * VALUE_MOVE_BULLET;
			g_aBullet[nCntBullet].pos.z += cosf(g_aBullet[nCntBullet].move.z) * VALUE_MOVE_BULLET;

			// �e�̈ʒu�ݒ�
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.1f, g_aBullet[nCntBullet].pos.z));
		}

		//���ˈʒu�Ƃ̋���
		bulletdistance = hypotf((g_aBullet[nCntBullet].pos.x - player_parts_b->pos.x), (g_aBullet[nCntBullet].pos.z - player_parts_b->pos.z));

		//���̋������ꂽ�疢�g�p�ɖ߂�
		if (bulletdistance >= g_aBullet[nCntBullet].Range)
		{
			g_aBullet[nCntBullet].use = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	BULLET *g_aBullet = &g_aBulletWk[0];	// �o���b�g�̃|�C���^�[��������


	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet <BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorld, NULL, &mtxView);
			g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;
#else
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scl.x,
				g_aBullet[nCntBullet].scl.y,
				g_aBullet[nCntBullet].scl.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aBullet[nCntBullet].pos.x,
				g_aBullet[nCntBullet].pos.y,
				g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
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
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX *BULLET_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBullet = 0; nCntBullet <BULLET_MAX; nCntBullet++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-BULLET_WIDTH / 2.0f,BULLET_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_WIDTH / 2.0f,BULLET_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(int nIdxBullet, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorBullet(int nIdxBullet, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetBullet(float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxBullet = -1;
	BULLET *g_aBullet = &g_aBulletWk[0];		// �o���b�g�̃|�C���^�[��������


	for (int nCntBullet = 0; nCntBullet <BULLET_MAX; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].use)
		{			
			g_aBullet[nCntBullet].scl.x = Size;
			g_aBullet[nCntBullet].scl.y = Size;
			g_aBullet[nCntBullet].scl.z = Size;

			g_aBullet[nCntBullet].fWidth = fWidth;
			g_aBullet[nCntBullet].fHeight = fHeight;

			// ���_���W�̐ݒ�
			SetVertexBullet(nCntBullet, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorBullet(nCntBullet, col);

			// �e�̐ݒ�
			g_aBullet[nCntBullet].nIdxShadow = CreateShadow(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].fWidth, g_aBullet[nCntBullet].fWidth);

			nIdxBullet = nCntBullet;

			break;
		}
	}

	return nIdxBullet;
}

//=============================================================================
// �e���˂̐ݒ�
//=============================================================================
void SetFire(D3DXVECTOR3 pos)
{
	BULLET *g_aBullet = &g_aBulletWk[0];				// �o���b�g�̃|�C���^�[��������

															// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int nCntBullet = 0; nCntBullet <BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			g_aBullet[nCntBullet].use = true;			// �g�p��Ԃ֕ύX����
			g_aBullet[nCntBullet].pos = pos;			// ���W���Z�b�g

			PlaySound(g_pSE, E_DS8_FLAG_NONE);			// ���ˉ��Đ�

			return;										// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g���擾
//=============================================================================
BULLET *GetBullet(int no)
{
	return &g_aBulletWk[no];
}
