// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/CameraManager.h" // �J�����}�l�[�W���[
#include "MainCamera.generated.h"

UCLASS()
class CUBE_API AMainCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// ����������
	void InitializeCamera();

	void Initialize();

	// �X�e�[�W�̎擾
	void GetStage();

	// �v���C���[�̎擾
	void GetPlayer();

	// ���t���[���̃J�����̍X�V
	void UpdateCamera();

public:
	// �J������]�̏���
	void RotationCamera(bool _right, bool _left);

	// �J�����̋����ύX
	void ChangeDistance(float _offset);

	// �v���C���[�̍����ɍ��킹�邩
	void OnFollowPlayer(bool _follow);

	// �����o�ϐ�
private:
	// �A�N�^�[
	AActor* Stage;
	AActor* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraManager* mp_CameraMng = nullptr;   // �J�����}�l�[�W���[

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* mp_Camera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* pSpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float MaxArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float MinArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float ChangeLocationNum;

	bool FollowPlayer;
};
