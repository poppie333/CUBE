//-------------------------------------------------------
// �t�@�C�����FInGameGameMode.cpp
// �T�v�@�@�@�F�C���Q�[���̃Q�[�����[�h
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/19 ���� �쐬
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
	// Player��j������
	Player->Destroy();

	// Respawn���s��
	RespawnPlayer();
}

void AInGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Viewport�ɔz�u���ꂽPlayerStart��T��
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	// PlayerStart�̈ʒu����Resporn�̈ʒu�Ƃ��ĕێ�����
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AInGameGameMode::RespawnPlayer()
{
	// BallPlayer��Spawn����
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerCharacter* Player = GetWorld()->SpawnActor<APlayerCharacter>(APlayerCharacter::StaticClass(), SpawnTransform, SpawnInfo);

	// Controller��ݒ肷��
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);
}
