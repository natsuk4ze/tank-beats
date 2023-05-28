//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "player_parts_a.h"
#include "target.h"
#include "debugproc.h"
#include "main.h"
#include "circle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_CAR		"data/MODEL/enemy000/enemy000.x"// �ǂݍ��ރG�l�~�[��
#define TEXTURE_FILENAME	"data/TEXTURE/pink001.jpg"

#define	VALUE_MOVE		(0.1f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��
#define SPAWNSQUARE1		(60.0f/2)					// �G�l�~�[���X�|�[�����Ȃ������͈̔�
#define SPAWNSQUARE2		(50.0f)						// �G�l�~�[���X�|�[������O���͈̔�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Homing(void);
void Targeting(void);
void Spawn(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			g_pD3DXMeshEnemy;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatEnemy;	// �}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatEnemy;			// �}�e���A�����̐�

D3DXVECTOR3			homingTarget;			//�z�[�~���O��̍��W������
D3DXMATRIX			ENEMY_g_mtxWorld;		// ���[���h�}�g���b�N�X

ENEMY				enemyWk[ENEMY_MAX];		// �G�l�~�[�\����
D3DXVECTOR3			pos[ENEMY_MAX];         // �G�l�~�[���W�z��
D3DXVECTOR3		the_nearest_enemy_pos;	    // �v���C���[�ƍł��߂������ɂ���G�l�~�[�̃|�W�V����

static	int				g_nIdxShadow;		// �eID
static	float			g_fSizeShadow;		// �e�̃T�C�Y
static	D3DXCOLOR		g_colShadow;		// �e�̐F

float enemyAngle;							// �z�[�~���O��Ƃ̊p�x
float homingRadius_x;						// �z�[�~���O��Ƃ̋���x
float homingRadius_z;						// �z�[�~���O��Ƃ̋���z

float playerdistance[ENEMY_MAX];
float min;
float Spawn_x;
float Spawn_z;
float enemyAntiSpawn_x1;                // �G�l�~�[���X�|�[�����Ȃ�X1���W
float enemyAntiSpawn_z1;				// �G�l�~�[���X�|�[�����Ȃ�Z1���W
float enemyAntiSpawn_x2;                // �G�l�~�[���X�|�[�����Ȃ�X2���W
float enemyAntiSpawn_z2;				// �G�l�~�[���X�|�[�����Ȃ�Z2���W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);	// �v���C���[�̃|�C���^�[��������
	playerdistance[ENEMY_MAX] = {};
	pos[ENEMY_MAX] = {};

	srand((unsigned)time(NULL));

	int data = 0;

	//data = 30 + rand() % (300);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;

		//Spawn();
		//enemy->pos = D3DXVECTOR3(Spawn_x, 0.0f, Spawn_z);

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		if (i == 0)
		{
			enemy->pos = D3DXVECTOR3(100.0f + float(data), 0.0f, 100.0f);
		}

		if (i == 1)
		{
			enemy->pos = D3DXVECTOR3(300.0f + float(data), 0.0f, 0.0f);
		}

		if (i == 2)
		{
			enemy->pos = D3DXVECTOR3(-300.0f + float(data), 0.0f, 0.0f);
		}

		if (i == 3)
		{
			enemy->pos = D3DXVECTOR3(0.0f, 0.0f, 300.0f + float(data));
		}

		if (i == 4)
		{
			enemy->pos = D3DXVECTOR3(0.0f, 0.0f, -300.0f + float(data));
		}

		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		enemy->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		enemy->HP = ENEMY_HP;
		enemyAngle = 0;													// �z�[�~���O��Ƃ̊p�x��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);									// �G�l�~�[�̔��a��������
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		//	// �e�̐���
		//g_nIdxShadow = CreateShadow(enemy->pos, 25.0f, 25.0f);
		//g_fSizeShadow = 25.0f;
		//g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}

	g_pD3DTextureEnemy = NULL;
	g_pD3DXMeshEnemy = NULL;
	g_pD3DXBuffMatEnemy = NULL;
	g_nNumMatEnemy = 0;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMY_CAR,				// �ǂݍ��ރG�l�~�[�t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,								// ���b�V���̍쐬�I�v�V�������w��
		pDevice,										// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,											// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&g_pD3DXBuffMatEnemy,							// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,											// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&g_nNumMatEnemy,								// D3DXMATERIAL�\���̂̐�
		&g_pD3DXMeshEnemy)))							// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}

	the_nearest_enemy_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �v���C���[�Ƃ̋�����������
	min = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}

	if (g_pD3DXMeshEnemy != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshEnemy->Release();
		g_pD3DXMeshEnemy = NULL;
	}

	if (g_pD3DXBuffMatEnemy != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatEnemy->Release();
		g_pD3DXBuffMatEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);
	TARGET *target = GetTarget(0);
	CIRCLE *circle = GetCircle(0);

	enemyAntiSpawn_x1 = player_parts_a->pos.x + SPAWNSQUARE1;
	enemyAntiSpawn_x2 = player_parts_a->pos.x - SPAWNSQUARE1;
	enemyAntiSpawn_z1 = player_parts_a->pos.z + SPAWNSQUARE1;
	enemyAntiSpawn_z2 = player_parts_a->pos.z - SPAWNSQUARE1;

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		playerdistance[i] = hypotf((enemy->pos.x - player_parts_a->pos.x), (enemy->pos.z - player_parts_a->pos.z));
		pos[i] = enemy->pos;

		if (enemy->use == false)
		{
			// ���i�{���͍\���̂̒��g�S�Ă��������������j
			enemy->pos = {};
			target->use = false;
			circle->use = false;	
		}

		Homing();

		Targeting();

		enemy->rot.y += VALUE_ROTATE;

		//// �e�̈ʒu�ݒ�
		//SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(enemy->pos.x, 0.1f, enemy->pos.z));
		//SetVertexShadow(g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
		//SetColorShadow(g_nIdxShadow, g_colShadow);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	ENEMY *enemy = &enemyWk[0];

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&ENEMY_g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, enemy->scl.x, enemy->scl.y, enemy->scl.z);
			D3DXMatrixMultiply(&ENEMY_g_mtxWorld, &ENEMY_g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->rot.y, enemy->rot.x, enemy->rot.z);
			D3DXMatrixMultiply(&ENEMY_g_mtxWorld, &ENEMY_g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy->pos.x, enemy->pos.y, enemy->pos.z);
			D3DXMatrixMultiply(&ENEMY_g_mtxWorld, &ENEMY_g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &ENEMY_g_mtxWorld);

			// ���݂̃}�e���A�����擾(���ɖ߂����߂̃o�b�N�A�b�v)
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemy);

				// �`��
				g_pD3DXMeshEnemy->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// �z�[�~���O����
//=============================================================================
void Homing(void)
{
	ENEMY *enemy = &enemyWk[0];
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);			// �v���C���[�̃|�C���^�[��������
	TARGET *target = GetTarget(0);


	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			//�z�[�~���O���ݒ�
			homingTarget = player_parts_a->pos;

			//�z�[�~���O��Ƃ̋���
			homingRadius_x = homingTarget.x - enemy->pos.x;
			homingRadius_z = homingTarget.z - enemy->pos.z;


			enemyAngle = atan2f(homingRadius_x, homingRadius_z);

			enemy->pos.x += sinf(enemyAngle)*VALUE_MOVE;
			enemy->pos.z += cosf(enemyAngle)*VALUE_MOVE;
		}
	}
}

//=============================================================================
// �^�[�Q�b�e�B���O����
//=============================================================================
void Targeting(void)
{
	ENEMY *enemy = &enemyWk[0];
	TARGET *target = GetTarget(0);
	CIRCLE *circle = GetCircle(0);


	// �ŏ��l���߂�
	min = playerdistance[0];

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (min >= playerdistance[j])
		{
			min = playerdistance[j];
			the_nearest_enemy_pos = D3DXVECTOR3(pos[j].x, pos[j].y, pos[j].z);
		}
	}

	// �^�[�Q�b�g���Z�b�g
	D3DXVECTOR3 pos = the_nearest_enemy_pos;
	SetTarget(pos);
	SetCircle(pos);
}

//=============================================================================
// �X�|�[������
//=============================================================================
void Spawn(void)
{
	float enemySpawn_x = 0;						// �G�l�~�[���X�|�[������X���W
	float enemySpawn_z = 0;						// �G�l�~�[���X�|�[������Z���W
	Spawn_x = 0;
	Spawn_z = 0;

	srand((unsigned)time(NULL));
	enemySpawn_x = float(-int(SPAWNSQUARE2) + rand() % (int SPAWNSQUARE2 * 2));

	srand((unsigned)time(NULL));
	enemySpawn_z = float(-int(SPAWNSQUARE2) + rand() % (int SPAWNSQUARE2 * 2));

	while (1)
	{
		srand((unsigned)time(NULL));
		enemySpawn_x = float(-int(SPAWNSQUARE2) + rand() % (int SPAWNSQUARE2 * 2));

		srand((unsigned)time(NULL));
		enemySpawn_z = float(-int(SPAWNSQUARE2) + rand() % (int SPAWNSQUARE2 * 2));


		if (
			(enemySpawn_x >= enemyAntiSpawn_x1) || (enemySpawn_x <= enemyAntiSpawn_x2)
			|| (enemySpawn_z >= enemyAntiSpawn_z1) || (enemySpawn_z <= enemyAntiSpawn_z2)
			)
		{
			Spawn_x = enemySpawn_x;
			Spawn_z = enemySpawn_z;

			break;
		}
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}
