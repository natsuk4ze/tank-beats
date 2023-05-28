//=============================================================================
//
// �o�[��ʏ��� [bar.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _BAR_H_
#define _BAR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BAR		("data/TEXTURE/bar001.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BAR_SIZE_X		(770.0)						// �o�[�̕�
#define	BAR_SIZE_Y		(80.0)						// �o�[�̍���

typedef struct	// �o�[�\����
{
	D3DXVECTOR3		pos;							// �|���S���̈ړ���
	D3DXVECTOR3		rot;							// �|���S���̉�]��
	LPDIRECT3DTEXTURE9	Texture;					// �e�N�X�`�����
	VERTEX_2D	g_vertexWkBar[NUM_VERTEX];			// ���_���i�[���[�N

	float			Radius;							// ���a
	float			BaseAngle;						// �p�x

} BAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBar(void);
void UninitBar(void);
void UpdateBar(void);
void DrawBar(void);

BAR *GetBar(int no);

#endif
