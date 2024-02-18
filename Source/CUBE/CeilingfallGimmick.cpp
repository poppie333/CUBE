//-------------------------------------------------------
// �t�@�C�����FCeilingfallGimmick.cpp
// �T�v�@�@�@�FGimmickBase���p�������A�V�䗎���M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/15
//           �F12/18 �X�V
//           �F12/20 �X�V
//�@�@�@�@ �@ �F12/22 �X�V
//�@�@�@�@ �@ �F1/12 �X�V
//�@�@�@�@  �@�F1/22 �X�V
//-------------------------------------------------------


#include "CeilingfallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

//�R���X�g���N�^
ACeilingfallGimmick::ACeilingfallGimmick()
{
	//Tick���N��
	PrimaryActorTick.bCanEverTick = true;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("CeilingfallGimmick"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	GimmickMesh->SetStaticMesh(Mesh);
	
	// Box�̃T�C�Y��ݒ肷��
	Box->SetBoxExtent(FVector(80.0f, 80.0f, 50.0f));

	// Box�����蔻��̈ʒu�𒲐�����
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, -250.0f), false);

	//�ϐ��̏�����
	FallON = false;
	OnProgram = true;
	GimmickCnt = 0;

	// �������x�Ə����ʒu�̐ݒ������       
	startLocation = this->GetActorLocation();

	//�v���C���[���L������
	PlayerKill = true;
}

//���t���[���̍X�V����
void ACeilingfallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FallON != false)
	{
		FVector location = this->GetActorLocation();
		location.Z -= velocity;
		this->SetActorLocation(location);

		ACeilingfallGimmick::GimmickActivation();

		// GimmickCntActivation�Ŏw�肵���J�E���g���o�߂�����j��
		if (GimmickCnt >= GimmickCntActivation)
		{
			//�ړ����~
			velocity = 0.0f;

			//�M�~�b�N����~�����Ƃ�
			if (velocity == 0.0f)
			{
				//�v���C���[���L�����Ȃ�
				PlayerKill = false;
			}
		}
	}
}

//�M�~�b�N�ғ����̃J�E���g����
void ACeilingfallGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//�v���C���[�ɐG�ꂽ�珈�����J�n����t���O���N��
void ACeilingfallGimmick::GimmickON()
{
	//UE_LOG(LogTemp, Error, TEXT("COLLTION"));

	//�����l�����肷��
	if (OnProgram != false)
	{
		// �������x�Ə����ʒu�̐ݒ������
		if (velocity == NULL)
		{
			velocity = 1.0f * AdjustVelocity;
		}
		if (GimmickCntActivation == NULL)
		{
			GimmickCntActivation = 10.0f * AdjustCount;
		}

		OnProgram = false;

		//UE_LOG(LogTemp, Error, TEXT("INITIALIZATION"));
	}

	//�����t���O�������ɂȂ��Ă���Ƃ�
	if (FallON == false)
	{
		//�����������J�n����
		FallON = true;
	}
}



	