/*
* CameraManager.h
*
* Create by ������@�吹 on 2023/12/07
*/

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CameraManager.generated.h"


// �N���X�̑O���錾
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UCameraManager : public UObject
{
	GENERATED_BODY()

public:
	// constructor
	UCameraManager();
	// destructor
	~UCameraManager();

	// �J�����I�u�W�F�N�g�̎擾
	UCameraComponent* GetCamera()const { return m_pCamera; }

	// �X�v�����O�A�[���̎擾
	USpringArmComponent* GetSpringArm() const { return m_pSpringArm; }

	// �J�����I�u�W�F�N�g�̐ݒ�
	void SetCamera(UCameraComponent* _pCamera, USpringArmComponent* _pSpringArm);

	// �X�v�����O�A�[���̒�����ݒ�
	void SetTargetArmLength(float _length);

	// �X�v�����O�A�[���̒������擾
	float GetTargetArmLength();

	// �J�����̊p�x��ݒ�
	void SetCameraRot(float _pitch, float _yaw, float _roll);

	// �J�����̃R���W�����e�X�g
	void SetDoCollisionTest(bool _bEnable);

	// �J�����Ǐ]���O
	void SetEnableCameraLag(bool _bEnable);

protected:

	// �����o�ϐ�
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* m_pCamera;		 // �J����

private:
	USpringArmComponent* m_pSpringArm;   // �X�v�����O�A�[��
};
