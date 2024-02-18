/*
* CameraManager.cpp
*
* Create by 日向野　大聖 on 2023/12/07
*/

#include "CameraManager.h"
#include "GameFramework/SpringArmComponent.h"		// スプリングアーム制御

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

// カメラの座標を設定
void UCameraManager::SetTargetArmLength(float _length)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->TargetArmLength = _length;
	}
}

// カメラの座標を取得
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

// カメラの角度を設定
void UCameraManager::SetCameraRot(float _pitch, float _yaw, float _roll)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->SetRelativeRotation(FRotator(_pitch, _yaw, _roll));
	}
}

// カメラのコリジョンテスト
void UCameraManager::SetDoCollisionTest(bool _bEnable)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->bDoCollisionTest = _bEnable;
	}
}

// カメラ追従ラグ
void UCameraManager::SetEnableCameraLag(bool _bEnable)
{
	if (m_pSpringArm != NULL)
	{
		m_pSpringArm->bEnableCameraLag = _bEnable;
	}
}
