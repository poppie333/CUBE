/*
* CameraManager.cpp
*
* Create by ������@�吹 on 2023/12/07
*/

#include "CameraManager.h"
#include "GameFramework/SpringArmComponent.h"		// �X�v�����O�A�[������

// Constructor
UCameraManager::UCameraManager()
	:m_pCamera(NULL)
	, m_pSpringArm(NULL)
{
}

// destructor
UCameraManager::~UCameraManager()
{
}

void UCameraManager::SetCamera(UCameraComponent* _pCamera, USpringArmComponent* _pSpringArm)
{
	m_pCamera = _pCamera;
	m_pSpringArm = _pSpringArm;
}

// �J�����̍��W��ݒ�
void UCameraManager::SetTargetArmLength(float _length)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->TargetArmLength = _length;
	}
}

// �J�����̍��W���擾
float UCameraManager::GetTargetArmLength()
{
	if (m_pSpringArm != NULL)
	{
		return m_pSpringArm->TargetArmLength;
	}
	else
	{
		return 0;
	}
}

// �J�����̊p�x��ݒ�
void UCameraManager::SetCameraRot(float _pitch, float _yaw, float _roll)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->SetRelativeRotation(FRotator(_pitch, _yaw, _roll));
	}
}

// �J�����̃R���W�����e�X�g
void UCameraManager::SetDoCollisionTest(bool _bEnable)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->bDoCollisionTest = _bEnable;
	}
}

// �J�����Ǐ]���O
void UCameraManager::SetEnableCameraLag(bool _bEnable)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->bEnableCameraLag = _bEnable;
	}
}
