//-------------------------------------------------------
// ファイル名：MovefloorGimmick.cpp
// 概要　　　：GimmickBaseを継承した、移動床ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：12/25 作成
//　　　　 　：1/29 更新
//　　　　 　：2/08 更新
//　　　　 　：2/09 更新
//-------------------------------------------------------

#include "MovefloorGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

//コンストラクタ
AMovefloorGimmick::AMovefloorGimmick()
{
	//Tickを起動
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("MovefloorGimmick"));

	// StaticMeshをStaticMeshComponentに設定する
	GimmickMesh->SetStaticMesh(Mesh);

	FloorDown = false;
	OnProgram = true;
}

//毎フレームの更新処理
void AMovefloorGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	//ギミックが常に稼働し続けるか
	if (AutGimmick != false)
	{
		BootGimmickReaction = true;
	}

	//一度だけ行う処理
	if (OnProgram != false)
	{
		// 初期速度と初期位置の設定をする
		if (velocity == NULL)
		{
			velocity = 1.0f * AdjustVelocity;
		}
		if (GimmickCntActivation == NULL)
		{
			GimmickCntActivation = 100.0f * AdjustCount;
		}

		//移動速度の初期値を保存
		Save_velocity = velocity;
		OnProgram = false;
	}

	//床移動の処理
	if (BootGimmickReaction != false)
	{
		//X軸の移動である時
		if (Xaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.X += velocity;
			this->SetActorLocation(location);
		}
		//Y軸の移動である時
		if (Yaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.Y += velocity;
			this->SetActorLocation(location);
		}
		//Z軸の移動である時
		if (Zaxis != false)
		{
			FVector location = this->GetActorLocation();
			location.Z += velocity;
			this->SetActorLocation(location);
		}

		//ギミック稼働中のカウント関数
		AMovefloorGimmick::GimmickActivation();

		// GimmickCntActivationで指定したカウントが経過したら破棄
		if (GimmickCnt >= GimmickCntActivation)
		{
			//上昇中か下降中かを判別するフラグを切り替える
			if (FloorDown == false)
			{
				FloorDown = true;
			}
			else if (FloorDown != false)
			{
				FloorDown = false;
			}

			//一時停止処理
			velocity = 0.0f;

			//再稼働処理
			if (GimmickCnt >= GimmickCntActivation * 1.5)
			{
				if (FloorDown == false)
				{
					velocity = -Save_velocity;
				}
				else if (FloorDown != false)
				{
					velocity = Save_velocity;
				}

				GimmickCnt = 0;
				velocity = -velocity;
			}
		}
	}
}

//ギミック稼働中のカウント処理
void AMovefloorGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//プレイヤーに触れたら行う処理
void AMovefloorGimmick::GimmickON()
{
	//ギミックを起動
	BootGimmick = true;

	//スイッチを押したら後は自動で動き続ける
	if (AutGimmickBoot != false)
	{
		AutGimmick = true;
	}
}
