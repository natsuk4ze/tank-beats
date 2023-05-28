//=============================================================================
//
// �o���A�|���� [barrier.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"

#define BARRIER_MAX (1)
#define TEXTURE_BARRIER_SIZE_X	(25/2) // �e�N�X�`���T�C�Y
#define TEXTURE_BARRIER_SIZE_Y	(25/2) // ����

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �o���A�|�\����
{
	D3DXVECTOR3		pos;				// �|���S���̈ړ���
	D3DXVECTOR3		rot;				// �|���S���̉�]��
	D3DXVECTOR3		scl;				// ���f���̑傫��(�X�P�[��)

	bool		    use;                // �g�p���Ă��邩�ǂ���
	float           radian;
	float			Radius;
	float			BaseAngle;

} BARRIER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBarrier(int type);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
void SetBarrier(D3DXVECTOR3 pos);

BARRIER *GetBarrier(int no);

#endif
