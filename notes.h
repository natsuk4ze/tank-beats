//=============================================================================
//
// �m�[�c��ʏ��� [notes.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _NOTES_H_
#define _NOTES_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NOTES		("data/TEXTURE/notes001.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	NOTES_SIZE_X		(50.0)							// �m�[�c�̕�
#define	NOTES_SIZE_Y		(50.0)							// �m�[�c�̍���
#define NOTES_INTERVAL		(150.0f)						// �m�[�c�̊Ԋu

typedef struct	// �m�[�c�\����
{
	D3DXVECTOR3		pos;									// �|���S���̈ړ���
	D3DXVECTOR3		rot;									// �|���S���̉�]��
	LPDIRECT3DTEXTURE9	Texture;							// �e�N�X�`�����
	VERTEX_2D	g_vertexWkNotes[NUM_VERTEX];				// ���_���i�[���[�N

	float			Radius;									// ���a
	float			BaseAngle;								// �p�x

	bool			use;

} NOTES;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitNotes(void);
void UninitNotes(void);
void UpdateNotes(void);
void DrawNotes(void);

NOTES *GetNotes(int no);

#endif
