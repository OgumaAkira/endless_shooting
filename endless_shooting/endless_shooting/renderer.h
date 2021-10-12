//*****************************************************************************
//
// �����_���[���� [renderer.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�����_�����O�̃N���X�錾
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();												//�R���X�g���N�^
	~CRenderer();												//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	//�������֐�
	void Uninit(void);											//�I���֐�
	void Update(void);											//�X�V�֐�
	void Draw(void);											//�`��֐�
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//�f�o�C�X�̎擾

private:
	//�����o�֐�
	void DrawFPS(void);

	//�����o�ϐ�
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
};
#endif // !_RENDERER_H_

