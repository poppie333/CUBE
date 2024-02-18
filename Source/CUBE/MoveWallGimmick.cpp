//-------------------------------------------------------
// �t�@�C�����FMoveWallGimmick.cpp
// �T�v�@�@�@�FGimmickBase���p�������A�ړ��ǃM�~�b�N�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/08�@�쐬
//�@�@�@�@ �@�F2/13 �X�V
//-------------------------------------------------------


#include "MoveWallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

//�R���X�g���N�^
AMoveWallGimmick::AMoveWallGimmick()
{
	//Tick���N��
	PrimaryActorTick.bCanEverTick = true;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("AMoveWallGimmick"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	GimmickMesh->SetStaticMesh(Mesh);

	// Box�̃T�C�Y��ݒ肷��
	Box->SetBoxExtent(FVector(120.0f, 120.0f, 50.0f));

	// Box�����蔻��̈ʒu�𒲐�����
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, -250.0f), false);

	//�ϐ��̏�����
	MoveON = false;
	OnProgram = true;
	GimmickCnt = 0;

	// �������x�Ə����ʒu�̐ݒ������
	startLocation = this->GetActorLocation();
}

//���t���[���̍X�V����
void AMoveWallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�M�~�b�N���N������
	if (MoveON != false)
	{
		//�ړ����鏈���ł���ꍇ
		if (Move != false)
		{
			//X���̈ړ��ł��鎞
			if (Xaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̈ړ��ł��鎞
				if (XPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.X += velocity;
					this->SetActorLocation(location);
				}
				//PlusMove��true = �}�C�i�X�����ւ̈ړ��ł��鎞
				if (XPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.X -= velocity;
					this->SetActorLocation(location);
				}
			}
			//Y���̈ړ��ł��鎞
			if (Yaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̈ړ��ł��鎞
				if (YPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.Y += velocity;
					this->SetActorLocation(location);
				}
				//PlusMove��true = �}�C�i�X�����ւ̈ړ��ł��鎞
				if (YPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.Y -= velocity;
					this->SetActorLocation(location);
				}
			}
			//Z���̈ړ��ł��鎞
			if (Zaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̈ړ��ł��鎞
				if (ZPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.Z += velocity;
					this->SetActorLocation(location);
				}
				//PlusMove��true = �}�C�i�X�����ւ̈ړ��ł��鎞
				if (ZPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.Z -= velocity;
					this->SetActorLocation(location);
				}
			}
		}

		//�g�k���鏈���ł���ꍇ
		if (Scale != false)
		{
			//X���̊g�k�ł��鎞
			if (Xaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̊g�k�ł��鎞
				if (XPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.X += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMove��true = �}�C�i�X�����ւ̊g�k�ł��鎞
				if (XPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.X -= velocity;
					this->SetActorScale3D(scale);
				}
			}
			//Y���̊g�k�ł��鎞
			if (Yaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̊g�k�ł��鎞
				if (YPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Y += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMove��true = �}�C�i�X�����ւ̊g�k�ł��鎞
				if (YPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Y -= velocity;
					this->SetActorScale3D(scale);
				}
			}
			//Z���̊g�k�ł��鎞
			if (Zaxis != false)
			{
				//PlusMove��true = �v���X�����ւ̊g�k�ł��鎞
				if (ZPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Z += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMove��true = �}�C�i�X�����ւ̊g�k�ł��鎞
				if (ZPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Z -= velocity;
					this->SetActorScale3D(scale);
				}
			}
		}
		

		AMoveWallGimmick::GimmickActivation();

		// GimmickCntActivation�Ŏw�肵���J�E���g���o�߂�����j��
		if (GimmickCnt >= GimmickCntActivation)
		{
			velocity = 0.0f;
			GimmickCnt = 0;
		}
	}
}

//�M�~�b�N�ғ����̃J�E���g����
void AMoveWallGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//�v���C���[�ɐG�ꂽ�珈�����J�n����t���O���N��
void AMoveWallGimmick::GimmickON()
{
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
	}

	//���̃A�N�^�[���N�����鏈��
	if (MoveON == false)
	{
		//�ړ��������J�n����
		MoveON = true;
	}
}