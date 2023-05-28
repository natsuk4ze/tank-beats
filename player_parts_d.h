//=============================================================================
//
// �v���C���[�p�[�cd���� [player_parts_d.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_PARTS_D_H_
#define _PLYER_PARTS_D_H_

#include "main.h"

#define PLAYER_PARTS_D_MAX (1)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3		move;						// �ړ���

	float Angle;
	float radian;
	float targetdistance;
	bool FireEffectUse;							//���˃G�t�F�N�g�g�p���

} PLAYER_PARTS_D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer_Parts_d(int type);
void UninitPlayer_Parts_d(void);
void UpdatePlayer_Parts_d(void);
void DrawPlayer_Parts_d(void);

PLAYER_PARTS_D *GetPlayer_Parts_d(int no);

#endif



