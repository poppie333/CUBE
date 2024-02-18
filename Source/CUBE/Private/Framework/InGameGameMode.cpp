//-------------------------------------------------------
// ファイル名：InGameGameMode.cpp
// 概要　　　：インゲームのゲームモード
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/19 松丸 作成
//-------------------------------------------------------


#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AInGameGameMode::AInGameGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void AInGameGameMode::KillPlayer(APlayerCharacter* Player)
{
	// Playerを破棄する
	Player->Destroy();

	// Respawnを行う
	RespawnPlayer();
}

void AInGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Viewportに配置されたPlayerStartを探す
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	// PlayerStartの位置情報をRespornの位置として保持する
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AInGameGameMode::RespawnPlayer()
{
	// BallPlayerをSpawnする
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerCharacter* Player = GetWorld()->SpawnActor<APlayerCharacter>(APlayerCharacter::StaticClass(), SpawnTransform, SpawnInfo);

	// Controllerを設定する
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);
}
