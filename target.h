//=============================================================================
//
// �^�[�Q�b�g���� [target.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_

#include "main.h"

#define TARGET_MAX (1)

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

} TARGET;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTarget(int type);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
void SetTarget(D3DXVECTOR3 pos);

TARGET *GetTarget(int no);

#endif
