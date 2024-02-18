//-------------------------------------------------------
// �t�@�C�����FInGameGameMode.h
// �T�v�@�@�@�F�C���Q�[���̃Q�[�����[�h
// �쐬�ҁ@�@�F22cu0136 ���ۍW��
// �X�V�@�@�@�F1/19 ���� �쐬
//-------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CUBE/PlayerCharacter.h"
#include "InGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API AInGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//�R���X�g���N�^
	AInGameGameMode();

	/** Player��j������ **/
	void KillPlayer(APlayerCharacter* Player);

	// Player��Respawn����ʒu���
	FTransform SpawnTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Player��Respawn���� **/
	void RespawnPlayer();

};
