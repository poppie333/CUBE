//-------------------------------------------------------
// ファイル名：GimmickBase.cpp
// 概要　　　：ギミックのベースクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/08  
//          ：12/15 更新
//　　　　　 ：12/22 更新
//          ：1/12  更新
//          ：1/19  更新
//　　　　 　：1/22 更新
//　　　　 　：2/08 更新
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

	// StaticMeshComponentを追加し、RootComponentに設定する
	GimmickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = GimmickMesh;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh"));

	// StaticMeshをStaticMeshComponentに設定する
	GimmickMesh->SetStaticMesh(Mesh);

	// BoxComponentを追加し、BoxComponentをRootComponentにAttachする
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Boxの位置を調整する
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, 45.0f), false);

	// OnComponentBeginOverlapをBindする
	Box->OnComponentBeginOverlap.AddDynamic(this, &AGimmickBase::OnBoxBeginOverlap);

	// OnComponentEndOverlapをBindする
	Box->OnComponentEndOverlap.AddDynamic(this, &AGimmickBase::OnOverlapEnd);

	// Hit Eventを有効にする
	GimmickMesh->BodyInstance.bNotifyRigidBodyCollision = true;


	//初期化
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

	//梯子ギミックの処理
	if (PA != false && GimmickCnt >= GimmickCntActivation)
	{
			FVector location = AO->GetActorLocation();
			location.Z += velocity;
			AO->SetActorLocation(location);

			GimmickCnt = 0.0f;
			PA = false;
	}
}

//ギミック稼働中のカウント処理
void AGimmickBase::GimmickActivation()
{
	GimmickCnt++;
}

void AGimmickBase::GimmickON()
{
	// 処理は子クラスで継承して実装する
}

void AGimmickBase::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	
	// プレイヤーが触れてるとき
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(Other))
	{
		//プレイヤーをキルするフラグが起動中のとき
		if (PlayerKill != false)
		{
			// GameModeを取得して、InGameGameModeにCastする
			if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				// KillPlayerを呼び出してPlayerを破棄する
				GameMode->KillPlayer(Player);
			}
		}
	}
}

void AGimmickBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//プレイヤーが触れているとき
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		this->GimmickON();

		//このギミックを破壊する
		if (UNDestroy != false)
		{
			// ギミックを破棄する
			this->Destroy();
		}

		//このギミックを起動する
		if (BootGimmick != false)
		{
			BootGimmickReaction = true;
		}

		//梯子ギミックを起動する
		if (LadderCol != false)
		{
			AO = OtherActor;
			PA = true;
		}
	}
}

void AGimmickBase::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//このギミックを停止
	BootGimmick = false;
	BootGimmickReaction = false;
}