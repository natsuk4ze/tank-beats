//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BULLET_MAX				(30)	// �o���b�g�ő吔
#define TEXTURE_BULLET_SIZE_X	(25/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(25/2)	// ����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 scl;		// �X�P�[��
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F

	float Bulletradian;		// sin��
	float fWidth;			// ��
	float fHeight;			// ����
	int	  nIdxShadow;		// �eID
	bool  use;				// �g�p���Ă��邩�ǂ���
	float Angle;			// ���ˊp�x
	float Range = 500.0f;   // �˒�
	float Radius;
	float BaseAngle;

} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void Bound(void);
int SetBullet(float fWidth, float fHeight, D3DXCOLOR col);
void SetFire(D3DXVECTOR3 pos);

BULLET *GetBullet(int no);

#endif


