//-------------------------------------------------------
// ファイル名：CheckpointActor.cpp
// 概要　　　：チェックポイントのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/22 松丸 作成
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

	// StaticMeshComponentを追加し、RootComponentに設定する
	Checkpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentCheckpoint"));
	RootComponent = Checkpoint;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* CheckpointMesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_Checkpoint"));

	// StaticMeshをStaticMeshComponentに設定する
	Checkpoint->SetStaticMesh(CheckpointMesh);

	// StaticMeshComponentを追加し、RootComponentにAttachする
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentButton"));
	Button->SetupAttachment(RootComponent);

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* ButtonMesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_CheckpointButton"));

	// StaticMeshをStaticMeshComponentに設定する
	Button->SetStaticMesh(ButtonMesh);

	// SphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radiusを設定する
	Sphere->SetSphereRadius(70.0f);

	// SceneComponentを作成する
	CheckTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CheckTransform->SetupAttachment(RootComponent);

	// 高さを調整する
	CheckTransform->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	// OnComponentBeginOverlapをBindする
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
	// 接触したActorがBallPlayerか判定する
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// GameModeを取得して、InGameGameModeにCastする
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			//　CheckTransformのWorldTransformを取得する
			const FTransform& WorldTransform = CheckTransform->GetComponentToWorld();

			// Transform情報が一致しなかったらSpawnするTransform情報を更新する
			if (!GameMode->SpawnTransform.Equals(WorldTransform))
			{
				// RespawnするTransform情報を更新する
				GameMode->SpawnTransform = WorldTransform;

				UE_LOG(LogTemp, Log, TEXT("CheckPoint_Update"));
			}
		}
	}
}

