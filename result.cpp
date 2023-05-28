//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "title.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo = NULL;		// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkResult[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkResultLogo[NUM_VERTEX];	// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT,				// �t�@�C���̖��O
								&g_pD3DTextureResult);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT_LOGO,		// �t�@�C���̖��O
								&g_pD3DTextureResultLogo);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexResult();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	if(g_pD3DTextureResult != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResult->Release();
		g_pD3DTextureResult = NULL;
	}

	if(g_pD3DTextureResultLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultLogo->Release();
		g_pD3DTextureResultLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���

		InitTitle();
		SetStage(STAGE_TITLE);
	}

	else if (IsButtonTriggered(0, BUTTON_C))
	{
		InitTitle();
		SetStage(STAGE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�

	pDevice->SetTexture(0, g_pD3DTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult(void)
{	
	// ���_���W�̐ݒ�
	g_vertexWkResult[0].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[1].vtx = D3DXVECTOR3(RESULT_POS_X + SCREEN_WIDTH, RESULT_POS_Y, 0.0f);
	g_vertexWkResult[2].vtx = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + SCREEN_HEIGHT, 0.0f);
	g_vertexWkResult[3].vtx = D3DXVECTOR3(RESULT_POS_X + SCREEN_WIDTH, RESULT_POS_Y + SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult[0].rhw =
	g_vertexWkResult[1].rhw =
	g_vertexWkResult[2].rhw =
	g_vertexWkResult[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkResultLogo[0].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y, 0.0f);
	g_vertexWkResultLogo[1].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y, 0.0f);
	g_vertexWkResultLogo[2].vtx = D3DXVECTOR3(RESULTLOGO_POS_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);
	g_vertexWkResultLogo[3].vtx = D3DXVECTOR3(RESULTLOGO_POS_X + RESULTLOGO_SIZE_X, RESULTLOGO_POS_Y + RESULTLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResultLogo[0].rhw =
	g_vertexWkResultLogo[1].rhw =
	g_vertexWkResultLogo[2].rhw =
	g_vertexWkResultLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResultLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResultLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResultLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResultLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResultLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResultLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

