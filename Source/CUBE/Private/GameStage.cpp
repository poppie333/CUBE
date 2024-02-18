/*
* GameStage.cpp
* ステージを制御するクラス
* Create by 日向野　大聖 on 2023/01/05
* 更新日時・内容：ステージの回転処理 by 日向野　大聖 on 2023/01/05
*/

#include "GameStage.h"

// Sets default values
AGameStage::AGameStage()
	:StartRotation(false)
	, CntNum(0)
	, stagestatus(Side)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameStage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateStage();
}

void AGameStage::StartRot(bool _rotOn)
{
	StartRotation = _rotOn;
}

void AGameStage::RotateStage()
{
	FRotator rotation = GetActorRotation();
	// ステージの回転処理
	if (StartRotation) {
		if (stagestatus == Side) {
			if (CntNum < 95)
			{
				rotation.Yaw += 5.0f;
				CntNum += 5;
			}
			else {
				stagestatus = Front;
				CntNum = 0;
				StartRotation = false;
			}
		}
		if (stagestatus == Front) {
			if (CntNum < 95)
			{
				rotation.Yaw -= 5.0f;
				CntNum += 5;
			}
			else {
				stagestatus = Side;
				CntNum = 0;
				StartRotation = false;
			}
		}
		SetActorRotation(rotation);
	}
}