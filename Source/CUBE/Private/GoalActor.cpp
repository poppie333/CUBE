//-------------------------------------------------------
// ファイル名：GoalActor.cpp
// 概要　　　：ゴールアクターのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/15 作成
// 
//-------------------------------------------------------

#include "GoalActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CUBE/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponentを追加し、RootComponentに設定する
	Goal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Goal;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("S_Goal"));

	// StaticMeshをStaticMeshComponentに設定する
	Goal->SetStaticMesh(Mesh);

	// SphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radiusを設定する
	Sphere->SetSphereRadius(72.0f);

	// OnComponentBeginOverlapをBindする
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//スフィアコリジョン
void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 接触したActorがプレイヤーに触れているとき
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		//デバッグログ
		UE_LOG(LogTemp, Display, TEXT("Goal"));

		// 遷移するLevelをLoadする
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadLevel);
	}
}