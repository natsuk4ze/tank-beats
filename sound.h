//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : natsuk4ze
//
//=============================================================================

#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// �}�N����`
enum
{	// �T�E���h�ʂ��i���o�[
	BGM_00,
	SE_00,
	SOUND_MAX
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���

#endif