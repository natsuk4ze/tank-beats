//=============================================================================
//
// �|�[�Y��ʏ��� [pause.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PAUSE		("data/TEXTURE/pausemenu004.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSEMENU001	("data/TEXTURE/gototitle.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSEMENU002	("data/TEXTURE/backtogame001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CURSOR			("data/TEXTURE/cursor.png")				// �ǂݍ��ރe�N�X�`���t�@�C����

#define	PAUSE_POS_X			(SCREEN_WIDTH/2-PAUSE_SIZE_X/2)				// �|�[�Y�̕\���ʒu
#define	PAUSE_POS_Y			(SCREEN_HEIGHT/2-PAUSE_SIZE_Y/2)			// �|�[�Y�̕\���ʒu
#define	PAUSE_SIZE_X		(SCREEN_WIDTH/2)							// �|�[�Y�̕�
#define	PAUSE_SIZE_Y		(SCREEN_HEIGHT/2)							// �|�[�Y�̍���
#define	PAUSEMENU001_POS_X		(SCREEN_WIDTH/2-PAUSE_SIZE_X/2+200)		// �|�[�Y���S�̕\���ʒu
#define	PAUSEMENU001_POS_Y		(SCREEN_HEIGHT/2-PAUSE_SIZE_Y/2+150)	// �|�[�Y���S�̕\���ʒu
#define	PAUSEMENU001_SIZE_X	(600)										// �|�[�Y���S�̕�
#define	PAUSEMENU001_SIZE_Y	(100)										// �|�[�Y���S�̍���
#define	PAUSEMENU002_POS_X		(SCREEN_WIDTH/2-PAUSE_SIZE_X/2+200)		// �|�[�Y���S�̕\���ʒu
#define	PAUSEMENU002_POS_Y		(SCREEN_HEIGHT/2-PAUSE_SIZE_Y/2+300)	// �|�[�Y���S�̕\���ʒu
#define	PAUSEMENU002_SIZE_X	(600)										// �|�[�Y���S�̕�
#define	PAUSEMENU002_SIZE_Y	(100)										// �|�[�Y���S�̍���
#define	CURSOR_SIZE_X		(70.0)										// �J�[�\���̕�
#define	CURSOR_SIZE_Y		(70.0)										// �J�[�\���̍���
#define	CURSOR_MAX           (1)											//�@�J�[�\���̐�
#define PAUSE_MAX (1)
#define MENU_MAX (2)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �J�[�\���\����
{
	D3DXVECTOR3		pos;										// �|���S���̈ړ���
	D3DXVECTOR3		rot;										// �|���S���̉�]��
	LPDIRECT3DTEXTURE9	Texture;								// �e�N�X�`�����
	VERTEX_2D	g_vertexWkCursor[NUM_VERTEX];					// ���_���i�[���[�N

	float			Radius;										// ���a
	float			BaseAngle;									// �p�x
	int				State_Menu;

} CURSOR;

typedef struct	// �|�[�Y�\����
{
	bool            use;

} PAUSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
PAUSE *GetPause(int no);
CURSOR*GetCursor(int no);

#endif
