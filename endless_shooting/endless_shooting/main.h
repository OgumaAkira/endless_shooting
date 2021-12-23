//*****************************************************************************
//
// ���C������ [main.h]
// Author : ���F �N
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <time.h>
#include <d3dx9.h>
#include <xaudio2.h> //�T�E���h�����ŕK�v
#include <windows.h>
#define DIRECTINPUT_VERSION (0x0800) //�x���Ώ��p dinput.h�̒��O�ɏ���
#include <dinput.h>
#include <vector>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"										//�E�C���h�E�̃N���X��
#define WINDOW_NAME		"DISK BREAK"									//�E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH	(1920)											//�E�B���h�E�̉�
#define SCREEN_HEIGHT	(1080)											//�E�B���h�E�̏c
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX (4)													//���_��
#define NUM_POLYGON (2)													//�|���S����
#define NUM_KEY_MAX (256)												//�L�[�{�[�h�̍ő吔
#define NUM_MOUSE_MAX (4)												//�}�E�X�L�[�̍ő吔
#define BULLET_SIZEX (150.0f)											//�eX�̒���
#define BULLET_SIZEY (150.0f)											//�eY�̒���
#define	MAX_FLASHING (30)												//�t���b�V������t���[���b��
#define MAX_BULLET	 (5)												//�ő�e��
#define DEBUG_SOUND (0)

//�e�N�X�`���}�N��
#define MAX_TEXTURE (516)												//�e�N�X�`���̍ő喇��
#define BULLETUI_TEXTURE ("data/TEXTURE/BULLET.png")					//�c�e��TEXTURE

#define ENEMY_TEXTURE2 ("data/TEXTURE/�G�@UFO�P.png")					//�G��TEXTURE

#define PAUSEBUTTON_TEXTURE ("data/TEXTURE/PAUSE_WINDOW.png")			//�|�[�Y�̃e�N�X�`��
#define TITLERETURNBUTTON_TEXTURE ("data/TEXTURE/TITLE_RETURN.png")		//TITLE�ɖ߂�{�^���̃e�N�X�`��
#define GAMERETURNBUTTON_TEXTURE ("data/TEXTURE/GAME_RETURN.png")		//�Q�[���ɖ߂�{�^���̃e�N�X�`��
#define GAMETITLE_TEXTURE ("data/TEXTURE/GAMETITLE.png")				//�^�C�g���e�N�X�`��
#define TUTORIAL_TEXTURE ("data/TEXTURE/TUTORIAL.png")					//�`���[�g���A���̃e�N�X�`��
#define HISCOREUI_TEXTURE ("data/TEXTURE/HISCORE.png")					//�n�C�X�R�A�̃e�N�X�`��
#define MYSCOREUI_TEXTURE ("data/TEXTURE/YOURSCORE.png")				//�n�C�X�R�A�̃e�N�X�`��
#define SPEEDUP_TEXTURE ("data/TEXTURE/SPEEDUP!.png")					//�X�s�[�h�A�b�v�̃e�N�X�`��
#define NUMBER_TEXTURE ("data/TEXTURE/number_HGM.png")					//�i���o�[�̃e�N�X�`��
#define COMBOBONUS_TEXTURE ("data/TEXTURE/COMBO_BONUS.png")					//�R���{�{�[�i�X�̃e�N�X�`��

#define VECTOR3_DEFAULT		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))//�f�t�H���g�x�N�^�[
#define ZeroVector2			(D3DXVECTOR2(0.0f, 0.0f))
#define ZeroVector3			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WhiteColor			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define BlackColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))

//�{�^���}�N��
#define BUTTON_POSX (940.0f)//�{�^����X�̒���
#define BUTTON_POSY (800.0f)//�{�^����Y�̒���

//�G�l�~�[�}�N��
#define ENEMY_POSX (150.0f)//�G��X�̒���
#define ENEMY_POSY (150.0f)//�G��Y�̒���
#define ENEMY_SIZEX (250.0f)//�G��X�̒���
#define ENEMY_SIZEY (150.0f)//�G��Y�̒���


//�X�R�A�i���o�[�}�N��
#define MAX_SCORE_NUMBER (10)		//�X�R�A�i���o�[�̍ő吔
#define SCORE_POS_X (35)			//�X�R�A�ꌅ��X�̈ʒu
#define SCORE_POS_Y (70)			//�X�R�A�ꌅ��Y�̈ʒu
#define SCORE_SIZE_X (35)			//�X�R�A�ꌅ��X�̑傫��
#define SCORE_SIZE_Y (70)			//�X�R�A�ꌅ��Y�̑傫��

//�R���{�i���o�[�}�N��
#define MAX_COMBO_NUMBER (2)		//�X�R�A�i���o�[�̍ő吔
#define COMBO_POS_X (35)			//�X�R�A�ꌅ��X�̈ʒu
#define COMBO_POS_Y (140)			//�X�R�A�ꌅ��Y�̈ʒu
#define COMBO_SIZE_X (35)			//�X�R�A�ꌅ��X�̑傫��
#define COMBO_SIZE_Y (70)			//�X�R�A�ꌅ��Y�̑傫��

//�X�s�[�h�A�b�vUI�̃}�N��
#define SPEEDUP_POS_X (SCREEN_WIDTH / 2)			//�X�R�A�ꌅ��X�̈ʒu
#define SPEEDUP_POS_Y (SCREEN_HEIGHT / 2.5)			//�X�R�A�ꌅ��Y�̈ʒu
#define SPEEDUP_SIZE_X (SCREEN_WIDTH / 2.5)			//�X�R�A�ꌅ��X�̑傫��
#define SPEEDUP_SIZE_Y (1000.0f)					//�X�R�A�ꌅ��Y�̑傫��

//�X�R�AUI�̃}�N��
#define SCOREUI_TEXTURE ("data/TEXTURE/SCORE.png")	//�X�R�A�̃e�N�X�`��
#define SCOREUI_POSX (100.0f)						//�X�R�AUI��X�̒���
#define SCOREUI_POSY (70.0f)						//�X�R�AUI��Y�̒���
#define SCOREUI_SIZEX (200.0f)						//�X�R�AUI��X�̒���
#define SCOREUI_SIZEY (70.0f)						//�X�R�AUI��Y�̒���

//�R���{UI�̃}�N��
#define COMBOUI_TEXTURE ("data/TEXTURE/COMBO.png")	//�X�R�A�̃e�N�X�`��
#define COMBOUI_POSX (100.0f)						//�X�R�AUI��X�̒���
#define COMBOUI_POSY (140.0f)						//�X�R�AUI��Y�̒���
#define COMBOUI_SIZEX (200.0f)						//�X�R�AUI��X�̒���
#define COMBOUI_SIZEY (70.0f)						//�X�R�AUI��Y�̒���

//�E�B���h�E�p
#define WindowVersion (0)

//�t���X�N���[���p
#define FullScreenVersion (1)

using namespace std;         //  ���O��Ԏw��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W1
	float rhw;				//���W�ϊ��p�W��(1.0�ŌŒ�j
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`��
}VERTEX_2D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);
#endif