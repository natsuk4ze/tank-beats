//=============================================================================
//
// �X�^�[��ʏ��� [star.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "star.h"
#include "tutorial.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	STAR_MAX           (1)							//�@�X�^�[�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexStar(int no);
void SetVertexStar(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureStar = NULL;		// �e�N�X�`���ւ̃|�C���^
STAR					starWk[STAR_MAX];				// �X�^�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	STAR *star = &starWk[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_STAR,				// �t�@�C���̖��O
								&g_pD3DTextureStar);		// �ǂݍ��ރ������[

	for (int i = 0; i < STAR_MAX; i++, star++)
	{
		star->pos = D3DXVECTOR3(SCREEN_CENTER_X, 910.0f, 0.0f);
		star->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR2 temp = D3DXVECTOR2(STAR_SIZE_X, STAR_SIZE_Y);
		star->Radius = D3DXVec2Length(&temp);				// ���a��������
		star->BaseAngle = atan2f(STAR_SIZE_Y, STAR_SIZE_X);	// �p�x��������
										
		star->Texture = g_pD3DTextureStar;					// �e�N�X�`�����

		MakeVertexStar(i); // ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStar(void)
{
	if(g_pD3DTextureStar != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureStar->Release();
		g_pD3DTextureStar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStar(void)
{
	STAR *star = &starWk[0];

	for (int i = 0; i < STAR_MAX; i++, star++)
	{
		SetVertexStar(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	STAR *star = &starWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < STAR_MAX; i++, star++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, star->Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, star->g_vertexWkStar, sizeof(VERTEX_2D));

		PrintDebugProc("[�X�^�[�̈ʒu  �F(%f : %f : %f)]\n", star->pos.x, star->pos.y, star->pos.z);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexStar(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	STAR *star = &starWk[no];

	// ���_���W�̐ݒ�
	SetVertexStar(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	star->g_vertexWkStar[0].rhw =
		star->g_vertexWkStar[1].rhw =
		star->g_vertexWkStar[2].rhw =
		star->g_vertexWkStar[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	star->g_vertexWkStar[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	star->g_vertexWkStar[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	star->g_vertexWkStar[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	star->g_vertexWkStar[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	star->g_vertexWkStar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	star->g_vertexWkStar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	star->g_vertexWkStar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	star->g_vertexWkStar[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexStar(int no)
{
	STAR *star = &starWk[no];

	// ���_���W�̐ݒ�
	star->g_vertexWkStar[0].vtx.x = star->pos.x - cosf(star->BaseAngle + star->rot.z) * star->Radius;
	star->g_vertexWkStar[0].vtx.y = star->pos.y - sinf(star->BaseAngle + star->rot.z) * star->Radius;
	star->g_vertexWkStar[0].vtx.z = 0.0f;

	star->g_vertexWkStar[1].vtx.x = star->pos.x + cosf(star->BaseAngle - star->rot.z) * star->Radius;
	star->g_vertexWkStar[1].vtx.y = star->pos.y - sinf(star->BaseAngle - star->rot.z) * star->Radius;
	star->g_vertexWkStar[1].vtx.z = 0.0f;

	star->g_vertexWkStar[2].vtx.x = star->pos.x - cosf(star->BaseAngle - star->rot.z) * star->Radius;
	star->g_vertexWkStar[2].vtx.y = star->pos.y + sinf(star->BaseAngle - star->rot.z) * star->Radius;
	star->g_vertexWkStar[2].vtx.z = 0.0f;

	star->g_vertexWkStar[3].vtx.x = star->pos.x + cosf(star->BaseAngle + star->rot.z) * star->Radius;
	star->g_vertexWkStar[3].vtx.y = star->pos.y + sinf(star->BaseAngle + star->rot.z) * star->Radius;
	star->g_vertexWkStar[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�^�[�擾�֐�
//=============================================================================
STAR *GetStar(int no)
{
	return(&starWk[no]);
}
