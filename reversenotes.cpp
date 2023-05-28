//=============================================================================
//
// �t�m�[�c��ʏ��� [reversenotes.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "reversenotes.h"
#include "tutorial.h"
#include "debugproc.h"
#include "notes.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	REVERSENOTES_MAX           (5)							//�@�t�m�[�c�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexReversenotes(int no);
void SetVertexReversenotes(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureReversenotes = NULL;		// �e�N�X�`���ւ̃|�C���^
REVERSENOTES			reversenotesWk[REVERSENOTES_MAX];		// �t�m�[�c�\����

static	int bgm;
static	float bps;
static	float notesspeed;
static	float notesspeedperflame;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitReversenotes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	REVERSENOTES *reversenotes = &reversenotesWk[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
								TEXTURE_REVERSENOTES,			// �t�@�C���̖��O
								&g_pD3DTextureReversenotes);	// �ǂݍ��ރ������[

	for (int i = 0; i < REVERSENOTES_MAX; i++, reversenotes++)
	{
		reversenotes->use = true;

		reversenotes->pos = D3DXVECTOR3(SCREEN_CENTER_X + 300 + i* NOTES_INTERVAL, 930.0f, 0.0f);
		reversenotes->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR2 temp = D3DXVECTOR2(REVERSENOTES_SIZE_X, REVERSENOTES_SIZE_Y);
		reversenotes->Radius = D3DXVec2Length(&temp);								// ���a��������
		reversenotes->BaseAngle = atan2f(REVERSENOTES_SIZE_Y, REVERSENOTES_SIZE_X);	// �p�x��������
										
		reversenotes->Texture = g_pD3DTextureReversenotes;							// �e�N�X�`�����

		MakeVertexReversenotes(i); // ���_���̍쐬
	}

	// �m�[�c�X�s�[�h����

	bgm = 0;

	if (bgm == 0)
	{
		bps = 145.0f / 60;
		notesspeed = NOTES_INTERVAL * bps;
		notesspeedperflame = notesspeed / 60;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitReversenotes(void)
{
	if(g_pD3DTextureReversenotes != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureReversenotes->Release();
		g_pD3DTextureReversenotes = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReversenotes(void)
{
	REVERSENOTES *reversenotes = &reversenotesWk[0];

	for (int i = 0; i < REVERSENOTES_MAX; i++, reversenotes++)
	{
		if (reversenotes->use == true)
		{
			reversenotes->pos.x -= notesspeedperflame;

			SetVertexReversenotes(i);

			if (reversenotes->pos.x <= SCREEN_CENTER_X)
			{
				reversenotes->pos.x = SCREEN_CENTER_X;
			}

			if (reversenotes->pos.x == SCREEN_CENTER_X)
			{
				reversenotes->use = false;
				i = 3;
				reversenotes->pos = D3DXVECTOR3(SCREEN_CENTER_X + 300 + i * NOTES_INTERVAL, 930.0f, 0.0f);
				reversenotes->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				D3DXVECTOR2 temp = D3DXVECTOR2(REVERSENOTES_SIZE_X, REVERSENOTES_SIZE_Y);
				reversenotes->Radius = D3DXVec2Length(&temp);								// ���a��������
				reversenotes->BaseAngle = atan2f(REVERSENOTES_SIZE_Y, REVERSENOTES_SIZE_X);	// �p�x��������

				reversenotes->Texture = g_pD3DTextureReversenotes;							// �e�N�X�`�����

				MakeVertexReversenotes(i); // ���_���̍쐬
				reversenotes->use = true;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawReversenotes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	REVERSENOTES *reversenotes = &reversenotesWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < REVERSENOTES_MAX; i++, reversenotes++)
	{
		if (reversenotes->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, reversenotes->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, reversenotes->g_vertexWkReversenotes, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexReversenotes(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	REVERSENOTES *reversenotes = &reversenotesWk[no];

	// ���_���W�̐ݒ�
	SetVertexReversenotes(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	reversenotes->g_vertexWkReversenotes[0].rhw =
		reversenotes->g_vertexWkReversenotes[1].rhw =
		reversenotes->g_vertexWkReversenotes[2].rhw =
		reversenotes->g_vertexWkReversenotes[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	reversenotes->g_vertexWkReversenotes[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	reversenotes->g_vertexWkReversenotes[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	reversenotes->g_vertexWkReversenotes[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	reversenotes->g_vertexWkReversenotes[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	reversenotes->g_vertexWkReversenotes[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	reversenotes->g_vertexWkReversenotes[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	reversenotes->g_vertexWkReversenotes[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	reversenotes->g_vertexWkReversenotes[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexReversenotes(int no)
{
	REVERSENOTES *reversenotes = &reversenotesWk[no];

	// ���_���W�̐ݒ�
	reversenotes->g_vertexWkReversenotes[0].vtx.x = reversenotes->pos.x - cosf(reversenotes->BaseAngle + reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[0].vtx.y = reversenotes->pos.y - sinf(reversenotes->BaseAngle + reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[0].vtx.z = 0.0f;

	reversenotes->g_vertexWkReversenotes[1].vtx.x = reversenotes->pos.x + cosf(reversenotes->BaseAngle - reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[1].vtx.y = reversenotes->pos.y - sinf(reversenotes->BaseAngle - reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[1].vtx.z = 0.0f;

	reversenotes->g_vertexWkReversenotes[2].vtx.x = reversenotes->pos.x - cosf(reversenotes->BaseAngle - reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[2].vtx.y = reversenotes->pos.y + sinf(reversenotes->BaseAngle - reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[2].vtx.z = 0.0f;

	reversenotes->g_vertexWkReversenotes[3].vtx.x = reversenotes->pos.x + cosf(reversenotes->BaseAngle + reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[3].vtx.y = reversenotes->pos.y + sinf(reversenotes->BaseAngle + reversenotes->rot.z) * reversenotes->Radius;
	reversenotes->g_vertexWkReversenotes[3].vtx.z = 0.0f;
}

//=============================================================================
// �t�m�[�c�擾�֐�
//=============================================================================
REVERSENOTES *GetReversenotes(int no)
{
	return(&reversenotesWk[no]);
}
