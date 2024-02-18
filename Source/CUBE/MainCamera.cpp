// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Camera/CameraComponent.h"				// カメラ制御
#include "GameFramework/SpringArmComponent.h"   // スプリングアーム
#include "kismet/GamePlayStatics.h"

// Sets default values
AMainCamera::AMainCamera()
	: Stage(NULL)
	, Player(NULL)
	, FollowPlayer(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// カメラの初期設定
	InitializeCamera();
}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	// ステージの取得
	GetStage();
	// プレイヤーの取得
	GetPlayer();

	// カメラの初期化
	Initialize();
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// カメラの更新処理
	UpdateCamera();
}

// 初期化
void AMainCamera::Initialize()
{
	FVector stageloc = Stage->GetActorLocation();
	FVector playerloc = Player->GetActorLocation();
	SetActorLocation(FVector(stageloc.X, stageloc.Y, playerloc.Z));
}

// カメラの初期設定
void AMainCamera::InitializeCamera()
{
	// スプリングアームオブジェクトの生成
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	pSpringArm->SetupAttachment(RootComponent);

	// カメラのオブジェクトを生成
	mp_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("pCamera"));
	mp_Camera->SetupAttachment(pSpringArm, USpringArmComponent::SocketName);

	// カメラのセット
	mp_CameraMng = NewObject<UCameraManager>();
	mp_CameraMng->SetCamera(mp_Camera, pSpringArm);

	// カメラが存在するなら
	if (mp_CameraMng->GetCamera() != NULL)
	{
		// カメラの相対回転を設定
		mp_CameraMng->SetCameraRot(0.f, -90.f, 0.f);
		// スプリングアーム
		mp_CameraMng->SetTargetArmLength(2000.f);
		// カメラのコリジョン
		mp_CameraMng->SetDoCollisionTest(false);
		// カメラの追従ラグ
		mp_CameraMng->SetEnableCameraLag(false);
	}

}

// ステージアクターの取得
void AMainCamera::GetStage()
{
	if (Stage == NULL)
	{
		TSubclassOf<AActor> findClass;
		findClass = AActor::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), findClass, actors);

		if (actors.Num() > 0)
		{
			for (int idx = 0; idx < actors.Num(); idx++)
			{
				AActor* pActor = Cast<AActor>(actors[idx]);

				if (pActor->ActorHasTag("Stage"))
				{
					Stage = pActor;
					break;
				}
			}
		}
	}
}

// プレイヤーアクターの取得
void AMainCamera::GetPlayer()
{
	if (Player == NULL)
	{
		TSubclassOf<AActor> findClass;
		findClass = AActor::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), findClass, actors);

		if (actors.Num() > 0)
		{
			for (int idx = 0; idx < actors.Num(); idx++)
			{
				AActor* pActor = Cast<AActor>(actors[idx]);

				if (pActor->ActorHasTag("Player"))
				{
					Player = pActor;
					break;
				}
			}
		}
	}
}

// 毎フレームの更新処理
void AMainCamera::UpdateCamera()
{
	// 高さをプレイヤーに合わせる
	if (Player != NULL)
	{
		float z = Player->GetActorLocation().Z;
		FVector newlocation = GetActorLocation();

		if (FollowPlayer == true)
		{
			newlocation.Z = z + 60.f;
			FollowPlayer = false;
		}
		else if (z + 135.f < newlocation.Z)
		{
			newlocation.Z = z + 135.f;
		}

		SetActorLocation(newlocation);
	}
}

///* public *///
// カメラを回転させる
void AMainCamera::RotationCamera(bool _right, bool _left)
{
	FRotator rotation = GetActorRotation();

	if (_right == true)
	{
		rotation.Yaw -= 5.f;
	}
	if (_left == true)
	{
		rotation.Yaw += 5.f;
	}

	SetActorRotation(rotation);
}

// カメラの距離変更
void AMainCamera::ChangeDistance(float _offset)
{
	if (pSpringArm != NULL)
	{
		// スプリングアームの調節
		pSpringArm->TargetArmLength -= _offset * 10;
		// 1範囲の設定
		if (pSpringArm->TargetArmLength < MinArm) { pSpringArm->TargetArmLength = MinArm; }
		if (pSpringArm->TargetArmLength > MaxArm) { pSpringArm->TargetArmLength = MaxArm; }
	}
}

// プレイヤー追従開始
void AMainCamera::OnFollowPlayer(bool _follow)
{
	FollowPlayer = _follow;
}