//=============================================================================
//
// �|�[�Y��ʏ��� [pause.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "pause.h"
#include "tutorial.h"
#include "game.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPause(void);
HRESULT MakeVertexCursor(int no);
void SetVertexCursor(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePause = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePauseMenu001 = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTexturePauseMenu002 = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureCursor = NULL;			// �e�N�X�`���ւ̃|�C���^
CURSOR					cursorWk[CURSOR_MAX];				// �J�[�\���\����

VERTEX_2D				g_vertexWkPauseMenu001[NUM_VERTEX];	// ���_���i�[���[�N
VERTEX_2D				g_vertexWkPauseMenu002[NUM_VERTEX];	// ���_���i�[���[�N

VERTEX_2D				g_vertexWkPause[NUM_VERTEX];		// ���_���i�[���[�N

PAUSE					pauseWk[PAUSE_MAX];					// �|�[�Y�\����
float					Distance_Menu;

// ���Ԍv���p
static	DWORD ExecLastTime;
static	DWORD LastTime;
static	DWORD CurrentTime;
static	BOOL bPerf;                 // ���𑜓x�J�E���^�[�ɑΉ����Ă��邩
static	LARGE_INTEGER mFreq;        // 1�b�Ԃ̃J�E���g��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PAUSE *pause = GetPause(0);								// �|�[�Y�̃|�C���^�[��������
	CURSOR *cursor = &cursorWk[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PAUSE,				// �t�@�C���̖��O
								&g_pD3DTexturePause);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PAUSEMENU001,		// �t�@�C���̖��O
								&g_pD3DTexturePauseMenu001);// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PAUSEMENU002,		// �t�@�C���̖��O
								&g_pD3DTexturePauseMenu002);// �ǂݍ��ރ������[

															// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_CURSOR,										// �t�@�C���̖��O
		&g_pD3DTextureCursor);								// �ǂݍ��ރ������[

	for (int i = 0; i < CURSOR_MAX; i++, cursor++)
	{
		cursor->pos = D3DXVECTOR3(PAUSEMENU001_POS_X , PAUSEMENU001_POS_Y + PAUSEMENU001_SIZE_Y/2, 0.0f);
		cursor->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR2 temp = D3DXVECTOR2(CURSOR_SIZE_X, CURSOR_SIZE_Y);
		cursor->Radius = D3DXVec2Length(&temp);						// ���a��������
		cursor->BaseAngle = atan2f(CURSOR_SIZE_Y, CURSOR_SIZE_X);	// �p�x��������

		cursor->Texture = g_pD3DTextureCursor;						// �e�N�X�`�����

		MakeVertexCursor(i); // ���_���̍쐬
	}

	Distance_Menu = PAUSEMENU002_POS_Y - PAUSEMENU001_POS_Y;
	cursor->State_Menu = 0;

	// ���_���̍쐬
	MakeVertexPause();
	pause->use = false;

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	ExecLastTime =
		LastTime = timeGetTime();
	CurrentTime = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	if(g_pD3DTexturePause != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePause->Release();
		g_pD3DTexturePause = NULL;
	}

	if(g_pD3DTexturePauseMenu001 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePauseMenu001->Release();
		g_pD3DTexturePauseMenu001 = NULL;
	}

	if (g_pD3DTexturePauseMenu002 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePauseMenu002->Release();
		g_pD3DTexturePauseMenu002 = NULL;
	}

	if (g_pD3DTextureCursor != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCursor->Release();
		g_pD3DTextureCursor = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	PAUSE *pause = GetPause(0);					// �|�[�Y�̃|�C���^�[��������
	CURSOR *cursor = &cursorWk[0];


	if (GetKeyboardTrigger(DIK_P))
	{
		pause->use = pause->use ? false : true;
	}
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		pause->use = pause->use ? false : true;
	}

	if (pause->use == true)
	{
		if (cursor->State_Menu == 0)
		{
			if (GetKeyboardTrigger(DIK_RETURN))
			{// Enter��������A�X�e�[�W��؂�ւ���

			 //�`���[�g���A���̏���������
				InitTutorial();
				SetStage(STAGE_TITLE);
			}
			else if (IsButtonTriggered(0, BUTTON_C))
			{
				//�`���[�g���A���̏���������
				InitTutorial();
				SetStage(STAGE_TITLE);
			}
		}

		if (cursor->State_Menu == 1)
		{
			if (GetKeyboardTrigger(DIK_RETURN))
			{// Enter��������A�X�e�[�W��؂�ւ���
				pause->use = false;
			}
			else if (IsButtonTriggered(0, BUTTON_C))
			{
				pause->use = false;
			}
		}
	}


	cursor->pos.y = PAUSEMENU001_POS_Y + PAUSEMENU001_SIZE_Y / 2 + cursor->State_Menu * Distance_Menu;

	CurrentTime = timeGetTime();
	if ((CurrentTime - LastTime) >= 10)	// 00.1�b���ƂɎ��s
	{
		if (GetKeyboardPress(DIK_SPACE))
		{
			cursor->State_Menu += 1;

			if (cursor->State_Menu >= MENU_MAX)
			{
				cursor->State_Menu = 0;
			}
		}
		else if (IsButtonTriggered(0, BUTTON_A))
		{
			cursor->State_Menu += 1;

			if (cursor->State_Menu >= MENU_MAX)
			{
				cursor->State_Menu = 0;
			}
		}


		LastTime = CurrentTime;
	}

	//cursor->State_Menu = (cursor->State_Menu + 1) % (MENU_MAX);

	for (int i = 0; i < CURSOR_MAX; i++, cursor++)
	{
		SetVertexCursor(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PAUSE *pause = GetPause(0);	// �|�[�Y�̃|�C���^�[��������

	if (pause->use == true)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePause);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkPause, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePauseMenu001);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkPauseMenu001, sizeof(VERTEX_2D));


		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePauseMenu002);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkPauseMenu002, sizeof(VERTEX_2D));

		CURSOR *cursor = &cursorWk[0];

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < CURSOR_MAX; i++, cursor++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, cursor->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, cursor->g_vertexWkCursor, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPause(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkPause[0].vtx = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	g_vertexWkPause[1].vtx = D3DXVECTOR3(PAUSE_POS_X + PAUSE_SIZE_X, PAUSE_POS_Y, 0.0f);
	g_vertexWkPause[2].vtx = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + PAUSE_SIZE_Y, 0.0f);
	g_vertexWkPause[3].vtx = D3DXVECTOR3(PAUSE_POS_X + PAUSE_SIZE_X, PAUSE_POS_Y + PAUSE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkPause[0].rhw =
	g_vertexWkPause[1].rhw =
	g_vertexWkPause[2].rhw =
	g_vertexWkPause[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkPause[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPause[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPause[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPause[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkPause[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPause[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkPause[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPause[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkPauseMenu001[0].vtx = D3DXVECTOR3(PAUSEMENU001_POS_X, PAUSEMENU001_POS_Y, 0.0f);
	g_vertexWkPauseMenu001[1].vtx = D3DXVECTOR3(PAUSEMENU001_POS_X + PAUSEMENU001_SIZE_X, PAUSEMENU001_POS_Y, 0.0f);
	g_vertexWkPauseMenu001[2].vtx = D3DXVECTOR3(PAUSEMENU001_POS_X, PAUSEMENU001_POS_Y + PAUSEMENU001_SIZE_Y, 0.0f);
	g_vertexWkPauseMenu001[3].vtx = D3DXVECTOR3(PAUSEMENU001_POS_X + PAUSEMENU001_SIZE_X, PAUSEMENU001_POS_Y + PAUSEMENU001_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkPauseMenu001[0].rhw =
	g_vertexWkPauseMenu001[1].rhw =
	g_vertexWkPauseMenu001[2].rhw =
	g_vertexWkPauseMenu001[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkPauseMenu001[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu001[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu001[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu001[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkPauseMenu001[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPauseMenu001[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkPauseMenu001[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPauseMenu001[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkPauseMenu002[0].vtx = D3DXVECTOR3(PAUSEMENU002_POS_X, PAUSEMENU002_POS_Y, 0.0f);
	g_vertexWkPauseMenu002[1].vtx = D3DXVECTOR3(PAUSEMENU002_POS_X + PAUSEMENU002_SIZE_X, PAUSEMENU002_POS_Y, 0.0f);
	g_vertexWkPauseMenu002[2].vtx = D3DXVECTOR3(PAUSEMENU002_POS_X, PAUSEMENU002_POS_Y + PAUSEMENU002_SIZE_Y, 0.0f);
	g_vertexWkPauseMenu002[3].vtx = D3DXVECTOR3(PAUSEMENU002_POS_X + PAUSEMENU002_SIZE_X, PAUSEMENU002_POS_Y + PAUSEMENU002_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkPauseMenu002[0].rhw =
		g_vertexWkPauseMenu002[1].rhw =
		g_vertexWkPauseMenu002[2].rhw =
		g_vertexWkPauseMenu002[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkPauseMenu002[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu002[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu002[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkPauseMenu002[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkPauseMenu002[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkPauseMenu002[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkPauseMenu002[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkPauseMenu002[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCursor(int no)
{
	CURSOR *cursor = &cursorWk[no];

	// ���_���W�̐ݒ�
	SetVertexCursor(no);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	cursor->g_vertexWkCursor[0].rhw =
		cursor->g_vertexWkCursor[1].rhw =
		cursor->g_vertexWkCursor[2].rhw =
		cursor->g_vertexWkCursor[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	cursor->g_vertexWkCursor[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cursor->g_vertexWkCursor[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cursor->g_vertexWkCursor[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	cursor->g_vertexWkCursor[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	cursor->g_vertexWkCursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	cursor->g_vertexWkCursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	cursor->g_vertexWkCursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	cursor->g_vertexWkCursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexCursor(int no)
{
	CURSOR *cursor = &cursorWk[no];

	// ���_���W�̐ݒ�
	cursor->g_vertexWkCursor[0].vtx.x = cursor->pos.x - cosf(cursor->BaseAngle + cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[0].vtx.y = cursor->pos.y - sinf(cursor->BaseAngle + cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[0].vtx.z = 0.0f;

	cursor->g_vertexWkCursor[1].vtx.x = cursor->pos.x + cosf(cursor->BaseAngle - cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[1].vtx.y = cursor->pos.y - sinf(cursor->BaseAngle - cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[1].vtx.z = 0.0f;

	cursor->g_vertexWkCursor[2].vtx.x = cursor->pos.x - cosf(cursor->BaseAngle - cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[2].vtx.y = cursor->pos.y + sinf(cursor->BaseAngle - cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[2].vtx.z = 0.0f;

	cursor->g_vertexWkCursor[3].vtx.x = cursor->pos.x + cosf(cursor->BaseAngle + cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[3].vtx.y = cursor->pos.y + sinf(cursor->BaseAngle + cursor->rot.z) * cursor->Radius;
	cursor->g_vertexWkCursor[3].vtx.z = 0.0f;
}

//=============================================================================
// �|�[�Y�擾�֐�
//=============================================================================
PAUSE *GetPause(int no)
{
	return(&pauseWk[no]);
}

//=============================================================================
// �J�[�\���擾�֐�
//=============================================================================
CURSOR *GetCursor(int no)
{
	return(&cursorWk[no]);
}
