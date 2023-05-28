//=============================================================================
//
// �o�[��ʏ��� [bar.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "bar.h"
#include "tutorial.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BAR_MAX           (1)						//�@�o�[�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBar(int no);
void SetVertexBar(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBar = NULL;	// �e�N�X�`���ւ̃|�C���^
BAR						barWk[BAR_MAX];				// �o�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BAR *bar = &barWk[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BAR,			// �t�@�C���̖��O
								&g_pD3DTextureBar);		// �ǂݍ��ރ������[

	for (int i = 0; i < BAR_MAX; i++, bar++)
	{
		bar->pos = D3DXVECTOR3(SCREEN_CENTER_X, 930.0f, 0.0f);
		bar->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR2 temp = D3DXVECTOR2(BAR_SIZE_X, BAR_SIZE_Y);
		bar->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		bar->BaseAngle = atan2f(BAR_SIZE_Y, BAR_SIZE_X);	// �v���C���[�̊p�x��������
										
		bar->Texture = g_pD3DTextureBar;					// �e�N�X�`�����

		MakeVertexBar(i); // ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBar(void)
{
	if(g_pD3DTextureBar != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBar->Release();
		g_pD3DTextureBar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBar(void)
{
	BAR *bar = &barWk[0];

	for (int i = 0; i < BAR_MAX; i++, bar++)
	{
		SetVertexBar(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BAR *bar = &barWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BAR_MAX; i++, bar++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, bar->Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bar->g_vertexWkBar, sizeof(VERTEX_2D));

		PrintDebugProc("[�o�[�̈ʒu  �F(%f : %f : %f)]\n", bar->pos.x, bar->pos.y, bar->pos.z);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBar(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BAR *bar = &barWk[no];

	// ���_���W�̐ݒ�
	SetVertexBar(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	bar->g_vertexWkBar[0].rhw =
		bar->g_vertexWkBar[1].rhw =
		bar->g_vertexWkBar[2].rhw =
		bar->g_vertexWkBar[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bar->g_vertexWkBar[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bar->g_vertexWkBar[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bar->g_vertexWkBar[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bar->g_vertexWkBar[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bar->g_vertexWkBar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bar->g_vertexWkBar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bar->g_vertexWkBar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bar->g_vertexWkBar[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBar(int no)
{
	BAR *bar = &barWk[no];

	// ���_���W�̐ݒ�
	bar->g_vertexWkBar[0].vtx.x = bar->pos.x - cosf(bar->BaseAngle + bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[0].vtx.y = bar->pos.y - sinf(bar->BaseAngle + bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[0].vtx.z = 0.0f;

	bar->g_vertexWkBar[1].vtx.x = bar->pos.x + cosf(bar->BaseAngle - bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[1].vtx.y = bar->pos.y - sinf(bar->BaseAngle - bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[1].vtx.z = 0.0f;

	bar->g_vertexWkBar[2].vtx.x = bar->pos.x - cosf(bar->BaseAngle - bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[2].vtx.y = bar->pos.y + sinf(bar->BaseAngle - bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[2].vtx.z = 0.0f;

	bar->g_vertexWkBar[3].vtx.x = bar->pos.x + cosf(bar->BaseAngle + bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[3].vtx.y = bar->pos.y + sinf(bar->BaseAngle + bar->rot.z) * bar->Radius;
	bar->g_vertexWkBar[3].vtx.z = 0.0f;
}

//=============================================================================
// �o�[�擾�֐�
//=============================================================================
BAR *GetBar(int no)
{
	return(&barWk[no]);
}
