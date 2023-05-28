//=============================================================================
//
// �v���C���[�p�[�ce���� [player_parts_e.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_PARTS_E_H_
#define _PLYER_PARTS_D_H_

#include "main.h"

#define PLAYER_PARTS_E_MAX (1)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)

} PLAYER_PARTS_E;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer_Parts_e(int type);
void UninitPlayer_Parts_e(void);
void UpdatePlayer_Parts_e(void);
void DrawPlayer_Parts_e(void);

PLAYER_PARTS_E *GetPlayer_Parts_e(int no);

#endif


