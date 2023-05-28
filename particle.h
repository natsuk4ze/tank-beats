//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PARTICLE_MAX			(20)	// �p�[�e�B�N���ő吔
#define	PARTICLE_WIDTH			(1.0f)	// �e�̔��a��
#define	PARTICLE_HEIGHT			(1.0f)	// �e�̔��a��

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
	D3DXCOLOR col;			//�F

	float Particleradian;	//sin��
	float fWidth;			// ��
	float fHeight;			// ����
	int nIdxShadow;			// �eID
	float Angle;			//���ˊp�x
	float hight;            //�o�E���h�̍���
	float Length;			//���ˋ���
	float Size;				//�傫��

	bool use;				// �g�p���Ă��邩�ǂ���

} PARTICLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitParticle(int type);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void Bound(void);
int SetParticle(float fWidth, float fHeight, D3DXCOLOR col);
void SetEffect(D3DXVECTOR3 pos);

PARTICLE *GetParticle(int no);

#endif

