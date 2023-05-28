//=============================================================================
//
// �m�[�c��ʏ��� [notes.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "notes.h"
#include "tutorial.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NOTES_MAX           (5)							// �m�[�c�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexNotes(int no);
void SetVertexNotes(int no);
void Gettime(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureNotes = NULL;		// �e�N�X�`���ւ̃|�C���^
NOTES					notesWk[NOTES_MAX];				// �m�[�c�\����

int bgm;
float bps;
float notesspeed;
float notesspeedperflame;
float speed;
//float time;

// ���Ԍv���p
static	DWORD ExecLastTime;
static	DWORD LastTime;
static	DWORD CurrentTime;
static	BOOL bPerf;                 // ���𑜓x�J�E���^�[�ɑΉ����Ă��邩
static	LARGE_INTEGER mFreq;        // 1�b�Ԃ̃J�E���g��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitNotes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOTES *notes = &notesWk[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NOTES,			// �t�@�C���̖��O
								&g_pD3DTextureNotes);	// �ǂݍ��ރ������[

	for (int i = 0; i < NOTES_MAX; i++, notes++)
	{
		notes->use = true;
		notes->pos = D3DXVECTOR3(SCREEN_CENTER_X -300 - i*NOTES_INTERVAL, 930.0f, 0.0f);
		notes->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR2 temp = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
		notes->Radius = D3DXVec2Length(&temp);					// ���a��������
		notes->BaseAngle = atan2f(NOTES_SIZE_Y, NOTES_SIZE_X);	// �p�x��������
										
		notes->Texture = g_pD3DTextureNotes;					// �e�N�X�`�����

		MakeVertexNotes(i); // ���_���̍쐬
	}

	// �m�[�c�X�s�[�h����

	bgm = 0;

	if (bgm == 0)
	{
		bps = 145.0f/60;
		notesspeed = NOTES_INTERVAL * bps;
		notesspeedperflame = notesspeed / 60;
	}

	////
	//time = 60 / 145;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitNotes(void)
{
	if(g_pD3DTextureNotes != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureNotes->Release();
		g_pD3DTextureNotes = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateNotes(void)
{
	NOTES *notes = &notesWk[0];

	for (int i = 0; i < NOTES_MAX; i++, notes++)
	{
		if (notes->use == true)
		{
			notes->pos.x += notesspeedperflame;

			SetVertexNotes(i);

			if (notes->pos.x >= SCREEN_CENTER_X)
			{
				notes->pos.x = SCREEN_CENTER_X;
			}

			if (notes->pos.x == SCREEN_CENTER_X)
			{
				notes->use = false;
				i = 3;
				notes->pos = D3DXVECTOR3(SCREEN_CENTER_X - 300 - i * NOTES_INTERVAL, 930.0f, 0.0f);
				notes->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				D3DXVECTOR2 temp = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
				notes->Radius = D3DXVec2Length(&temp);					// ���a��������
				notes->BaseAngle = atan2f(NOTES_SIZE_Y, NOTES_SIZE_X);	// �p�x��������

				notes->Texture = g_pD3DTextureNotes;					// �e�N�X�`�����

				MakeVertexNotes(i); // ���_���̍쐬
				notes->use = true;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawNotes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOTES *notes = &notesWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NOTES_MAX; i++, notes++)
	{
		if (notes->use == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, notes->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, notes->g_vertexWkNotes, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexNotes(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	NOTES *notes = &notesWk[no];

	// ���_���W�̐ݒ�
	SetVertexNotes(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	notes->g_vertexWkNotes[0].rhw =
		notes->g_vertexWkNotes[1].rhw =
		notes->g_vertexWkNotes[2].rhw =
		notes->g_vertexWkNotes[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	notes->g_vertexWkNotes[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	notes->g_vertexWkNotes[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	notes->g_vertexWkNotes[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	notes->g_vertexWkNotes[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	notes->g_vertexWkNotes[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	notes->g_vertexWkNotes[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	notes->g_vertexWkNotes[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	notes->g_vertexWkNotes[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexNotes(int no)
{
	NOTES *notes = &notesWk[no];

	// ���_���W�̐ݒ�
	notes->g_vertexWkNotes[0].vtx.x = notes->pos.x - cosf(notes->BaseAngle + notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[0].vtx.y = notes->pos.y - sinf(notes->BaseAngle + notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[0].vtx.z = 0.0f;

	notes->g_vertexWkNotes[1].vtx.x = notes->pos.x + cosf(notes->BaseAngle - notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[1].vtx.y = notes->pos.y - sinf(notes->BaseAngle - notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[1].vtx.z = 0.0f;

	notes->g_vertexWkNotes[2].vtx.x = notes->pos.x - cosf(notes->BaseAngle - notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[2].vtx.y = notes->pos.y + sinf(notes->BaseAngle - notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[2].vtx.z = 0.0f;

	notes->g_vertexWkNotes[3].vtx.x = notes->pos.x + cosf(notes->BaseAngle + notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[3].vtx.y = notes->pos.y + sinf(notes->BaseAngle + notes->rot.z) * notes->Radius;
	notes->g_vertexWkNotes[3].vtx.z = 0.0f;
}

////=============================================================================
//// �o�ߎ��ԏ�������
////=============================================================================
//void Gettime()
//{
//	CurrentTime = timeGetTime();
//	if ((CurrentTime - LastTime) >= 10)	// 0.01�b���ƂɎ��s
//	{
//		speed += notesspeedperflame / 100;
//		LastTime = CurrentTime;
//	}
//}

//=============================================================================
// �m�[�c�擾�֐�
//=============================================================================
NOTES *GetNotes(int no)
{
	return(&notesWk[no]);
}
