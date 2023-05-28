//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "tutorial.h"
#include "game.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTutorial(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorialLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTutorial[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTutorialLogo[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL,				// �t�@�C���̖��O
		&g_pD3DTextureTutorial);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL_LOGO,			// �t�@�C���̖��O
		&g_pD3DTextureTutorialLogo);	// �ǂݍ��ރ������[

										// ���_���̍쐬
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	if (g_pD3DTextureTutorial != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTutorial->Release();
		g_pD3DTextureTutorial = NULL;
	}

	if (g_pD3DTextureTutorialLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTutorialLogo->Release();
		g_pD3DTextureTutorialLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���

		InitGame();
		SetStage(STAGE_GAME);
	}

	// �Q�[���p�b�h�łňړ�����
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		InitGame();
		SetStage(STAGE_GAME);
	}
	else if (IsButtonTriggered(0, BUTTON_C))
	{
		InitGame();
		SetStage(STAGE_GAME);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTutorial);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTutorialLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorialLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTutorial(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkTutorial[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTutorial[0].rhw =
	g_vertexWkTutorial[1].rhw =
	g_vertexWkTutorial[2].rhw =
	g_vertexWkTutorial[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkTutorialLogo[0].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X, TUTORIALLOGO_POS_Y, 0.0f);
	g_vertexWkTutorialLogo[1].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X + TUTORIALLOGO_SIZE_X, TUTORIALLOGO_POS_Y, 0.0f);
	g_vertexWkTutorialLogo[2].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X, TUTORIALLOGO_POS_Y + TUTORIALLOGO_SIZE_Y, 0.0f);
	g_vertexWkTutorialLogo[3].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X + TUTORIALLOGO_SIZE_X, TUTORIALLOGO_POS_Y + TUTORIALLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTutorialLogo[0].rhw =
	g_vertexWkTutorialLogo[1].rhw =
	g_vertexWkTutorialLogo[2].rhw =
	g_vertexWkTutorialLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTutorialLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTutorialLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorialLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorialLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorialLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

