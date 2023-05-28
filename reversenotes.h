//=============================================================================
//
// �t�m�[�c��ʏ��� [reversenotes.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _REVERSENOTES_H_
#define _REVERSENOTES_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_REVERSENOTES		("data/TEXTURE/notes001.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	REVERSENOTES_SIZE_X		(50.0)								// �t�m�[�c�̕�
#define	REVERSENOTES_SIZE_Y		(50.0)								// �t�m�[�c�̍���

typedef struct	// �t�m�[�c�\����
{
	D3DXVECTOR3		pos;											// �|���S���̈ړ���
	D3DXVECTOR3		rot;											// �|���S���̉�]��
	LPDIRECT3DTEXTURE9	Texture;									// �e�N�X�`�����
	VERTEX_2D	g_vertexWkReversenotes[NUM_VERTEX];					// ���_���i�[���[�N

	float			Radius;											// ���a
	float			BaseAngle;										// �p�x

	bool            use;

} REVERSENOTES;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitReversenotes(void);
void UninitReversenotes(void);
void UpdateReversenotes(void);
void DrawReversenotes(void);

REVERSENOTES *GetReversenotes(int no);

#endif
