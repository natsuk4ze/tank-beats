//=============================================================================
//
// �v���C���[�p�[�cb���� [player_parts_b.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_PARTS_B_H_
#define _PLYER_PARTS_B_H_

#include "main.h"

#define PLAYER_PARTS_B_MAX (1)
#define	VALUE_ROTATE_B	(D3DX_PI * 0.013f)		// ��]��

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3		move;						// ���f���̑傫��(�X�P�[��)

	float           Angle;
	float           targetdistance;

} PLAYER_PARTS_B;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer_Parts_b(int type);
void UninitPlayer_Parts_b(void);
void UpdatePlayer_Parts_b(void);
void DrawPlayer_Parts_b(void);

PLAYER_PARTS_B *GetPlayer_Parts_b(int no);
D3DXMATRIX *GetPlayer_Parts_bWorldMatrix(void);

#endif

