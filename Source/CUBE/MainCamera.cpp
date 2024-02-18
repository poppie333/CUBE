// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Camera/CameraComponent.h"				// �J��������
#include "GameFramework/SpringArmComponent.h"   // �X�v�����O�A�[��
#include "kismet/GamePlayStatics.h"

// Sets default values
AMainCamera::AMainCamera()
	: Stage(NULL)
	, Player(NULL)
	, FollowPlayer(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �J�����̏����ݒ�
	InitializeCamera();
}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	// �X�e�[�W�̎擾
	GetStage();
	// �v���C���[�̎擾
	GetPlayer();

	// �J�����̏�����
	Initialize();
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �J�����̍X�V����
	UpdateCamera();
}

// ������
void AMainCamera::Initialize()
{
	FVector stageloc = Stage->GetActorLocation();
	FVector playerloc = Player->GetActorLocation();
	SetActorLocation(FVector(stageloc.X, stageloc.Y, playerloc.Z));
}

// �J�����̏����ݒ�
void AMainCamera::InitializeCamera()
{
	// �X�v�����O�A�[���I�u�W�F�N�g�̐���
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	pSpringArm->SetupAttachment(RootComponent);

	// �J�����̃I�u�W�F�N�g�𐶐�
	mp_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("pCamera"));
	mp_Camera->SetupAttachment(pSpringArm, USpringArmComponent::SocketName);

	// �J�����̃Z�b�g
	mp_CameraMng = NewObject<UCameraManager>();
	mp_CameraMng->SetCamera(mp_Camera, pSpringArm);

	// �J���������݂���Ȃ�
	if (mp_CameraMng->GetCamera() != NULL)
	{
		// �J�����̑��Ή�]��ݒ�
		mp_CameraMng->SetCameraRot(0.f, -90.f, 0.f);
		// �X�v�����O�A�[��
		mp_CameraMng->SetTargetArmLength(2000.f);
		// �J�����̃R���W����
		mp_CameraMng->SetDoCollisionTest(false);
		// �J�����̒Ǐ]���O
		mp_CameraMng->SetEnableCameraLag(false);
	}

}

// �X�e�[�W�A�N�^�[�̎擾
void AMainCamera::GetStage()
{
	if (Stage == NULL)
	{
		TSubclassOf<AActor> findClass;
		findClass = AActor::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), findClass, actors);

		if (actors.Num() > 0)
		{
			for (int idx = 0; idx < actors.Num(); idx++)
			{
				AActor* pActor = Cast<AActor>(actors[idx]);

				if (pActor->ActorHasTag("Stage"))
				{
					Stage = pActor;
					break;
				}
			}
		}
	}
}

// �v���C���[�A�N�^�[�̎擾
void AMainCamera::GetPlayer()
{
	if (Player == NULL)
	{
		TSubclassOf<AActor> findClass;
		findClass = AActor::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), findClass, actors);

		if (actors.Num() > 0)
		{
			for (int idx = 0; idx < actors.Num(); idx++)
			{
				AActor* pActor = Cast<AActor>(actors[idx]);

				if (pActor->ActorHasTag("Player"))
				{
					Player = pActor;
					break;
				}
			}
		}
	}
}

// ���t���[���̍X�V����
void AMainCamera::UpdateCamera()
{
	// �������v���C���[�ɍ��킹��
	if (Player != NULL)
	{
		float z = Player->GetActorLocation().Z;
		FVector newlocation = GetActorLocation();

		if (FollowPlayer == true)
		{
			newlocation.Z = z + 60.f;
			FollowPlayer = false;
		}
		else if (z + 135.f < newlocation.Z)
		{
			newlocation.Z = z + 135.f;
		}

		SetActorLocation(newlocation);
	}
}

///* public *///
// �J��������]������
void AMainCamera::RotationCamera(bool _right, bool _left)
{
	FRotator rotation = GetActorRotation();

	if (_right == true)
	{
		rotation.Yaw -= 5.f;
	}
	if (_left == true)
	{
		rotation.Yaw += 5.f;
	}

	SetActorRotation(rotation);
}

// �J�����̋����ύX
void AMainCamera::ChangeDistance(float _offset)
{
	if (pSpringArm != NULL)
	{
		// �X�v�����O�A�[���̒���
		pSpringArm->TargetArmLength -= _offset * 10;
		// 1�͈͂̐ݒ�
		if (pSpringArm->TargetArmLength < MinArm) { pSpringArm->TargetArmLength = MinArm; }
		if (pSpringArm->TargetArmLength > MaxArm) { pSpringArm->TargetArmLength = MaxArm; }
	}
}

// �v���C���[�Ǐ]�J�n
void AMainCamera::OnFollowPlayer(bool _follow)
{
	FollowPlayer = _follow;
}