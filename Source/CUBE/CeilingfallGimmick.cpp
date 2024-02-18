//-------------------------------------------------------
// ファイル名：CeilingfallGimmick.cpp
// 概要　　　：GimmickBaseを継承した、天井落下ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/15
//           ：12/18 更新
//           ：12/20 更新
//　　　　 　 ：12/22 更新
//　　　　 　 ：1/12 更新
//　　　　  　：1/22 更新
//-------------------------------------------------------


#include "CeilingfallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

//コンストラクタ
ACeilingfallGimmick::ACeilingfallGimmick()
{
	//Tickを起動
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("CeilingfallGimmick"));

	// StaticMeshをStaticMeshComponentに設定する
	GimmickMesh->SetStaticMesh(Mesh);
	
	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(80.0f, 80.0f, 50.0f));

	// Box当たり判定の位置を調整する
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, -250.0f), false);

	//変数の初期化
	FallON = false;
	OnProgram = true;
	GimmickCnt = 0;

	// 初期速度と初期位置の設定をする       
	startLocation = this->GetActorLocation();

	//プレイヤーをキルする
	PlayerKill = true;
}

//毎フレームの更新処理
void ACeilingfallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FallON != false)
	{
		FVector location = this->GetActorLocation();
		location.Z -= velocity;
		this->SetActorLocation(location);

		ACeilingfallGimmick::GimmickActivation();

		// GimmickCntActivationで指定したカウントが経過したら破棄
		if (GimmickCnt >= GimmickCntActivation)
		{
			//移動を停止
			velocity = 0.0f;

			//ギミックが停止したとき
			if (velocity == 0.0f)
			{
				//プレイヤーをキルしない
				PlayerKill = false;
			}
		}
	}
}

//ギミック稼働中のカウント処理
void ACeilingfallGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//プレイヤーに触れたら処理を開始するフラグを起動
void ACeilingfallGimmick::GimmickON()
{
	//UE_LOG(LogTemp, Error, TEXT("COLLTION"));

	//初期値を決定する
	if (OnProgram != false)
	{
		// 初期速度と初期位置の設定をする
		if (velocity == NULL)
		{
			velocity = 1.0f * AdjustVelocity;
		}
		if (GimmickCntActivation == NULL)
		{
			GimmickCntActivation = 10.0f * AdjustCount;
		}

		OnProgram = false;

		//UE_LOG(LogTemp, Error, TEXT("INITIALIZATION"));
	}

	//落下フラグが無効になっているとき
	if (FallON == false)
	{
		//落下処理を開始する
		FallON = true;
	}
}



	