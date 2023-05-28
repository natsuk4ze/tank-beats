//=============================================================================
//
// ���f������ [camera.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "input.h"
#include "player_parts_a.h"
#include <math.h>
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_CAMERA_P_X	(-200.0f)										// �J�������_�̏����ʒu(X���W)
#define	POS_CAMERA_P_Y	(100.0f)										// �J�������_�̏����ʒu(Y���W)
#define	POS_CAMERA_P_Z	(-200.0f)										// �J�������_�̏����ʒu(Z���W)
#define CAMERA_MOVE (5.0f)												//�J�����̈ړ���
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3			g_posCameraEye;			// �J�����̎��_
D3DXVECTOR3			g_posCameraAt;			// �J�����̒����_
D3DXVECTOR3			g_vecCameraUp;			// �J�����̏�����x�N�g��
D3DXVECTOR3			g_rotCamera;			// �J�����̉�]

float			    Cameraradian;			//�J�����̊p�x
float				Cameraradius;			//�����_�𒆐S�Ƃ����~�̔��a

D3DXMATRIX			g_mtxView;				// �r���[�}�g���b�N�X
D3DXMATRIX			g_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X


//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);			// �v���C���[�̃|�C���^�[��������

	g_posCameraEye = D3DXVECTOR3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	g_posCameraAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Cameraradian = 0.0f;

	//�����_���v���C���[�ɃZ�b�g
	g_posCameraAt = player_parts_a->pos;

	//�J�����ƃv���C���[�̋���
	Cameraradius = sqrtf(
		(powf((g_posCameraEye.z - g_posCameraAt.z), 2.0f))
		+ (powf((g_posCameraEye.x - g_posCameraAt.x), 2.0f))
	);
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);			// �v���C���[�̃|�C���^�[��������

	g_posCameraEye.x = player_parts_a->pos.x + cosf(Cameraradian) *Cameraradius*1.50f;
	g_posCameraEye.z = player_parts_a->pos.z - sinf(Cameraradian) *Cameraradius*1.50f;
	g_posCameraEye.y = player_parts_a->pos.y + 300.0f;

	g_posCameraAt = player_parts_a->pos;


	////�v���C���[�ƃJ�����̋�����ύX
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	Cameraradius += 5.0f;

	//}

	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	Cameraradius -= 5.0f;

	//}

	//�J�����̊p�x��ύX
	if (GetKeyboardPress(DIK_1))
	{
		Cameraradian += 0.05f;
	}
	else if(IsButtonPressed(0,BUTTON_L))
	{
		Cameraradian += 0.05f;
	}

	if (GetKeyboardPress(DIK_2))
	{
		Cameraradian -= 0.05f;
	}
	else if (IsButtonPressed(0, BUTTON_R))
	{
		Cameraradian -= 0.05f;
	}

	if (Cameraradius <= 50.0f)
	{
		Cameraradius = 50.0f;
	}

	if (GetKeyboardPress(DIK_3))
	{
		g_posCameraEye = D3DXVECTOR3(player_parts_a->pos.x, player_parts_a->pos.y + 500.0f, player_parts_a->pos.z);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,		// �J�����̎��_
		&g_posCameraAt,			// �J�����̒����_
		&g_vecCameraUp);		// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	// �v���W�F�N�V����(���e�ϊ�)�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}



