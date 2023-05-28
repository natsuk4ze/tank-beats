//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "tutorial.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE,				// �t�@�C���̖��O
								&g_pD3DTextureTitle);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE_LOGO,			// �t�@�C���̖��O
								&g_pD3DTextureTitleLogo);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if(g_pD3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if(g_pD3DTextureTitleLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���

	 //�`���[�g���A���̏���������
		InitTutorial();
		SetStage(STAGE_TUTORIAL);
	}

	// �Q�[���p�b�h
	else if (IsButtonTriggered(0, BUTTON_START))
	{
		//�`���[�g���A���̏���������
		InitTutorial();
		SetStage(STAGE_TUTORIAL);
	}
	else if (IsButtonTriggered(0, BUTTON_C))
	{
		//�`���[�g���A���̏���������
		InitTutorial();
		SetStage(STAGE_TUTORIAL);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	
	// ���_���W�̐ݒ�
	g_vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	g_vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitle[0].rhw =
	g_vertexWkTitle[1].rhw =
	g_vertexWkTitle[2].rhw =
	g_vertexWkTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkTitleLogo[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y, 0.0f);
	g_vertexWkTitleLogo[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_vertexWkTitleLogo[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleLogo[0].rhw =
	g_vertexWkTitleLogo[1].rhw =
	g_vertexWkTitleLogo[2].rhw =
	g_vertexWkTitleLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

