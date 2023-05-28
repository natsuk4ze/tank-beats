//=============================================================================
//
// ���U���g��ʏ��� [result.h]
// Author : natsuk4ze
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT      ("data/TEXTURE/gameover001.png")// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_LOGO	("data/TEXTURE/logo001.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_POS_X			(0)							// ���U���g�̕\���ʒu
#define	RESULT_POS_Y			(0)							// ���U���g�̕\���ʒu
#define	RESULT_SIZE_X			(800)						// ���U���g�̕�
#define	RESULT_SIZE_Y			(600)						// ���U���g�̍���
#define	RESULTLOGO_POS_X		(SCREEN_WIDTH/2-330)		// ���U���g���S�̕\���ʒu
#define	RESULTLOGO_POS_Y		(650)						// ���U���g���S�̕\���ʒu
#define	RESULTLOGO_SIZE_X		(700)						// ���U���g���S�̕�
#define	RESULTLOGO_SIZE_Y		(200)						// ���U���g���S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif
