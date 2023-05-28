//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author :natsuk4ze
//
//=============================================================================
#include "game.h"
#include "pause.h"
#include "result.h"
#include "sound.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "enemy.h"
#include "billboard.h"
#include "tree.h"
#include "particle.h"
#include "score.h"
#include "meshwall.h"
#include "target.h"
#include "player_parts_a.h"
#include "barrier.h"
#include "life.h"
#include "debugproc.h"
#include "bar.h"
#include "notes.h"
#include "reversenotes.h"
#include "star.h"
#include "circle.h"
#include "title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckHit(void);

bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	LPDIRECT3D9		g_pD3D = NULL;				// Direct3D �I�u�W�F�N�g
LPDIRECTSOUNDBUFFER8	g_pBGM;						// BGM�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���[�h�ƍĐ�
	g_pBGM = LoadSound(BGM_00);
	PlaySound(g_pBGM, E_DS8_FLAG_NONE);
	g_pBGM->SetVolume(DSBVOLUME_MIN/4);

	// �|�[�Y�̏�����
	InitPause();

	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// �e�̏�����
	InitShadow(0);

	// �p�[�e�B�N���̏�����
	InitParticle(0);

	// �o���b�g�̏�����
	InitBullet(0);

	// ���f���̏�����
	InitPlayer(0);

	// �G�l�~�[�̏�����
	InitEnemy(0);

	// �t�B�[���h�̏�����
	InitField(0);

	// �r���{�[�h�̏�����
	InitBillboard(0);
	
	// �^�[�Q�b�g�̏�����
	InitTarget(0);

	// �T�[�N���̏�����
	InitCircle(0);

	// �c���[�̏�����
	InitTree(0);

	// �X�R�A�̏�����
	InitScore();

	// �o�[�̏�����
	InitBar();

	// �X�^�[�̏�����
	InitStar();

	// �m�[�c�̏�����
	InitNotes();

	// �t�m�[�c�̏�����
	InitReversenotes();

	// �o���A�|�̏�����
	InitBarrier(0);

	// �v���C���[HP�̏�����
	InitLife();

	// �ǂ̏�����
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, FIELD_SCL), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(-FIELD_SCL, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(FIELD_SCL, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -FIELD_SCL), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, FIELD_SCL / 4, 80.0f);

	// ��(�����p)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, FIELD_SCL), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(-FIELD_SCL, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(FIELD_SCL, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, FIELD_SCL / 4, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -FIELD_SCL), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, FIELD_SCL / 4, 80.0f);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �T�E���h�����̏I������
	if (g_pD3D != NULL)
	{
		g_pBGM->Release();
		g_pBGM = NULL;
	}


	// �|�[�Y�����̏I������
	UninitPause();

	// �T�E���h�����̏I������
	UninitSound();

	// �o���b�g�̏I������
	UninitBullet();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �t�B�[���h�̏I������
	UninitField();

	// �e�̏I������
	UninitShadow();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �^�[�Q�b�g�̏I������
	UninitTarget();

	// �T�[�N���̏I������
	UninitCircle();

	// �؂̏I������
	UninitTree();

	// �p�[�e�B�N���̏I������
	UninitParticle();

	// �X�R�A�̏I������
	UninitScore();

	// �o�[�̏I������
	UninitBar();

	// �X�^�[�̏I������
	UninitStar();

	// �m�[�c�̏I������
	UninitNotes();

	// �t�m�[�c�̏I������
	UninitReversenotes();

	// �o���A�|�̏I������
	UninitBarrier();

	// �ǂ̏I������
	UninitMeshWall();

	// �v���C���[HP�̏I������
	UninitLife();

	// �T�E���h�̏I������
	UninitSound();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);	// �v���C���[�̃|�C���^�[��������
	PAUSE *pause = GetPause(0);								// �|�[�Y�̃|�C���^�[��������
	CURSOR *cursor = GetCursor(0);
	
															// �|�[�Y�X�V
	UpdatePause();

	if (GetKeyboardTrigger(DIK_P))
	{
		pause->use = pause->use ? false : true;

		if (pause->use == true)
		{// Enter��������A�X�e�[�W��؂�ւ���

		 // �Ȃ��~�߂�
			StopSound(g_pBGM);
		}
		else
		{
			if (IsPlaying(g_pBGM) == false)
			{
				PlaySound(g_pBGM, E_DS8_FLAG_LOOP);
			}
		}
	}

	if (pause->use == true)
	{
		if (cursor->State_Menu == 0)
		{
			if (GetKeyboardTrigger(DIK_RETURN))
			{// Enter��������A�X�e�[�W��؂�ւ���

			 //�`���[�g���A���̏���������
				InitTitle();
				SetStage(STAGE_TITLE);
			}
		}

		if (cursor->State_Menu == 1)
		{
			if (GetKeyboardTrigger(DIK_RETURN))
			{// Enter��������A�X�e�[�W��؂�ւ���
				if (IsPlaying(g_pBGM) == false)
				{
					PlaySound(g_pBGM, E_DS8_FLAG_LOOP);
				}

				pause->use = false;
			}
		}
	}

	if (pause->use == false)
	{
		if (player_parts_a->use == false)
		{
			// �Ȃ��~�߂�
			StopSound(g_pBGM);

			InitResult();
			SetStage(STAGE_RESULT);
		}

		if (IsPlaying(g_pBGM) == false)
		{// Enter��������A�X�e�[�W��؂�ւ���

		 // �Ȃ��~�߂�
			StopSound(g_pBGM);

			InitResult();
			SetStage(STAGE_RESULT);
		}

		// �c���[�X�V
		UpdateTree();

		// �o���b�g�̍X�V����
		UpdateBullet();

		// ���f���̍X�V����
		UpdatePlayer();

		// �v���C���[HP�̍X�V����
		UpdateLife();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();

		// �t�B�[���h�̍X�V����
		UpdateField();

		// �J�����̍X�V����
		UpdateCamera();

		// �r���{�[�h�̍X�V����
		UpdateBillboard();

		// �^�[�Q�b�g�̍X�V����
		UpdateTarget();

		// �T�[�N���̍X�V����
		UpdateCircle();

		// �p�[�e�B�N���̍X�V����
		UpdateParticle();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �o�[�̍X�V����
		UpdateBar();

		// �X�^�[�̍X�V����
		UpdateStar();

		// �m�[�c�̍X�V����
		UpdateNotes();

		// �t�m�[�c�̏I������
		UpdateReversenotes();

		// �o���A�|�̍X�V����
		UpdateBarrier();

		// �Ǐ����̍X�V
		UpdateMeshWall();

		// �e�̍X�V����
		UpdateShadow();

		// �����蔻��̍X�V����
		CheckHit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̕`�揈��
	DrawCamera();

	//// �e�̕`�揈��
	//DrawShadow();

	// �p�[�e�B�N���̕`�揈��
	DrawParticle();

	//DrawTree();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	//�G�l�~�[�̕`�揈��
	DrawEnemy();

	// �t�B�[���h�̕`�揈��
	DrawField();

	// �^�[�Q�b�g�̕`�揈��
	DrawTarget();

	// �T�[�N���̕`�揈��
	DrawCircle();

	// �o���A�|�̕`�揈��
	DrawBarrier();

	// �ǂ̕`�揈��
	DrawMeshWall();

	// �o���b�g�̕`�揈��
	DrawBullet();

	// �r���{�[�h�̕`�揈��
	DrawBillboard();

	// �v���C���[HP�̕`�揈��
	DrawLife();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �o�[�̕`�揈��
	DrawBar();

	// �X�^�[�̕`�揈��
	DrawStar();

	// �m�[�c�̕`�揈��
	DrawNotes();

	// �t�m�[�c�̕`�揈��
	DrawReversenotes();

	// �|�[�Y�̕`�揈��
	DrawPause();
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	ENEMY *enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������
	BULLET *bullet = GetBullet(0);			// �o���b�g�̃|�C���^�[��������
	PARTICLE *g_aParticle = GetParticle(0);	// �p�[�e�B�N���̃|�C���^�[��������
	BARRIER *barrier = GetBarrier(0);		// �o���A�|�̃|�C���^�[��������
	TARGET *target = GetTarget(0);			// �^�[�Q�b�g�̃|�C���^�[��������
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);

	int Enemycnt = 0;						// �G�̐��𐔂���


	// �G�Ƒ���L����(BB)
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == false)	continue;

		if (CheckHitBB(GetPlayer_Parts_a(0)->pos, enemy->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
		{
			// HP��������
			enemy->HP -= 1;

			if (enemy->HP <= 0)
			{
				enemy->use = false;	// �G�͓|�����
				ChangeScore(20);	// �X�R�A�v�Z
			}

			ChangeLife(-1);
		}
	}

	// �e�ƓG(BC)
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// �G�l�~�[�̃|�C���^�[��������
		enemy = GetEnemy(0);

		if (bullet->use == false) continue;

		for (int j = 0; j < ENEMY_MAX; j++, enemy++)
		{
			if (enemy->use == false) continue;

			if (CheckHitBC(bullet->pos, enemy->pos, TEXTURE_BULLET_SIZE_X, TEXTURE_ENEMY_SIZE_X))
			{
				// �p�[�e�B�N���̏�����
				for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
				{
					g_aParticle[nCntParticle].use = false;

					g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aParticle[nCntParticle].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
					g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aParticle[nCntParticle].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
					g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//���ˋ����Ɗp�x�����߂�
					g_aParticle[nCntParticle].Angle = (float)(50.0 + rand() % 360) / 100.0f;
					g_aParticle[nCntParticle].Length = (float)(rand() % 10) / 1.0f;
					g_aParticle[nCntParticle].hight = (float)(30.0 + rand() % 200) / 1.0f;
					g_aParticle[nCntParticle].Size = (float)(10.0 + rand() % 20) / 30.0f;

					g_aParticle[nCntParticle].move.x = sinf(g_aParticle[0].Angle) *g_aParticle[nCntParticle].Length;
					g_aParticle[nCntParticle].move.z = cosf(g_aParticle[0].Angle) *g_aParticle[nCntParticle].Length;
					g_aParticle[nCntParticle].move.y = g_aParticle[nCntParticle].hight;
					g_aParticle[nCntParticle].scl.x = g_aParticle[nCntParticle].Size;
					g_aParticle[nCntParticle].scl.y = g_aParticle[nCntParticle].Size;
					g_aParticle[nCntParticle].scl.z = g_aParticle[nCntParticle].Size;

					g_aParticle[nCntParticle].fWidth = PARTICLE_WIDTH;
					g_aParticle[nCntParticle].fHeight = PARTICLE_HEIGHT;

					//�p�[�e�B�N���̐ݒ�
					SetParticle(30.0f, 30.0f, g_aParticle[nCntParticle].col);
					g_aParticle[nCntParticle].Particleradian = 0.0f;
				}

				// �e�̏��ŏ������s��
				bullet->use = false;
				enemy->HP -= 1;

				if (enemy->HP <= 0)
				{
					enemy->use = false;	// �G�͓|�����
					ChangeScore(20);	// �X�R�A�v�Z
				}

				D3DXVECTOR3 pos = enemy->pos;
				SetEffect(pos);
			}
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)
		{
			Enemycnt++;
		}
	}

	// ���������ʓG���S�ŁH
	if (Enemycnt == 0)
	{
		//�G�l�~�[��������(�ă|�b�v)
		InitEnemy(1);

		target->use = false;
	}
}

//=============================================================================
// BB(�o�E���f�B���O�{�b�N�X)�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	size1 /= 2.0f;	// ���T�C�Y�ɂ���
	size2 /= 2.0f;	// ����

	if (pos2.x + size2.x > pos1.x - size1.x && pos1.x + size1.x > pos2.x - size2.x &&
		pos2.z + size2.y > pos1.z - size1.y && pos1.z + size1.y > pos2.z - size2.y)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC(�o�E���f�B���O�T�[�N��)�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2) * (size1 + size2) >
		(pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.z - pos2.z) * (pos1.z - pos2.z))
	{
		return true;
	}

	return false;
}

