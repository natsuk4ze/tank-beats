//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _ENMEY_H_
#define _ENEMY_H_

#include "main.h"

#define BOOST_MAX (2)
#define ENEMY_MAX (5)
#define TEXTURE_ENEMY_SIZE_X	(50/2)			// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(40/2)			// ����
#define ENEMY_HP  (1.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		scl;						// ���f���̑傫��(�X�P�[��)

	float           playerdistance;             // �v���C���[�Ƃ̋���
	float			Radius;
	float			BaseAngle;
	float           HP;
	bool            use;

} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(int no);
#endif

