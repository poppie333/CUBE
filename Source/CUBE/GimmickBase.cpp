//-------------------------------------------------------
// �t�@�C�����FGimmickBase.cpp
// �T�v�@�@�@�F�M�~�b�N�̃x�[�X�N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F12/08  
//          �F12/15 �X�V
//�@�@�@�@�@ �F12/22 �X�V
//          �F1/12  �X�V
//          �F1/19  �X�V
//�@�@�@�@ �@�F1/22 �X�V
//�@�@�@�@ �@�F2/08 �X�V
//-------------------------------------------------------

#include "CUBE/GimmickBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "kismet/GamePlayStatics.h"
#include "CUBE/PlayerCharacter.h"
#include "Framework/InGameGameMode.h"

// Sets default values
AGimmickBase::AGimmickBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	GimmickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = GimmickMesh;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	GimmickMesh->SetStaticMesh(Mesh);

	// BoxComponent��ǉ����ABoxComponent��RootComponent��Attach����
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	// Box�̃T�C�Y��ݒ肷��
	Box->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Box�̈ʒu�𒲐�����
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, 45.0f), false);

	// OnComponentBeginOverlap��Bind����
	Box->OnComponentBeginOverlap.AddDynamic(this, &AGimmickBase::OnBoxBeginOverlap);

	// OnComponentEndOverlap��Bind����
	Box->OnComponentEndOverlap.AddDynamic(this, &AGimmickBase::OnOverlapEnd);

	// Hit Event��L���ɂ���
	GimmickMesh->BodyInstance.bNotifyRigidBodyCollision = true;


	//������
	GimmickCnt = 0.0f;
}

// Called when the game starts or when spawned
void AGimmickBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGimmickBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AGimmickBase::GimmickActivation();

	//��q�M�~�b�N�̏���
	if (PA != false && GimmickCnt >= GimmickCntActivation)
	{
			FVector location = AO->GetActorLocation();
			location.Z += velocity;
			AO->SetActorLocation(location);

			GimmickCnt = 0.0f;
			PA = false;
	}
}

//�M�~�b�N�ғ����̃J�E���g����
void AGimmickBase::GimmickActivation()
{
	GimmickCnt++;
}

void AGimmickBase::GimmickON()
{
	// �����͎q�N���X�Ōp�����Ď�������
}

void AGimmickBase::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	
	// �v���C���[���G��Ă�Ƃ�
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(Other))
	{
		//�v���C���[���L������t���O���N�����̂Ƃ�
		if (PlayerKill != false)
		{
			// GameMode���擾���āAInGameGameMode��Cast����
			if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				// KillPlayer���Ăяo����Player��j������
				GameMode->KillPlayer(Player);
			}
		}
	}
}

void AGimmickBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�v���C���[���G��Ă���Ƃ�
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		this->GimmickON();

		//���̃M�~�b�N��j�󂷂�
		if (UNDestroy != false)
		{
			// �M�~�b�N��j������
			this->Destroy();
		}

		//���̃M�~�b�N���N������
		if (BootGimmick != false)
		{
			BootGimmickReaction = true;
		}

		//��q�M�~�b�N���N������
		if (LadderCol != false)
		{
			AO = OtherActor;
			PA = true;
		}
	}
}

void AGimmickBase::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//���̃M�~�b�N���~
	BootGimmick = false;
	BootGimmickReaction = false;
}