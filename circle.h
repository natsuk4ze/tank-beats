//=============================================================================
//
// �T�[�N������ [circle.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "main.h"

#define CIRCLE_MAX (1)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �v���C���[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3	    move;				        // �ړ���

	bool		    use;						// �g�p���Ă��邩�ǂ���

	float			Size;

} CIRCLE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCircle(int type);
void UninitCircle(void);
void UpdateCircle(void);
void DrawCircle(void);
void SetCircle(D3DXVECTOR3 pos);
void GetParameter(void);
bool CanAtack();

CIRCLE *GetCircle(int no);

#endif
