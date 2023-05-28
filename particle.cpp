//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "particle.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "main.h"
#include <time.h>
#include "player_parts_a.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PARTICLE		"data/TEXTURE/particle006.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_PARTICLE		(3.00f)							// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);
void SetVertexParticle(int nIdxParticle, float fWidth, float fHeight);
void SetColorParticle(int nIdxParticle, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureParticle;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffParticle = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

PARTICLE					g_aParticleWk[PARTICLE_MAX];		// �p�[�e�B�N�����[�N
static	bool				g_bAlpaTest;						// �A���t�@�e�X�gON/OFF
static	int					g_nAlpha;							// �A���t�@�e�X�g��臒l

//=============================================================================
// ����������
//=============================================================================
HRESULT InitParticle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARTICLE *g_aParticle = &g_aParticleWk[0];	// �p�[�e�B�N���̃|�C���^�[��������

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_PARTICLE, 				// �t�@�C���̖��O
			&g_apD3DTextureParticle);		// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexParticle(pDevice);	

	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].scl = D3DXVECTOR3(1.0f,1.0f, 1.0f);
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���ˋ����Ɗp�x�����߂�
		g_aParticle[nCntParticle].Angle = (float)(50.0 + rand() % 360) / 100.0f;
		g_aParticle[nCntParticle].Length = (float)(rand() % 10) / 1.0f;
		g_aParticle[nCntParticle].hight = (float)(30.0 + rand() % 200) / 1.0f;
		g_aParticle[nCntParticle].Size = (float)(10.0 + rand() % 20)/30.0f;

		g_aParticle[nCntParticle].move.x = sinf(g_aParticle[0].Angle) * g_aParticle[nCntParticle].Length;
		g_aParticle[nCntParticle].move.z = cosf(g_aParticle[0].Angle) * g_aParticle[nCntParticle].Length;
		g_aParticle[nCntParticle].move.y = g_aParticle[nCntParticle].hight;
		g_aParticle[nCntParticle].scl.x = g_aParticle[nCntParticle].Size;
		g_aParticle[nCntParticle].scl.y = g_aParticle[nCntParticle].Size;
		g_aParticle[nCntParticle].scl.z = g_aParticle[nCntParticle].Size;

		g_aParticle[nCntParticle].fWidth = PARTICLE_WIDTH;
		g_aParticle[nCntParticle].fHeight = PARTICLE_HEIGHT;
		g_aParticle[nCntParticle].use = false;

		//�p�[�e�B�N���̐ݒ�
		SetParticle(30.0f, 30.0f, g_aParticle[nCntParticle].col);
		g_aParticle[nCntParticle].Particleradian = 0.0f;
	}

	g_bAlpaTest = true;
	g_nAlpha = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	if (g_apD3DTextureParticle != NULL)
	{// �e�N�X�`���̊J��
		g_apD3DTextureParticle->Release();
		g_apD3DTextureParticle = NULL;
	}

	if (g_pD3DVtxBuffParticle != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffParticle->Release();
		g_pD3DVtxBuffParticle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	PARTICLE *g_aParticle = &g_aParticleWk[0];	// �p�[�e�B�N���̃|�C���^�[��������


	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		g_aParticle[nCntParticle].Particleradian += 0.05f;

		if (g_aParticle[nCntParticle].use == true)
		{
			// �e�̈ʒu�ݒ�
			SetPositionShadow(g_aParticle[nCntParticle].nIdxShadow, D3DXVECTOR3(g_aParticle[nCntParticle].pos.x, 0.1f, g_aParticle[nCntParticle].pos.z));

			//�ړ�����
			if (g_aParticle[nCntParticle].pos.y > 0.0f)
			{
				g_aParticle[nCntParticle].pos.x += sinf(g_aParticle[nCntParticle].move.x);
				g_aParticle[nCntParticle].pos.z += cosf(g_aParticle[nCntParticle].move.z);
			}
			
			//�o�E���h
			Bound();
			
			//�����ɂ��Ă���
			g_aParticle[nCntParticle].col.a -= 0.01f;
			//g_aParticle[nCntParticle].col.r += 0.60f;
			//g_aParticle[nCntParticle].col.g += 0.70f;
			//g_aParticle[nCntParticle].col.b += 0.05f;

			SetColorParticle(nCntParticle, g_aParticle[nCntParticle].col);


			if (g_aParticle[nCntParticle].col.a <= 0.0f)
			{
				g_aParticle[nCntParticle].use = false;

				g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aParticle[nCntParticle].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aParticle[nCntParticle].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���ˋ����Ɗp�x�����߂�
				g_aParticle[nCntParticle].Angle = (float)(50.0 + rand() % 360) / 100.0f;
				g_aParticle[nCntParticle].Length = (float)(rand() % 10) / 1.0f;
				g_aParticle[nCntParticle].hight = (float)(30.0 + rand() % 200) / 1.0f;
				g_aParticle[nCntParticle].Size = (float)(10.0 + rand() % 20) / 30.0f;

				g_aParticle[nCntParticle].move.x = sinf(g_aParticle[0].Angle) * g_aParticle[nCntParticle].Length;
				g_aParticle[nCntParticle].move.z = cosf(g_aParticle[0].Angle) * g_aParticle[nCntParticle].Length;
				g_aParticle[nCntParticle].move.y = g_aParticle[nCntParticle].hight;
				g_aParticle[nCntParticle].scl.x = g_aParticle[nCntParticle].Size;
				g_aParticle[nCntParticle].scl.y = g_aParticle[nCntParticle].Size;
				g_aParticle[nCntParticle].scl.z = g_aParticle[nCntParticle].Size;

				g_aParticle[nCntParticle].fWidth = PARTICLE_WIDTH;
				g_aParticle[nCntParticle].fHeight = PARTICLE_HEIGHT;

				//�p�[�e�B�N���̐ݒ�
				SetParticle(30.0f, 30.0f, g_aParticle[nCntParticle].col);
				g_aParticle[nCntParticle].Particleradian = 0.0f;
			}
		}
	}

	// �A���t�@�e�X�gON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		g_bAlpaTest = g_bAlpaTest ? false : true;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	PARTICLE *g_aParticle = &g_aParticleWk[0];	// �p�[�e�B�N���̃|�C���^�[��������

	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���e�X�g�ݒ�
	if (g_bAlpaTest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, g_nAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&g_aParticle[nCntParticle].mtxWorld, NULL, &mtxView);
			g_aParticle[nCntParticle].mtxWorld._41 = 0.0f;
			g_aParticle[nCntParticle].mtxWorld._42 = 0.0f;
			g_aParticle[nCntParticle].mtxWorld._43 = 0.0f;
#else
			g_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
			g_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
			g_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
			g_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
			g_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
			g_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
			g_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
			g_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
			g_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aParticle[nCntParticle].scl.x,
				g_aParticle[nCntParticle].scl.y,
				g_aParticle[nCntParticle].scl.z);
			D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtxWorld, &g_aParticle[nCntParticle].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aParticle[nCntParticle].pos.x,
				g_aParticle[nCntParticle].pos.y,
				g_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtxWorld, &g_aParticle[nCntParticle].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCntParticle].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureParticle);

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
HRESULT MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * PARTICLE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffParticle,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-PARTICLE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-PARTICLE_WIDTH / 2.0f, PARTICLE_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(PARTICLE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(PARTICLE_WIDTH / 2.0f, PARTICLE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffParticle->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexParticle(int nIdxParticle, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorParticle(int nIdxParticle, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxParticle * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffParticle->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetParticle(float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxParticle = -1;
	PARTICLE *g_aParticle = &g_aParticleWk[0];		// �p�[�e�B�N���̃|�C���^�[��������
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);					// �v���C���[�̃|�C���^�[��������


	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		if (!g_aParticle[nCntParticle].use)
		{
			g_aParticle[nCntParticle].scl.x = g_aParticle[nCntParticle].Size;
			g_aParticle[nCntParticle].scl.y = g_aParticle[nCntParticle].Size;
			g_aParticle[nCntParticle].scl.z = g_aParticle[nCntParticle].Size;

			g_aParticle[nCntParticle].fWidth = fWidth;
			g_aParticle[nCntParticle].fHeight = fHeight;
			//g_aParticle[nCntParticle].use = true;

			// ���_���W�̐ݒ�
			SetVertexParticle(nCntParticle, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorParticle(nCntParticle, col);

			// �e�̐ݒ�
			g_aParticle[nCntParticle].nIdxShadow = CreateShadow(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].fWidth, g_aParticle[nCntParticle].fWidth);

			nIdxParticle = nCntParticle;

			break;
		}
	}

	return nIdxParticle;
}

//=============================================================================
// �o�E���h����
//=============================================================================
void Bound()
{
	PARTICLE *g_aParticle = &g_aParticleWk[0];	// �p�[�e�B�N���̃|�C���^�[��������

	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos.y = sinf(g_aParticle[nCntParticle].Particleradian) *g_aParticle[nCntParticle].move.y;

			//���n�Ō���
			if (g_aParticle[nCntParticle].Particleradian >= D3DX_PI)
			{
				g_aParticle[nCntParticle].move.y *= 0.50f;
				g_aParticle[nCntParticle].Particleradian = 0.0f;
			}
	}
}

//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{
	PARTICLE *g_aParticle = &g_aParticleWk[0];				// �p�[�e�B�N���̃|�C���^�[��������

	// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].use == false)		// ���g�p��Ԃ̃o���b�g��������
		{
			g_aParticle[nCntParticle].use = true;			// �g�p��Ԃ֕ύX����
			g_aParticle[nCntParticle].pos = pos;			// ���W���Z�b�g
		}
	}
}

//=============================================================================
// �p�[�e�B�N�����擾
//=============================================================================
PARTICLE *GetParticle(int no)
{
	return &g_aParticleWk[no];
}
