/*
* GameStage.h
* ステージを制御するクラス
* Create by 日向野　大聖 on 2023/01/05
* 更新日時・内容：ステージの回転処理 by 日向野　大聖 on 2023/01/05
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStage.generated.h"

UCLASS()
class CUBE_API AGameStage : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartRot(bool _rotOn);

private:
	void RotateStage();

private:
	bool StartRotation;
	int CntNum;

	enum StageStatus
	{
		Side,
		Front
	};
	StageStatus stagestatus;

};
