//*****************************************************************************
//
// �T�E���h�̏��� [sound.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
//�T�E���h�̃N���X�錾
//*****************************************************************************
class CSound
{
public:
	//�\���̒�`(�Đ����e)
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,			// TITLEBGM
		SOUND_LABEL_GAMEBGM,				// GAMEBGM
		SOUND_LABEL_RESULTBGM,				// RESULTBGM
		SOUND_LABEL_SE_SHOT,				// �e���ˉ�
		SOUND_LABEL_SE_BUTTON,				// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,			// ������
		SOUND_LABEL_SE_SPEEDUP,				// �X�s�[�h�A�b�v
		SOUND_LABEL_MAX,					//�ő吔
	}SOUND_LABEL;

	CSound();								//�R���X�g���N�^
	~CSound();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT InitSound(HWND hWnd);			//�������֐�
	void UninitSound(void);					//�I���֐�
	HRESULT PlaySound(SOUND_LABEL label);	//�Đ��֐�
	void StopSound(SOUND_LABEL label);		//��~�֐�
	void StopSoundTo(void);					//�ꎞ��~�֐�

private:
	//�����o�ϐ�
	//�\���̒�`(�ϐ��錾)
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	//�`�F�b�N�`�����N
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	
	//�ǂݍ��݃`�F�b�N�`�����N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	

	IXAudio2 *m_pXAudio2 ;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];			// �e���f�ނ̃p�����[�^
};
#endif 