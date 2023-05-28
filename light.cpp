//=============================================================================
//
// ���C�e�B���O���� [player.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_LIGHT		(3)					// ���C�g�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9			g_aLight[NUM_LIGHT];	// ���C�g���

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U���̐ݒ�
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̊����̐ݒ�
	g_aLight[0].Ambient = D3DXCOLOR(0.75f, 0.75f, 0.750f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	pDevice->LightEnable(0, TRUE);

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g1�̃^�C�v�̐ݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g1�̊g�U���̐ݒ�
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g1�̊����̐ݒ�
	g_aLight[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ���C�g1�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	// ���C�g1�̐ݒ�
	pDevice->LightEnable(1, TRUE);

	// ���C�e�B���O���[�h��ON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
