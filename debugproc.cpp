//=============================================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : natsuk4ze
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "debugproc.h"
#include "player_parts_a.h"
#include "player_parts_b.h"
#include "player_parts_c.h"
#include "player_parts_d.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "target.h"
#include "circle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	LPD3DXFONT	g_pD3DXFont = NULL;	// �t�H���g�ւ̃|�C���^
char		g_aStrDebug[1024] = {"\0"};	// �f�o�b�O���


//=============================================================================
// �f�o�b�O�\�������̏�����
//=============================================================================
HRESULT InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// �f�o�b�O�\�������̏I������
//=============================================================================
void UninitDebugProc(void)
{
	if(g_pD3DXFont != NULL)
	{// ���\���p�t�H���g�̊J��
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}

//=============================================================================
// �f�o�b�O�\�������̍X�V����
//=============================================================================
void UpdateDebugProc(void)
{
	PLAYER_PARTS_A *player_parts_a = GetPlayer_Parts_a(0);
	PLAYER_PARTS_B *player_parts_b = GetPlayer_Parts_b(0);
	PLAYER_PARTS_C *player_parts_c = GetPlayer_Parts_c(0);
	PLAYER_PARTS_D *player_parts_d = GetPlayer_Parts_d(0);
	TARGET *target = GetTarget(0);
	CIRCLE *circle = GetCircle(0);
	ENEMY *enemy = GetEnemy(0);
	BULLET *bullet = GetBullet(0);


	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");

	PrintDebugProc("[���ˊp�x  �F(%f)]\n", bullet->Angle);
	PrintDebugProc("[��C�̌���  �F(%f)]\n", player_parts_b->rot.y);
	PrintDebugProc("[�^�[�Q�b�g�̈ʒu  �F(%f : %f : %f)]\n", target->pos.x, target->pos.y, target->pos.z);
	PrintDebugProc("[�v���C���[�̈ʒu  �F(%f : %f : %f)]\n", player_parts_a->pos.x, player_parts_a->pos.y, player_parts_a->pos.z);

	PrintDebugProc("\n");

	PrintDebugProc("*** �ԑ��� ***\n");
	PrintDebugProc("�O�ړ� : W\n");
	PrintDebugProc("��ړ� : S\n");
	PrintDebugProc("������ : Q\n");
	PrintDebugProc("�E���� : E\n");
	PrintDebugProc("��C�捶���� : ��\n");
	PrintDebugProc("��C�捶���� : ��\n");
	PrintDebugProc("\n");

	PrintDebugProc("[�T�[�N���̃T�C�Y  �F(%f :�@)]\n", circle->Size);

	PrintDebugProc("\n");

}

//=============================================================================
// �f�o�b�O�\�������̕`�揈��
//=============================================================================
void DrawDebugProc(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// ���\��
	g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
//=============================================================================
void PrintDebugProc(const char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
	va_start(list, fmt);

	pCur = (char *)fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if((strlen(g_aStrDebug) + strlen(aBuf)) < ((sizeof g_aStrDebug) - 1))
	{
		strcat(g_aStrDebug, aBuf);
	}
#endif
}
