//=============================================================================
//
// �X�^�[��ʏ��� [star.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _STAR_H_
#define _STAR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_STAR		("data/TEXTURE/starstar003.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	STAR_SIZE_X		(70.0)									// �X�^�[�̕�
#define	STAR_SIZE_Y		(70.0)									// �X�^�[�̍���

typedef struct	// �X�^�[�\����
{
	D3DXVECTOR3		pos;										// �|���S���̈ړ���
	D3DXVECTOR3		rot;										// �|���S���̉�]��
	LPDIRECT3DTEXTURE9	Texture;								// �e�N�X�`�����
	VERTEX_2D	g_vertexWkStar[NUM_VERTEX];						// ���_���i�[���[�N

	float			Radius;										// ���a
	float			BaseAngle;									// �p�x

} STAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStar(void);
void UninitStar(void);
void UpdateStar(void);
void DrawStar(void);

STAR *GetStar(int no);

#endif
