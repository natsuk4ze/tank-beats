//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		("data/TEXTURE/title004.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LOGO	("data/TEXTURE/logo002.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLE_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X		(SCREEN_WIDTH)					// �^�C�g���̕�
#define	TITLE_SIZE_Y		(SCREEN_HEIGHT)					// �^�C�g���̍���
#define	TITLELOGO_POS_X		(SCREEN_WIDTH/2 - 400)			// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(700)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(700)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(200)							// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
