//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIAL		("data/TEXTURE/how2control-1.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIAL_LOGO	("data/TEXTURE/logo001.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TUTORIAL_POS_X			(0)									// �`���[�g���A���̕\���ʒu
#define	TUTORIAL_POS_Y			(0)									// �`���[�g���A���̕\���ʒu
#define	TUTORIAL_SIZE_X		(SCREEN_WIDTH)							// �`���[�g���A���̕�
#define	TUTORIAL_SIZE_Y		(SCREEN_HEIGHT)							// �`���[�g���A���̍���
#define	TUTORIALLOGO_POS_X		(SCREEN_WIDTH/2 - 400)				// �`���[�g���A�����S�̕\���ʒu
#define	TUTORIALLOGO_POS_Y		(700)								// �`���[�g���A�����S�̕\���ʒu
#define	TUTORIALLOGO_SIZE_X	(700)									// �`���[�g���A�����S�̕�
#define	TUTORIALLOGO_SIZE_Y	(200)									// �`���[�g���A�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif

