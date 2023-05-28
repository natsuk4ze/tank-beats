//=============================================================================
//
// �v���C���[�p�[�ca���� [player_parts_a.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PLAYER_PARTS_A_H_
#define _PLYER_PARTS_A_H_

#include "main.h"

#define PLAYER_PARTS_A_MAX (1)
#define PLAYER_PARTS_A_MOVE (2.0f)
#define	VALUE_ROTATE_A	(D3DX_PI * 0.01f)		 // ��]��
#define TEXTURE_PLAYER_SIZE_X	(60/2)			 // �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(60/2)			 // ����

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3		move;
	D3DXVECTOR3		rotDest;
	bool            use;
	float			Radius;						// �v���C���[�̔��a
	float			BaseAngle;					// �v���C���[�̊p�x

} PLAYER_PARTS_A;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer_Parts_a(int type);
void UninitPlayer_Parts_a(void);
void UpdatePlayer_Parts_a(void);
void DrawPlayer_Parts_a(void);

PLAYER_PARTS_A *GetPlayer_Parts_a(int no);
D3DXMATRIX *GetPlayer_Parts_aWorldMatrix(void);

#endif

