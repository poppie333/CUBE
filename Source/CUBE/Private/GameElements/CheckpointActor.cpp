//-------------------------------------------------------
// �t�@�C�����FCheckpointActor.cpp
// �T�v�@�@�@�F�`�F�b�N�|�C���g�̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/22 ���� �쐬
//-------------------------------------------------------

#include "GameElements/CheckpointActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CUBE/PlayerCharacter.h"
#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent��ǉ����ARootComponent�ɐݒ肷��
	Checkpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentCheckpoint"));
	RootComponent = Checkpoint;

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* CheckpointMesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_Checkpoint"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	Checkpoint->SetStaticMesh(CheckpointMesh);

	// StaticMeshComponent��ǉ����ARootComponent��Attach����
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentButton"));
	Button->SetupAttachment(RootComponent);

	// StaticMesh��Laod����StaticMeshComponent��StaticMesh�ɐݒ肷��
	UStaticMesh* ButtonMesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_CheckpointButton"));

	// StaticMesh��StaticMeshComponent�ɐݒ肷��
	Button->SetStaticMesh(ButtonMesh);

	// SphereCollision��ǉ�����
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radius��ݒ肷��
	Sphere->SetSphereRadius(70.0f);

	// SceneComponent���쐬����
	CheckTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CheckTransform->SetupAttachment(RootComponent);

	// �����𒲐�����
	CheckTransform->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	// OnComponentBeginOverlap��Bind����
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnSphereBeginOverlap);
}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ڐG����Actor��BallPlayer�����肷��
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// GameMode���擾���āAInGameGameMode��Cast����
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			//�@CheckTransform��WorldTransform���擾����
			const FTransform& WorldTransform = CheckTransform->GetComponentToWorld();

			// Transform��񂪈�v���Ȃ�������Spawn����Transform�����X�V����
			if (!GameMode->SpawnTransform.Equals(WorldTransform))
			{
				// Respawn����Transform�����X�V����
				GameMode->SpawnTransform = WorldTransform;

				UE_LOG(LogTemp, Log, TEXT("CheckPoint_Update"));
			}
		}
	}
}

