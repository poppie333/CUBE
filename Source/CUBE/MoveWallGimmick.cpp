//-------------------------------------------------------
// ファイル名：MoveWallGimmick.cpp
// 概要　　　：GimmickBaseを継承した、移動壁ギミックのクラス
// 作成者　　：22cu0136 松丸晃汰
// 更新　　　：1/08　作成
//　　　　 　：2/13 更新
//-------------------------------------------------------


#include "MoveWallGimmick.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

//コンストラクタ
AMoveWallGimmick::AMoveWallGimmick()
{
	//Tickを起動
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("AMoveWallGimmick"));

	// StaticMeshをStaticMeshComponentに設定する
	GimmickMesh->SetStaticMesh(Mesh);

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(120.0f, 120.0f, 50.0f));

	// Box当たり判定の位置を調整する
	Box->SetRelativeLocation(FVector(40.0f, -40.0f, -250.0f), false);

	//変数の初期化
	MoveON = false;
	OnProgram = true;
	GimmickCnt = 0;

	// 初期速度と初期位置の設定をする
	startLocation = this->GetActorLocation();
}

//毎フレームの更新処理
void AMoveWallGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ギミックが起動した
	if (MoveON != false)
	{
		//移動する処理である場合
		if (Move != false)
		{
			//X軸の移動である時
			if (Xaxis != false)
			{
				//PlusMoveがtrue = プラス方向への移動である時
				if (XPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.X += velocity;
					this->SetActorLocation(location);
				}
				//PlusMoveがtrue = マイナス方向への移動である時
				if (XPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.X -= velocity;
					this->SetActorLocation(location);
				}
			}
			//Y軸の移動である時
			if (Yaxis != false)
			{
				//PlusMoveがtrue = プラス方向への移動である時
				if (YPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.Y += velocity;
					this->SetActorLocation(location);
				}
				//PlusMoveがtrue = マイナス方向への移動である時
				if (YPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.Y -= velocity;
					this->SetActorLocation(location);
				}
			}
			//Z軸の移動である時
			if (Zaxis != false)
			{
				//PlusMoveがtrue = プラス方向への移動である時
				if (ZPlusMinus != false)
				{
					FVector location = this->GetActorLocation();
					location.Z += velocity;
					this->SetActorLocation(location);
				}
				//PlusMoveがtrue = マイナス方向への移動である時
				if (ZPlusMinus == false)
				{
					FVector location = this->GetActorLocation();
					location.Z -= velocity;
					this->SetActorLocation(location);
				}
			}
		}

		//拡縮する処理である場合
		if (Scale != false)
		{
			//X軸の拡縮である時
			if (Xaxis != false)
			{
				//PlusMoveがtrue = プラス方向への拡縮である時
				if (XPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.X += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMoveがtrue = マイナス方向への拡縮である時
				if (XPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.X -= velocity;
					this->SetActorScale3D(scale);
				}
			}
			//Y軸の拡縮である時
			if (Yaxis != false)
			{
				//PlusMoveがtrue = プラス方向への拡縮である時
				if (YPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Y += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMoveがtrue = マイナス方向への拡縮である時
				if (YPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Y -= velocity;
					this->SetActorScale3D(scale);
				}
			}
			//Z軸の拡縮である時
			if (Zaxis != false)
			{
				//PlusMoveがtrue = プラス方向への拡縮である時
				if (ZPlusMinus != false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Z += velocity;
					this->SetActorScale3D(scale);
				}
				//PlusMoveがtrue = マイナス方向への拡縮である時
				if (ZPlusMinus == false)
				{
					FVector scale = this->GetActorScale3D();
					scale.Z -= velocity;
					this->SetActorScale3D(scale);
				}
			}
		}
		

		AMoveWallGimmick::GimmickActivation();

		// GimmickCntActivationで指定したカウントが経過したら破棄
		if (GimmickCnt >= GimmickCntActivation)
		{
			velocity = 0.0f;
			GimmickCnt = 0;
		}
	}
}

//ギミック稼働中のカウント処理
void AMoveWallGimmick::GimmickActivation()
{
	GimmickCnt++;
}

//プレイヤーに触れたら処理を開始するフラグを起動
void AMoveWallGimmick::GimmickON()
{
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
	}

	//このアクターを起動する処理
	if (MoveON == false)
	{
		//移動処理を開始する
		MoveON = true;
	}
}