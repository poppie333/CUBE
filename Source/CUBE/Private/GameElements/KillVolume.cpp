//-------------------------------------------------------
// ファイル名：KillVolume.cpp
// 概要　　　：プレイヤーをキルする空間のクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/15 松丸 作成
//          ：1/19 松丸 更新
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

	// SceneComponentを作成する
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// SceneComponentをRootComponentに設定する
	RootComponent = DefaultSceneRoot;

	KillVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	// BoxComponentをRootComponentにAttachする
	KillVolume->SetupAttachment(RootComponent);

	// BoxComponentのOnComponentBegineOverlapに関数「OnBoxBeginOverlap」を関連づける
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
	// KillVolumeのBox Extentを変更する
	KillVolume->SetBoxExtent(BoxExtent);
}

void AKillVolume::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 接触したActorがPlayerか判定する
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// GameModeを取得して、CUBEGameModeBaseにCastする
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			// KillPlayerを呼び出してPlayerを破棄する
			GameMode->KillPlayer(Player);
		}
	}
}