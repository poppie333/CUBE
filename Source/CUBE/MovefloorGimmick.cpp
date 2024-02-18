//-------------------------------------------------------
// �t�@�C�����FMovefloorGimmick.cpp
// �T�v�@�@�@�FGimmickBase���p�������A�ړ����M�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/25 �쐬
//�@�@�@�@ �@�F1/29 �X�V
//�@�@�@�@ �@�F2/08 �X�V
//�@�@�@�@ �@�F2/09 �X�V
//-------------------------------------------------------

#include "MovefloorGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

//�R���X�g���N�^
AMovefloorGimmick::AMovefloorGimmick()
{
	//Tick���N��
	PrimaryActorTick.bCanEverTick = true;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("MovefloorGimmick"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	GimmickMesh->SetStaticMesh(Mesh);

	FloorDown = false;
	OnProgram = true;
}

//���t���[���̍X�V����
void AMovefloorGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	//�M�~�b�N����ɉғ��������邩
	if (AutGimmick != false)
	{
		BootGimmickReaction = true;
	}

	//��x�����s������
	if (OnProgram != false)
	{
		// �������x�Ə����ʒu�̐ݒ������
		if (velocity == NULL)
		{
			velocity = 1.0f * AdjustVelocity;
		}
		if (GimmickCntActivation == NULL)
		{
			GimmickCntActivation = 100.0f * AdjustCount;
		}

		//�ړ����x�̏����l��ۑ�
		Save_velocity = velocity;
		OnProgram = false;
	}

	//���ړ��̏���
	if (BootGimmickReaction != false)
	{
		//X���̈ړ��ł��鎞
		if (Xaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.X += velocity;
			this->SetActorLocation(location);
		}
		//Y���̈ړ��ł��鎞
		if (Yaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.Y += velocity;
			this->SetActorLocation(location);
		}
		//Z���̈ړ��ł��鎞
		if (Zaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.Z += velocity;
			this->SetActorLocation(location);
		}

		//�M�~�b�N�ғ����̃J�E���g�֐�
		AMovefloorGimmick::GimmickActivation();

		// GimmickCntActivation�Ŏw�肵���J�E���g���o�߂�����j��
		if (GimmickCnt >= GimmickCntActivation)
		{
			//�㏸�������~�����𔻕ʂ���t���O��؂�ւ���
			if (FloorDown == false)
			{
				FloorDown = true;
			}
			else if (FloorDown != false)
			{
				FloorDown = false;
			}

			//�ꎞ��~����
			velocity = 0.0f;

			//�ĉғ�����
			if (GimmickCnt >= GimmickCntActivation * 1.5)
			{
				if (FloorDown == false)
				{
					velocity = -Save_velocity;
				}
				else if (FloorDown != false)
				{
					velocity = Save_velocity;
				}

				GimmickCnt = 0;
				velocity = -velocity;
			}
		}
	}
}

//�M�~�b�N�ғ����̃J�E���g����
void AMovefloorGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//�v���C���[�ɐG�ꂽ��s������
void AMovefloorGimmick::GimmickON()
{
	//�M�~�b�N���N��
	BootGimmick = true;

	//�X�C�b�`�����������͎����œ���������
	if (AutGimmickBoot != false)
	{
		AutGimmick = true;
	}
}
