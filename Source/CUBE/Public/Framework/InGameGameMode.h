//-------------------------------------------------------
// ファイル名：InGameGameMode.h
// 概要　　　：インゲームのゲームモード
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/19 松丸 作成
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
	//コンストラクタ
	AInGameGameMode();

	/** Playerを破棄する **/
	void KillPlayer(APlayerCharacter* Player);

	// PlayerをRespawnする位置情報
	FTransform SpawnTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** PlayerをRespawnする **/
	void RespawnPlayer();

};
