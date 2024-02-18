//-------------------------------------------------------
// �t�@�C�����FKillVolume.cpp
// �T�v�@�@�@�F�v���C���[���L�������Ԃ̃N���X
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/15 ���� �쐬
//          �F1/19 ���� �X�V
//-------------------------------------------------------


#include "GameElements/KillVolume.h"
#include "Components/BoxComponent.h"
#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKillVolume::AKillVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SceneComponent���쐬����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// SceneComponent��RootComponent�ɐݒ肷��
	RootComponent = DefaultSceneRoot;

	KillVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	// BoxComponent��RootComponent��Attach����
	KillVolume->SetupAttachment(RootComponent);

	// BoxComponent��OnComponentBegineOverlap�Ɋ֐��uOnBoxBeginOverlap�v���֘A�Â���
	KillVolume->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void AKillVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillVolume::OnConstruction(const FTransform& Transform)
{
	// KillVolume��Box Extent��ύX����
	KillVolume->SetBoxExtent(BoxExtent);
}

void AKillVolume::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ڐG����Actor��Player�����肷��
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// GameMode���擾���āACUBEGameModeBase��Cast����
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			// KillPlayer���Ăяo����Player��j������
			GameMode->KillPlayer(Player);
		}
	}
}