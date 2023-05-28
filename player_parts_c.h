//=============================================================================
//
// �v���C���[�p�[�cc���� [player_parts_c.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_PARTS_C_H_
#define _PLYER_PARTS_C_H_

#include "main.h"

#define PLAYER_PARTS_C_MAX (1)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)

} PLAYER_PARTS_C;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer_Parts_c(int type);
void UninitPlayer_Parts_c(void);
void UpdatePlayer_Parts_c(void);
void DrawPlayer_Parts_c(void);

PLAYER_PARTS_C *GetPlayer_Parts_c(int no);

#endif


